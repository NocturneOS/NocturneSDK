.extern main
.extern exit

.text
.globl	_start
.type	_start, @function
_start:
	# The kernel pushes ARGC, ARGV and ENVP at the top of the stack:
	# [esp] = argc, [esp+4] = argv, [esp+8] = envp.
	mov (%esp), %eax
	mov 4(%esp), %ecx
	mov 8(%esp), %edx

	# Kernel word-aligns the initial stack, so enforce the 16-byte alignment required by the i386 ABI,
	# then pass the arguments to main() using the cdecl convention.
	# NOTE: The kernel already aligns the stack by 16.
	# NOTE: KEEP THIS CODE, it's a defensive case if something goes wrong.
	and $-16, %esp
	sub $4, %esp         # padding, keeps the call site 16-byte aligned
	push %edx            # envp
	push %ecx            # argv
	push %eax            # argc
	call main

	# esp points at the argc slot here and is 16-byte aligned, so reuse
	# it as exit()'s cdecl argument.
	mov %eax, (%esp)
	call exit

	ud2

.size _start, . - _start
.section .note.GNU-stack,"",@progbits
