//void main(){
//    writeInteger(k(4,-3));
//    writeCharacter('\n');
//}

//Integer k(Integer a, Integer b){
//    if(a>0 && b>0)
//        return a+b;
//    if(a<0 && b<0)
//        return a*b
//    return a-b;
//}


main:
    asf     0
    pushc   4
    pushc   -3
    call    k
    drop    2
    pushr
    wrint
    pushc   10
    wrchr
    rsf
    halt

k:
    asf     0
    pushl   -4
    pushc   0
    gt
    pushl   -3
    pushc   0
    gt
    eq
    brt     end_p
    pushl   -4
    pushc   0
    lt
    pushl   -3
    pushc   0
    lt
    eq
    brt     end_m
    pushl   -4
    pushl   -3
    sub
    popr
    rsf
    ret

end_p:
    pushl   -4
    pushl   -3
    add
    popr
    rsf
    ret

end_m:
    pushl   -4
    pushl   -3
    mul
    popr
    rsf
    ret

