//void main(){
//    local Integer n;
//    n=readInteger();
//    writeInteger(isPrime(n));
//    writeCharacter('\n');
//}

//Boolean isPrime(Integer n){
//    local Integer i;
//    if(n<=0)
//        return false;
//    i=n-1;
//    while(i>1){
//        if((n%i)==0)
//            return false;
//        i=i-1;
//    }
//    return true;
//}


main:
    asf     1
    rdint
    popl    0
    pushl   0
    call isPrime
    drop    1
    pushr
    wrint
    pushc   10
    wrchr
    rsf
    halt

isPrime:
    asf     1
    pushl   -3
    pushc   0
    le
    brt     end_0
    pushl   -3
    pushc   1
    sub
    popl    0
    jmp loop_cond
    
loop_cond:
    pushl   0
    pushc   1
    gt
    brt     loop_body
    jmp     end_1

loop_body:
    pushl   -3
    pushl   0
    mod
    pushc   0
    eq
    brt     end_0
    pushl   0
    pushc   1
    sub
    popl    0
    jmp     loop_cond

end_1:
    pushc   1
    popr
    rsf
    ret
    
end_0:
    pushc   0
    popr
    rsf
    ret

    
    
