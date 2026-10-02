main:
    asf     1
    pushc   3
    pushc   25
    call    print_n_times
    pushr
    popl    0
    pushl   0
    wrint
    pushc   10
    wrchr
    rsf
    halt

print_n_times:
    asf     2
    pushl   -4
    pushc   0
    lt
    brt     end
    pushc   0
    popl    0
    jmp    while_cond

while_cond:
    pushl   0
    pushl   -4
    ne
    brt     while_body
    jmp    last_end

while_body:
    pushl   -3
    wrint
    pushc   10
    wrchr
    pushl   0
    pushc   1
    add
    popl    0
    jmp    while_cond

end:
    pushc   -1
    popr
    rsf
    ret

last_end:
    pushl   -4
    pushl   -3
    add
    popl    1
    pushl   1
    popr
    rsf
    ret
