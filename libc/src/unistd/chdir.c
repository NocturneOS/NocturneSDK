#include "sys/syscall.h"
#include <errno.h>
#include <stddef.h>
#include <syscall.h>

int chdir(const char* path) {
    int status = _syscall1(SYS_CHDIR, (size_t)path);

    if(status < 0) {
        errno = -status;
        return -1;
    }

    return status;
}