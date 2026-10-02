#include "njvm.h"

#include <stdio.h>
#include <string.h>

static void print_help(const char *program) {
    printf("Usage: %s [options] <code-file>\n", program);
    printf("\nOptions:\n");
    printf("  --debug      start in the interactive step debugger\n");
    printf("  --version    show version information and exit\n");
    printf("  --help       show this help and exit\n");
}

int main(int argc, char **argv) {
    const char *code_path = NULL;
    bool debug_mode = false;

    for (int index = 1; index < argc; ++index) {
        if (strcmp(argv[index], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        }
        if (strcmp(argv[index], "--version") == 0) {
            printf("Ninja Virtual Machine %s (NJBF format 4)\n", NJVM_RELEASE_VERSION);
            return 0;
        }
        if (strcmp(argv[index], "--debug") == 0) {
            debug_mode = true;
            continue;
        }
        if (argv[index][0] == '-') {
            fprintf(stderr, "Error: unknown option '%s'; try --help\n", argv[index]);
            return 2;
        }
        if (code_path != NULL) {
            fprintf(stderr, "Error: more than one code file specified\n");
            return 2;
        }
        code_path = argv[index];
    }

    if (code_path == NULL) {
        fprintf(stderr, "Error: no code file specified; try --help\n");
        return 2;
    }

    return njvm_run_file(code_path, debug_mode);
}
