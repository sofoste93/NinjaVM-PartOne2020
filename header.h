//
// Created by sofoste on 23.03.2021.
//

#ifndef NINJAVM_PARTONE2020_HEADER_H
#define NINJAVM_PARTONE2020_HEADER_H
#ifndef HEADER_H
#define HEADER_H


#define HALT  0

#define PUSHC 1
#define ADD   2
#define SUB   3
#define MUL   4
#define DIV   5
#define MOD   6

#define RDINT 7
#define WRINT 8
#define RDCHR 9
#define WRCHR 10

#define PUSHG 11
#define POPG  12

#define ASF   13
#define RSF   14
#define PUSHL 15
#define POPL  16

#define EQ    17
#define NE    18
#define LT    19
#define LE    20
#define GT    21
#define GE    22


#define JMP   23
#define BRF   24
#define BRT   25

#define CALL  26
#define RET   27
#define DROP  28
#define PUSHR 29
#define POPR  30

#define DUP   31

#define START	"Ninja Virtual Machine started\n"
#define STOP	"Ninja Virtual Machine stopped\n"

#define HELP	101
#define VERSION	102
#define DEBUG	103

#define VM_VERSION 4

#define IMMEDIATE(x) ((x) & 0x00FFFFFF)
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))

void init_all(void);
void runVM();
void stopVM();
void runner(unsigned int IR);
void push(int v);
int pop(void);
void asf(int frame_size);
void rsf(void);
void drop(int n);
void option_handler(char* opt_str,unsigned int opt);
void option_mapper(char **argv);
bool anyReadable(char *argv[],unsigned int index,unsigned int limit);
bool anyOption(char *argv[],unsigned int index,unsigned int limit);
void file_handler(char **argv,unsigned int fd);
void stack_printer(int i);

#endif // HEADER_H

#endif //NINJAVM_PARTONE2020_HEADER_H
