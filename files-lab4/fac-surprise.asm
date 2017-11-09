  # fac.asm
  # This file written 2017 by LIN XIANYING
  # Copyright abandoned - this file is in the public domain.


.global main
	.text
	
main:
addi $a0, $0, 5 # a0 = n
addi $v0, $0, 1 # result = v0 = 1
addi $a1, $0, 0		

loop:
	beq  $a0, 0, stop	
	mul  $v0, $v0, $a0 
	add  $a0, $a0, -1
	beq  $0, $0, loop
	
stop:
	beq $0, $0, stop			
	
	
	
