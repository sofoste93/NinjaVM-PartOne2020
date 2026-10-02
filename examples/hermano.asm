main:
    asf     0
    pushc   4             
    pushc  -3
    pushc   -5
    pushc    1
    call    ff
    drop    4
    pushr
    wrint 
    pushc   10
    wrchr
    rsf
    halt
    
ff:
    asf    0
    pushl    -6
	pushc     0
	gt
	pushl    -5
	pushc     0
	gt
	eq
	pushl     -4
	pushc      0
	lt
	pushl     -3
	pushc      0
	lt
	eq
	brt	      if_block
    brt       if_block
	jmp	      if_cond
	jmp	      end	

if_block:
    pushl      -6
	pushl      -5
	add
	pushl      -4
	pushl      -3
	sub
	mul
	popr
    rsf
	ret

if_cond:
    pushl       -6
    pushc        0
	lt
	pushl       -5
	pushc        0
	lt
	eq
	pushl        -4
	pushc	0
	gt
	pushl 	-3
	pushc      0
	gt
	eq
	brt		if_body
    brt      if_body
	jmp		end
	
if_body:
    pushl        -6
	pushl	 -5
	sub
	pushl        -4
	pushl        -3
	add
	div
	popr
	rsf
	ret
	
end:
    pushl	  -6
	pushl         -5	
	sub
	pushl         -4
	pushl         -3
	add
	mod
	popr
	rsf
	ret
