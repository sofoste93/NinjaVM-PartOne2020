#ifndef NJVM_OPCODES_H
#define NJVM_OPCODES_H

/* Instruction numbers defined by the THM Ninja VM version 4 format. */
enum NjvmOpcode {
    OP_HALT = 0,
    OP_PUSHC = 1,
    OP_ADD = 2,
    OP_SUB = 3,
    OP_MUL = 4,
    OP_DIV = 5,
    OP_MOD = 6,
    OP_RDINT = 7,
    OP_WRINT = 8,
    OP_RDCHR = 9,
    OP_WRCHR = 10,
    OP_PUSHG = 11,
    OP_POPG = 12,
    OP_ASF = 13,
    OP_RSF = 14,
    OP_PUSHL = 15,
    OP_POPL = 16,
    OP_EQ = 17,
    OP_NE = 18,
    OP_LT = 19,
    OP_LE = 20,
    OP_GT = 21,
    OP_GE = 22,
    OP_JMP = 23,
    OP_BRF = 24,
    OP_BRT = 25,
    OP_CALL = 26,
    OP_RET = 27,
    OP_DROP = 28,
    OP_PUSHR = 29,
    OP_POPR = 30,
    OP_DUP = 31
};

#define NJVM_BINARY_VERSION 4U
#define NJVM_OPCODE(word) ((unsigned int)((word) >> 24U))
#define NJVM_IMMEDIATE(word) ((word) & 0x00FFFFFFU)

#endif
