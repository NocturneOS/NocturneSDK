#pragma once

#include <stddef.h>
#include <sys/types.h>

#define O_RDONLY 1
#define O_WRONLY 2
#define O_RDWR (O_RDONLY | O_WRONLY)
#define O_CREAT 4
#define O_APPEND 8
#define O_TRUNC 16
#define O_DIRECTORY 32

int open(const char *filename, size_t mode, ...);
int creat(const char *__file, mode_t __mode);