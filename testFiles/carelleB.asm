_main:
    asf     0
    pushc   2
    pushc   3
    pushc   4
    call    _b
    drop    3
    rsf
    halt

_b:
    asf     3
    pushl   -5
    pushl   -4
    add
    popl    0
    pushl   -4
    pushl   -3
    sub
    popl    1
    pushl   0
    pushl   1
    add
    popl    2
    pushl   2
    wrint
    pushc   10
    wrchr
    rsf
    halt

