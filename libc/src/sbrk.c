#include "string.h"
#include "syscall.h"

#include <sys/types.h>

void *sbrk(ssize_t increment) { return (void *)_syscall1(SYS_SBRK, increment); }
