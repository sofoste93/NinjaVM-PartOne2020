#include "njvm.h"
#include "opcodes.h"

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_CAPACITY 1000000U
#define MAX_CODE_WORDS 10000000U
#define MAX_GLOBALS 1000000U

typedef struct {
    uint32_t *code;
    size_t code_count;
    int32_t *globals;
    size_t global_count;
    int32_t *stack;
    size_t sp;
    size_t fp;
    uint32_t pc;
    int32_t return_register;
    bool halted;
    bool debug;
} Vm;

static int fail(const char *format, ...) {
    va_list arguments;
    fprintf(stderr, "Error: ");
    va_start(arguments, format);
    vfprintf(stderr, format, arguments);
    va_end(arguments);
    fputc('\n', stderr);
    return 1;
}

static bool read_u32_le(FILE *file, uint32_t *value) {
    unsigned char bytes[4];
    if (fread(bytes, 1, sizeof(bytes), file) != sizeof(bytes)) {
        return false;
    }
    *value = (uint32_t)bytes[0]
        | ((uint32_t)bytes[1] << 8U)
        | ((uint32_t)bytes[2] << 16U)
        | ((uint32_t)bytes[3] << 24U);
    return true;
}

static int32_t sign_extend_24(uint32_t immediate) {
    if ((immediate & 0x00800000U) != 0U) {
        immediate |= 0xFF000000U;
    }
    return (int32_t)immediate;
}

static void vm_destroy(Vm *vm) {
    free(vm->code);
    free(vm->globals);
    free(vm->stack);
    memset(vm, 0, sizeof(*vm));
}

static int vm_load(Vm *vm, const char *path) {
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        return fail("cannot open code file '%s'", path);
    }

    unsigned char magic[4];
    uint32_t version = 0;
    uint32_t code_count = 0;
    uint32_t global_count = 0;
    int result = 1;

    if (fread(magic, 1, sizeof(magic), file) != sizeof(magic)
        || memcmp(magic, "NJBF", sizeof(magic)) != 0) {
        fail("file '%s' is not a Ninja binary", path);
        goto cleanup;
    }
    if (!read_u32_le(file, &version)
        || !read_u32_le(file, &code_count)
        || !read_u32_le(file, &global_count)) {
        fail("file '%s' has an incomplete NJBF header", path);
        goto cleanup;
    }
    if (version != NJVM_BINARY_VERSION) {
        fail("file '%s' uses NJBF version %" PRIu32 "; expected 4", path, version);
        goto cleanup;
    }
    if (code_count == 0U || code_count > MAX_CODE_WORDS || global_count > MAX_GLOBALS) {
        fail("file '%s' declares unreasonable code or global sizes", path);
        goto cleanup;
    }

    vm->code = calloc(code_count, sizeof(*vm->code));
    vm->globals = calloc(global_count == 0U ? 1U : global_count, sizeof(*vm->globals));
    vm->stack = calloc(STACK_CAPACITY, sizeof(*vm->stack));
    if (vm->code == NULL || vm->globals == NULL || vm->stack == NULL) {
        fail("not enough memory to initialize the virtual machine");
        goto cleanup;
    }

    vm->code_count = code_count;
    vm->global_count = global_count;
    for (size_t index = 0; index < vm->code_count; ++index) {
        if (!read_u32_le(file, &vm->code[index])) {
            fail("file '%s' ends before its declared code segment", path);
            goto cleanup;
        }
    }

    if (fgetc(file) != EOF) {
        fail("file '%s' contains unexpected bytes after the code segment", path);
        goto cleanup;
    }
    result = 0;

cleanup:
    fclose(file);
    if (result != 0) {
        vm_destroy(vm);
    }
    return result;
}

static bool push(Vm *vm, int32_t value) {
    if (vm->sp >= STACK_CAPACITY) {
        fail("stack overflow at instruction %" PRIu32, vm->pc - 1U);
        return false;
    }
    vm->stack[vm->sp++] = value;
    return true;
}

static bool pop(Vm *vm, int32_t *value) {
    if (vm->sp == 0U) {
        fail("stack underflow at instruction %" PRIu32, vm->pc - 1U);
        return false;
    }
    *value = vm->stack[--vm->sp];
    return true;
}

static bool local_index(Vm *vm, int32_t offset, size_t *index) {
    int64_t candidate = (int64_t)vm->fp + offset;
    if (candidate < 0 || (uint64_t)candidate >= vm->sp) {
        fail("local variable offset %" PRId32 " is outside the current frame", offset);
        return false;
    }
    *index = (size_t)candidate;
    return true;
}

static const char *opcode_name(unsigned int opcode) {
    static const char *names[] = {
        "halt", "pushc", "add", "sub", "mul", "div", "mod", "rdint",
        "wrint", "rdchr", "wrchr", "pushg", "popg", "asf", "rsf", "pushl",
        "popl", "eq", "ne", "lt", "le", "gt", "ge", "jmp", "brf", "brt",
        "call", "ret", "drop", "pushr", "popr", "dup"
    };
    return opcode < sizeof(names) / sizeof(names[0]) ? names[opcode] : "unknown";
}

static void print_stack(const Vm *vm) {
    fprintf(stderr, "stack[%zu]:", vm->sp);
    for (size_t index = 0; index < vm->sp; ++index) {
        fprintf(stderr, " %" PRId32, vm->stack[index]);
    }
    fputc('\n', stderr);
}

static bool debug_prompt(Vm *vm, uint32_t address, uint32_t instruction) {
    char command[32];
    fprintf(stderr, "[pc=%04" PRIu32 "] %-6s imm=%" PRId32 "  sp=%zu > ",
            address, opcode_name(NJVM_OPCODE(instruction)),
            sign_extend_24(NJVM_IMMEDIATE(instruction)), vm->sp);

    while (fgets(command, sizeof(command), stdin) != NULL) {
        if (command[0] == '\n' || command[0] == 's') {
            return true;
        }
        if (command[0] == 'c' || command[0] == 'r') {
            vm->debug = false;
            return true;
        }
        if (command[0] == 'p') {
            print_stack(vm);
        } else if (command[0] == 'q') {
            vm->halted = true;
            return false;
        } else {
            fprintf(stderr, "commands: [Enter]/s step, c continue, p stack, q quit\n");
        }
        fprintf(stderr, "debug > ");
    }
    vm->halted = true;
    return false;
}

static bool binary_operands(Vm *vm, int32_t *left, int32_t *right) {
    return pop(vm, right) && pop(vm, left);
}

static bool read_integer(int32_t *value) {
    char input[128];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fail("could not read an integer");
        return false;
    }

    char *end = NULL;
    errno = 0;
    long parsed = strtol(input, &end, 10);
    while (end != NULL && isspace((unsigned char)*end)) {
        ++end;
    }
    if (end == input || end == NULL || *end != '\0' || errno == ERANGE
        || parsed < INT32_MIN || parsed > INT32_MAX) {
        fail("input is not a valid 32-bit integer");
        return false;
    }
    *value = (int32_t)parsed;
    return true;
}

static bool execute(Vm *vm, uint32_t instruction) {
    unsigned int opcode = NJVM_OPCODE(instruction);
    uint32_t immediate = NJVM_IMMEDIATE(instruction);
    int32_t left = 0;
    int32_t right = 0;
    size_t index = 0;

    switch (opcode) {
        case OP_HALT:
            vm->halted = true;
            return true;
        case OP_PUSHC:
            return push(vm, sign_extend_24(immediate));
        case OP_ADD:
            return binary_operands(vm, &left, &right)
                && push(vm, (int32_t)((uint32_t)left + (uint32_t)right));
        case OP_SUB:
            return binary_operands(vm, &left, &right)
                && push(vm, (int32_t)((uint32_t)left - (uint32_t)right));
        case OP_MUL:
            return binary_operands(vm, &left, &right)
                && push(vm, (int32_t)((uint32_t)left * (uint32_t)right));
        case OP_DIV:
        case OP_MOD:
            if (!binary_operands(vm, &left, &right)) return false;
            if (right == 0) return fail("division by zero at instruction %" PRIu32, vm->pc - 1U) == 0;
            if (left == INT32_MIN && right == -1) {
                return push(vm, opcode == OP_DIV ? INT32_MIN : 0);
            }
            return push(vm, opcode == OP_DIV ? left / right : left % right);
        case OP_RDINT:
            if (!read_integer(&left)) return false;
            return push(vm, left);
        case OP_WRINT:
            if (!pop(vm, &left)) return false;
            printf("%" PRId32, left);
            return true;
        case OP_RDCHR:
            left = getchar();
            if (left == EOF) return fail("could not read a character") == 0;
            return push(vm, left);
        case OP_WRCHR:
            if (!pop(vm, &left)) return false;
            putchar((unsigned char)left);
            return true;
        case OP_PUSHG:
        case OP_POPG:
            if (immediate >= vm->global_count) return fail("global index %" PRIu32 " is out of range", immediate) == 0;
            if (opcode == OP_PUSHG) return push(vm, vm->globals[immediate]);
            if (!pop(vm, &left)) return false;
            vm->globals[immediate] = left;
            return true;
        case OP_ASF:
            if (immediate > STACK_CAPACITY - vm->sp - 1U) return fail("stack overflow while creating a frame") == 0;
            if (!push(vm, (int32_t)vm->fp)) return false;
            vm->fp = vm->sp;
            vm->sp += immediate;
            return true;
        case OP_RSF:
            if (vm->fp > vm->sp) return fail("invalid frame pointer") == 0;
            vm->sp = vm->fp;
            if (!pop(vm, &left) || left < 0 || (size_t)left > vm->sp) return fail("invalid saved frame pointer") == 0;
            vm->fp = (size_t)left;
            return true;
        case OP_PUSHL:
        case OP_POPL:
            if (!local_index(vm, sign_extend_24(immediate), &index)) return false;
            if (opcode == OP_PUSHL) return push(vm, vm->stack[index]);
            if (!pop(vm, &left)) return false;
            vm->stack[index] = left;
            return true;
        case OP_EQ: case OP_NE: case OP_LT: case OP_LE: case OP_GT: case OP_GE:
            if (!binary_operands(vm, &left, &right)) return false;
            switch (opcode) {
                case OP_EQ: left = left == right; break;
                case OP_NE: left = left != right; break;
                case OP_LT: left = left < right; break;
                case OP_LE: left = left <= right; break;
                case OP_GT: left = left > right; break;
                default: left = left >= right; break;
            }
            return push(vm, left);
        case OP_JMP:
            vm->pc = immediate;
            return true;
        case OP_BRF:
        case OP_BRT:
            if (!pop(vm, &left)) return false;
            if ((opcode == OP_BRF && left == 0) || (opcode == OP_BRT && left != 0)) vm->pc = immediate;
            return true;
        case OP_CALL:
            if (!push(vm, (int32_t)vm->pc)) return false;
            vm->pc = immediate;
            return true;
        case OP_RET:
            if (!pop(vm, &left) || left < 0) return fail("invalid return address") == 0;
            vm->pc = (uint32_t)left;
            return true;
        case OP_DROP:
            if (immediate > vm->sp) return fail("cannot drop %" PRIu32 " values from a stack of %zu", immediate, vm->sp) == 0;
            vm->sp -= immediate;
            return true;
        case OP_PUSHR:
            return push(vm, vm->return_register);
        case OP_POPR:
            return pop(vm, &vm->return_register);
        case OP_DUP:
            if (vm->sp == 0U) return fail("cannot duplicate an empty stack") == 0;
            return push(vm, vm->stack[vm->sp - 1U]);
        default:
            return fail("unknown opcode %u at instruction %" PRIu32, opcode, vm->pc - 1U) == 0;
    }
}

static int vm_run(Vm *vm) {
    while (!vm->halted) {
        if (vm->pc >= vm->code_count) {
            return fail("program counter %" PRIu32 " is outside the code segment", vm->pc);
        }
        uint32_t address = vm->pc;
        uint32_t instruction = vm->code[vm->pc++];
        if (vm->debug && !debug_prompt(vm, address, instruction)) {
            break;
        }
        if (!vm->halted && !execute(vm, instruction)) {
            return 1;
        }
    }
    return 0;
}

int njvm_run_file(const char *path, bool debug_mode) {
    Vm vm = {0};
    vm.debug = debug_mode;
    if (vm_load(&vm, path) != 0) {
        return 1;
    }

    printf("Ninja Virtual Machine started\n");
    int result = vm_run(&vm);
    if (result == 0) {
        printf("Ninja Virtual Machine stopped\n");
    }
    vm_destroy(&vm);
    return result;
}
