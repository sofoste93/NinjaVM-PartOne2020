//
// Created by sofoste on 23.03.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcDefAndGlobVar.h"
#include "instructionsAndMacros.h"


void dg(void){
    brkpoint=0;
    printf("******************************************************\n");
    printf("Wellcome in NINJA-VM DEBUG mode\n\n* file loaded:\t%s \n* code size:\t%d \n* sda size:\t%d \n\n",binFileName,important_value[1],important_value[2]);
    printf("******************************************************\n");
    char input[64];
    while(1){
        visualIndicator();
        printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");
        fgets(input,64,stdin);

        if(input[0]=='i'){
            printf("DEBUG [inspect]\n");
            printf("stack, data ?\n");
            fgets(input,12,stdin);
            if(input[0]=='s'){
                if(sp==0 && fp==0){
                    printf("sp, fp  --->\t%04d:\txxxx\n",sp);
                }
                else{
                    for(int i=sp; i>=0;i--){
                        if(i==sp) printf("sp   ----->\t%04d:\txxxx\n",i);
                        else if(i==fp) printf("fp   ----->\t%04d:\t%d\n",i,stack[i]);
                        else printf("\t\t%04d:\t%d\n",i,stack[i]);
                    }
                    printf("\t\t--- bottom of stack ---\n");
                }
            }

            else if(input[0]=='d'){
                if(sda!=NULL){
                    for(int i=0; i<important_value[2];i++){
                        printf("data[%04d]:\t%d\n",i,sda[i]);
                    }
                }
                printf("\t--- end of data ---\n");
            }

            else;

        }
        else if(input[0]=='l'){
            int irCopy=ir;
            int pcCopy=pc;
            for(int i=0; i<=important_value[1];i++){
                pc=i;
                visualIndicator();
            }
            printf("\n");
            ir=irCopy; pc=pcCopy;
        }

        else if(input[0]=='b'){
            printf("DEBUG [breakpoint]\n");
            if(brkpoint!=0) {
                printf("breakpoint current value :  %d\n",brkpoint);
                printf("enter <clear> to clear this , write a <value> to replace his value or <ret> to return\n");
                fgets(input,12,stdin);
                if(input[0]=='c') {
                    brkpoint=0;
                    brkpointstatus=false;
                }
                else if(isInteger(input)){
                    brkpoint=atoi(input);
                    brkpointstatus=true;
                }
                else;
            }
            else {
                printf("breakpoint is cleared\n");
                printf("enter a value to set his value or <ret> to return\n");
                fgets(input,12,stdin);
                if(isInteger(input)){
                    brkpoint=atoi(input);
                    brkpointstatus=true;
                }
            }
        }

        else if(input[0]=='s'){
            runProgWithdgOn();
        }

        else if(input[0]=='r') runProgWithdgOff();
        else if(input[0]=='q') vmFrameWork(0);
        else printf("unknown option :(\n");

        //vmFrameWork(0);
    }
}

void visualIndicator(void){
    ir=regist[pc];
    switch (ir>>24)
    {
        case HALT :printf("%04d:\thalt\n",pc);
            break;
        case PUSHC :printf("%04d:\tpushc\t%d\n",pc,SIGN_EXTEND(IMMEDIATE(ir)));
            break;
        case ADD : printf("%04d:\tadd\t\n",pc);
            break;
        case SUB :printf("%04d:\tsub\t\n",pc);
            break;
        case MUL :printf("%04d:\tmul\t\n",pc);
            break;
        case DIV :printf("%04d:\tdiv\t\n",pc);
            break;
        case MOD :printf("%04d:\tmod\t\n",pc);
            break;
        case WRINT :printf("%04d:\twrint\t\n",pc);
            break;
        case RDINT :printf("%04d:\trdint\t\n",pc);
            break;
        case WRCHR :printf("%04d:\twrchr\t\n",pc);
            break;
        case RDCHR :printf("%04d:\trdchr\t\n",pc);
            break;
        case PUSHG:printf("%04d:\tpushg\t%d\n",pc,IMMEDIATE(ir));
            break;
        case POPG:printf("%04d:\tpopg\t%d\n",pc,IMMEDIATE(ir));
            break;
        case ASF:printf("%04d:\tasf\t%d\n",pc,IMMEDIATE(ir));
            break;
        case RSF:printf("%04d:\trsf\t\n",pc);
            break;
        case PUSHL:printf("%04d:\tpushl\t%d\n",pc,SIGN_EXTEND(IMMEDIATE(ir)));
            break;
        case POPL: printf("%04d:\tpopl\t%d\n",pc,SIGN_EXTEND(IMMEDIATE(ir)));
            break;
        case EQ:printf("%04d:\teq\t\n",pc);
            break;
        case NE:printf("%04d:\tne\t\n",pc);
            break;
        case LT:printf("%04d:\tlt\t\n",pc);
            break;
        case LE:printf("%04d:\tle\t\n",pc);
            break;
        case GT:printf("%04d:\tgt\t\n",pc);
            break;
        case JMP:printf("%04d:\tjmp\t%d\n",pc,IMMEDIATE(ir));
            break;
        case GE:printf("%04d:\tge\t\n",pc);
            break;
        case BRF:printf("%04d:\tbrf\t%d\n",pc,IMMEDIATE(ir));
            break;
        case BRT:printf("%04d:\tbrt\t%d\n",pc,IMMEDIATE(ir));
            break;
        case CALL:printf("%04d:\tcall\t%d\n",pc,IMMEDIATE(ir));
            break;
        case RET:printf("%04d:\tret\t\n",pc);
            break;
        case DROP:printf("%04d:\tdrop\t%d\n",pc,IMMEDIATE(ir));
            break;
        case PUSHR:printf("%04d:\tpushr\t\n",pc);
            break;
        case POPR:printf("%04d:\tpopr\t\n",pc);
            break;
        case DUP:printf("%04d:\tdup\t\n",pc);
            break;
    }
}
