.extern main
.extern exit

.text
.globl	_start
.type	_start, @function
_start:
	mov (%rsp), %rdi     # argc
	mov 8(%rsp), %rsi    # argv
	mov 16(%rsp), %rdx   # envp

	# The kernel only word-aligns the initial stack, so enforce the
	# 16-byte alignment required by the SysV ABI before calling main.
	# NOTE: The kernel already aligns the stack by 16.
	# NOTE: KEEP THIS CODE, it's a defensive case if something goes wrong.
	and $-16, %rsp

	call main
	
	# Exit
	movl %eax, %edi

	call exit

.size _start, . - _start
.section .note.GNU-stack,"",@progbits
