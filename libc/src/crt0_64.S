.extern main
.extern exit

.text
.globl	_start
.type	_start, @function
_start:
	mov (%rsp), %rdi     # argc
	mov 8(%rsp), %rsi    # argv
	mov 16(%rsp), %rdx   # envp

	call main
	
	# Exit
	movl %eax, %edi

	call exit

.size _start, . - _start
.section .note.GNU-stack,"",@progbits
