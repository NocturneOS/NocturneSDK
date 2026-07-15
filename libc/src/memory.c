#include "syscall.h"
#include "string.h"
#include "memory.h"

void* sbrk(ssize_t increment) {
    return (void*)_syscall1(SYS_SBRK, increment);
}