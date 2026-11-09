.extern main
.extern exit

.text
.globl	_start
.type	_start, @function
_start:
	# ARGC, ARGV and ENVP are already pushed to the stack by the kernel. Just call main().

	call main
	
	# Exitcode in EAX, call exit(code).
	push %eax
	call exit

	ud2

.size _start, . - _start
.section .note.GNU-stack,"",@progbits
