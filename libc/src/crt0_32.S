.extern main

.globl _start
_start:
	call main
	
	# Exitcode in EAX
	mov %eax, %ebx
	mov $3, %eax

	int $0x80
