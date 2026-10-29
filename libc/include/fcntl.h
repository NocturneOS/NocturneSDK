#pragma once

#include <stddef.h>

#define O_READ 1
#define O_WRITE 2
#define O_CREATE 4
#define O_APPEND 8
#define O_TRUNC 16
#define O_DIR 32

int open(const char *filename, size_t mode);
