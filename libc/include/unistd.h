#pragma once

#include <stddef.h>
#include <sys/types.h>

void *sbrk(ssize_t increment);
int usleep(size_t usec);
