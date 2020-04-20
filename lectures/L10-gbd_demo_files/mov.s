##########
# mov.s for use in CSE351 Lec 10
#
# Intended for use with a gdb demo:
# gcc -o mov mov.s
##########

	.text
	.globl	main
	.type	main, @function
main:
	
	movq	$0x1020304050607080, %rax  # put non-zero junk in bytes of %rax,
	movq	%rax, %rbx		   #   %rbx,
	movq	%rax, %rcx		   #   and %rcx

	movzbw	%al, %bx		   # pull lowest byte into %bx (16 bits) and zero-extend
					   #   --> %rbx = 0x1020304050600080

	movzbq	%al, %rbx		   # pull lowest byte into %rbx and zero-extend
					   #   --> %rbx = 0x80 even though MSB=1

	leaq	gv, %rax			   # get address of global variable data
	movsbl	4(%rax), %ecx		   # pull byte 0x80 into %ecx and sign-extend
					   #   --> %rcx = 0xFFFFFF80 because 32-bit values
					   #       placed in a x86-64 register zero out
					   #       upper 32 bits
	ret
	.size	main, .-main
	.globl	gv
	.data
	.align 8
	.type	gv, @object
	.size	gv, 8
gv:	
	.quad	0x7778798081828384

