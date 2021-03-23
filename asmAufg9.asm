main:
    asf     2
    pushc   2
    popl    0
    pushc   10
    popl    1
    pushl   0
    pushl   1
    gt
    brt     if_body
    jmp     else_body
    
if_body:
    pushl   0
    pushl   1
    sub
    popl    0
    jmp end
    
else_body:
    pushl   1
    pushl   0
    sub
    popl    1
    jmp end

end:
    pushl   0
    wrint
    pushc   10
    wrchr
    pushl   1
    wrint
    pushc   10
    wrchr
    rsf
    halt
