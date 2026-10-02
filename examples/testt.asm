//
// version
//
	.vers	4

//
// execution framework
//
__start:
	call	_main
	call	_exit
__stop:
	jmp	__stop

//
// Integer readInteger()
//
_readInteger:
	asf	0
	rdint
	popr
	rsf
	ret

//
// void writeInteger(Integer)
//
_writeInteger:
	asf	0
	pushl	-3
	wrint
	rsf
	ret

//
// Character readCharacter()
//
_readCharacter:
	asf	0
	rdchr
	popr
	rsf
	ret

//
// void writeCharacter(Character)
//
_writeCharacter:
	asf	0
	pushl	-3
	wrchr
	rsf
	ret

//
// Integer char2int(Character)
//
_char2int:
	asf	0
	pushl	-3
	popr
	rsf
	ret

//
// Character int2char(Integer)
//
_int2char:
	asf	0
	pushl	-3
	popr
	rsf
	ret

//
// void exit()
//
_exit:
	asf	0
	halt
	rsf
	ret

//
// void main()
//
_main:
	asf	2
	pushc	1
	popl	1
	pushc	1000
	popg	0
	jmp	__2
__1:
	pushc	105
	call	_writeCharacter
	drop	1
	pushc	110
	call	_writeCharacter
	drop	1
	pushc	115
	call	_writeCharacter
	drop	1
	pushc	101
	call	_writeCharacter
	drop	1
	pushc	114
	call	_writeCharacter
	drop	1
	pushc	116
	call	_writeCharacter
	drop	1
	pushc	32
	call	_writeCharacter
	drop	1
	pushc	97
	call	_writeCharacter
	drop	1
	pushc	32
	call	_writeCharacter
	drop	1
	pushc	110
	call	_writeCharacter
	drop	1
	pushc	117
	call	_writeCharacter
	drop	1
	pushc	109
	call	_writeCharacter
	drop	1
	pushc	98
	call	_writeCharacter
	drop	1
	pushc	101
	call	_writeCharacter
	drop	1
	pushc	114
	call	_writeCharacter
	drop	1
	pushc	58
	call	_writeCharacter
	drop	1
	pushc	32
	call	_writeCharacter
	drop	1
	call	_readInteger
	pushr
	popl	0
	pushl	0
	pushc	100
	gt
	brf	__4
	pushc	0
	popl	1
	jmp	__5
__4:
	pushc	10
	call	_writeCharacter
	drop	1
	pushc	121
	call	_writeCharacter
	drop	1
	pushc	111
	call	_writeCharacter
	drop	1
	pushc	117
	call	_writeCharacter
	drop	1
	pushc	114
	call	_writeCharacter
	drop	1
	pushc	32
	call	_writeCharacter
	drop	1
	pushc	110
	call	_writeCharacter
	drop	1
	pushc	117
	call	_writeCharacter
	drop	1
	pushc	109
	call	_writeCharacter
	drop	1
	pushc	98
	call	_writeCharacter
	drop	1
	pushc	101
	call	_writeCharacter
	drop	1
	pushc	114
	call	_writeCharacter
	drop	1
	pushc	58
	call	_writeCharacter
	drop	1
	pushc	32
	call	_writeCharacter
	drop	1
	pushl	0
	call	_writeInteger
	drop	1
	pushc	10
	call	_writeCharacter
	drop	1
__5:
__2:
	pushl	1
	pushc	0
	ne
	brt	__1
__3:
	jmp	__7
__6:
	pushc	100
	call	_writeCharacter
	drop	1
	pushc	111
	call	_writeCharacter
	drop	1
	pushc	119
	call	_writeCharacter
	drop	1
	pushc	110
	call	_writeCharacter
	drop	1
	pushc	32
	call	_writeCharacter
	drop	1
	pushc	116
	call	_writeCharacter
	drop	1
	pushc	111
	call	_writeCharacter
	drop	1
	pushc	58
	call	_writeCharacter
	drop	1
	pushc	32
	call	_writeCharacter
	drop	1
	pushg	0
	call	_writeInteger
	drop	1
	pushc	10
	call	_writeCharacter
	drop	1
	pushg	0
	pushc	2
	sub
	popg	0
__7:
	pushg	0
	pushc	0
	gt
	brt	__6
__8:
__0:
	rsf
	ret
