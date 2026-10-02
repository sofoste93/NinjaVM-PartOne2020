//void main(){
//local Integer a;
//local Integer b;

//a=readInteger();
//b=fak(a);
//writeInteger(b);
//writeCharacter('\n');
//}

//Integer fak(Integer n){
//local Integer res;
//res=1;
//while(n>0){
//res=res*n;
//n=n-1;
//}
//return res;
//}

//_main()

_main:
    asf     2
    rdint   
    popl    0
    pushl   0
    
    call    _fak
    drop    1
    pushr
    popl    1
    pushl   1
    wrint
    pushc   10
    wrchr
    rsf
    halt
    
//_fak(Integer)

_fak:
    asf     1
    pushc   1
    popl    0
    
_l1:
    pushl   -3
    pushc   0
    gt
    brt     _l2
    
    
    pushl   0
    popr
    rsf
    ret
    
_l2:
    pushl    0
    pushl   -3
    mul
    popl    0
    pushl   -3
    pushc   1
    sub
    popl    -3
    jmp     _l1
