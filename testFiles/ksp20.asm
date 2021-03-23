main:
	asf	1
	pushc	0
	popl	0
	jmp	loop_cond

loop_cond:
	pushl	0
	pushc	10
	lt
	brt	loop_body
	rsf
	halt

loop_body:
	pushl	0
	call	print
	drop	1
	pushr
	wrint
	pushc	10
	wrchr
	pushl	0
	pushc	1
	add
	popl	0
	jmp	loop_cond

print:
	asf	0
	pushl	-3
	pushc	1
	add
	popr
	rsf
	ret
