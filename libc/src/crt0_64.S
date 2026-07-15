.extern main

.globl _start
_start:
	mov (%rsp), %rdi
	mov 8(%rsp), %rsi

	call main
	
	# Exit
	mov $3, %rax

	# FIXME: Use main()'s return value.
	xor %rdi, %rdi

	syscall
