_main:
    asf     0
    call    _a
    drop    0 
    rsf 
    halt

 _a :
    asf     3
    pushc   10
    popl    0
    pushc   2
    popl    1
    pushl   0
    pushl   1
    mod
    popl    2
    pushc   10
    wrchr
    rsf
    ret
