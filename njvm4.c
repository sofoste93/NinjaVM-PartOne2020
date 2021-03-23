//
// Created by sofoste on 23.03.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "header.h"
#include "unixshell.h"

int stack [1000000];
unsigned int PC;
unsigned int *reg;
unsigned int readableFileIndex;
unsigned int optionIndex;
int *sda;
unsigned int IR,SP,FP,SR;
FILE *file;
bool debugger;
unsigned int breakPoint;
unsigned int rest[3];

int main(int argc, char *argv[])
        BEGIN
        debugger=false;
        breakPoint=false;
                IF argc>3 THEN
printf("Error: more than one code file specified\n");
exit(0);
ELIF argc==1 THEN
printf("Error: no code file specified\n");
exit(0);
ELSE
        IF argc==3 THEN
        IF NOT anyOption(argv,1,argc) THEN
        IF NOT anyReadable(argv,1,argc) THEN
printf("Error: cannot open code file '%s'\n",argv[1]);
exit(0);
ELSE
file_handler(argv,readableFileIndex);
printf(START);
runVM();
FI
        ELSE
option_mapper(argv);
// DEBUG MODE
printf("debugger is not done yet\n");

FI
        ELIF argc==2 THEN
        IF NOT anyOption(argv,1,argc) THEN
        IF NOT anyReadable(argv,1,argc) THEN
printf("Error: cannot open code file '%s'\n",argv[1]);
exit(0);
ELSE
file_handler(argv,1);
printf(START);
runVM();
FI
        ELSE
option_mapper(argv);
FI
        FI
FI
return 0;
END

void file_handler(char **argv,unsigned int fd)
        BEGIN
        file=NULL;
        char f_form[4];
        file=fopen(argv[fd],"rb");
                fread(f_form,sizeof(char),4,file);
f_form[4]='\0';
fread(rest,sizeof(int),3,file);

//printf("file_format %s and size %d \nand V_numer %d\n", f_form,strlen(f_form),rest[0]);

IF strcmp(f_form,"NJBF")!=0 THEN
printf("Error: file '%s' is not a Ninja binary\n",argv[fd]);
exit(0);
ELIF rest[0]!=VM_VERSION THEN
printf("Error: file '%s' has wrong version number\n",argv[fd]);
exit(0);
ELSE
        reg=malloc(sizeof(unsigned int)*rest[1]);
fread(reg,sizeof(unsigned int),rest[1],file);
IF rest[2]!=0 THEN sda=malloc(sizeof(int)*rest[2]); FI
init_all();
FI
        END

void init_all(void)
        BEGIN
        PC=0;
        IR=0;
        SP=0;
        FP=0;
        SR=0;
                END

                bool anyOption(char **argv,unsigned int index,unsigned int limit)
BEGIN
        IF index==limit THEN return false; FI
// TODO indexOUtBound
IF argv[index][0]=='-' && argv[index][1]=='-' THEN
        optionIndex=index;
return true;
FI

return anyOption(argv,index+1,limit);
END

bool anyReadable(char **argv,unsigned int index,unsigned int limit)
BEGIN
//FILE *tmpF=NULL;
IF index==limit THEN return false; FI

        IF fopen(argv[index],"rb")!=NULL THEN
        readableFileIndex=index;
return true;
FI

return anyReadable(argv,index+1,limit);
END

void option_mapper(char ** argv)
BEGIN
        IF strcmp(argv[optionIndex],"--debug")==0 THEN option_handler(argv[optionIndex],103);
ELIF strcmp(argv[optionIndex],"--help")==0 THEN option_handler(argv[optionIndex],101);
ELIF strcmp(argv[optionIndex],"--version")==0 THEN option_handler(argv[optionIndex],102);
ELSE option_handler(argv[optionIndex],404);
FI

        END
void option_handler(char *opt_str,unsigned int opt)
BEGIN
        SWITCH opt IN
WHEN DEBUG: debugger=true;
ENDW
        WHEN HELP:printf("Usage: ./njvm [options] <code file>\nOptions:\n  --debug\t\tstart virtual machine in debug mode\n  --version\t\tshow version and exit\n  --help\t\tshow this help and exit\n");
exit(0);
ENDW

        WHEN VERSION:printf("Ninja Virtual Machine version 4 Compiled %s at %s\n",__DATE__,__TIME__);
exit(0);
ENDW
        DEFAULT
printf("Error: unknown option '%s', try './njvm --help'\n",opt_str);
exit(0);
ENDW

        ENDSW
END


void runVM(void)
        BEGIN
        IR=reg[PC];
                //printf("IR := %d\n",reg[PC+1]>>24);
                PC+=1;
runner(IR);
runVM();
END

void stopVM(void)
        BEGIN
        printf(STOP);
                exit(0);
END


void push(int v)
        BEGIN
        stack[SP++]=v;
                END

                int pop(void)
BEGIN
return stack[--SP];
END

void asf(int frame_size)
BEGIN
push(FP);
FP=SP;
SP+=frame_size;
END

void rsf(void)
        BEGIN
        SP=FP;
        FP=pop();
                END

                void drop(int n)
BEGIN
        IF n==0 THEN return; FI
pop();
drop(--n);
END

void stack_printer(int i){
    IF i==-1 THEN return; FI
    printf("stack[%i]:= %d\n",i,stack[i]);
    stack_printer(--i);
}
void runner(unsigned int IR)
        BEGIN
        char rdc;
        int op1,op2,rdi;
                //stack_printer(PC);
                //printf("IR := %d\n",IR>>24);
                SWITCH IR >> 24 IN
        WHEN HALT: stopVM();   //end framework
ENDW
        WHEN PUSHC: push(SIGN_EXTEND(IMMEDIATE(IR)));
ENDW

        WHEN ADD:op1=pop();
op2=pop();
push(op1+op2);
ENDW

        WHEN SUB:op1=pop();
op2=pop();
push(op2-op1);
ENDW

        WHEN MUL:op1=pop();
op2=pop();
push(op1*op2);
ENDW

        WHEN DIV:op1=pop();
op2=pop();
IF op1==0 THEN
printf("Error: Division by 0\n");
exit(0);
ELSE
push(op2/op1);
FI
        ENDW

WHEN MOD:op1=pop();
op2=pop();
push(op2%op1);
ENDW

        WHEN WRINT:printf("%d",pop());
ENDW

        WHEN RDINT:scanf("%d", &rdi);
push(rdi);
ENDW

        WHEN WRCHR:printf("%c",pop());
ENDW

        WHEN RDCHR:scanf("%c", &rdc);
push(rdc);
ENDW

        WHEN PUSHG:push(sda[IMMEDIATE(IR)]);
ENDW

        WHEN POPG:sda[IMMEDIATE(IR)]=pop();
ENDW

        WHEN ASF:asf(IMMEDIATE(IR));
ENDW
        WHEN RSF:rsf();
ENDW
        WHEN PUSHL:push(stack[FP+SIGN_EXTEND(IMMEDIATE(IR))]);
ENDW
        WHEN POPL:stack[FP+SIGN_EXTEND(IMMEDIATE(IR))]=pop();
ENDW

        WHEN EQ:op1=pop();
op2=pop();
push(op1==op2);
ENDW
        WHEN NE:op1=pop();
op2=pop();
push(op1!=op2);
ENDW

        WHEN LT:op1=pop();
op2=pop();
push(op2<op1);
ENDW

        WHEN LE:op1=pop();
op2=pop();
push(op2<=op1);
ENDW

        WHEN GT:op1=pop();
op2=pop();
push(op2>op1);
ENDW

        WHEN GE:op1=pop();
op2=pop();
push(op2>=op1);
ENDW

        WHEN JMP:PC=IMMEDIATE(IR);
ENDW
        WHEN BRF:IF NOT pop() THEN
                              PC=IMMEDIATE(IR);
        FI
        ENDW
WHEN BRT:IF pop() THEN
                  PC=IMMEDIATE(IR);
        FI
        ENDW
WHEN CALL:push(PC);
PC=IMMEDIATE(IR);
ENDW
        WHEN RET:PC=pop();
ENDW
        WHEN DROP:drop(IMMEDIATE(IR));
ENDW
        WHEN PUSHR:push(SR);
ENDW
        WHEN POPR:SR=pop();
ENDW
        WHEN DUP:push(stack[SP-1]);
ENDW
        ENDSW

END
