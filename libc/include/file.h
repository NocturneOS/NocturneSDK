#pragma once

#include "stdint.h"
#include "stddef.h"

#define O_READ 1
#define O_WRITE 2
#define O_CREATE 4
#define O_APPEND 8
#define O_TRUNC 16
#define O_DIR 32

#define SEEK_BEGIN 0
#define SEEK_CURRENT 1
#define SEEK_END 2

int open(const char* filename, size_t mode);
int read(int fd, size_t size, size_t count, void* buffer);
int write(int fd, size_t size, size_t count, const void* buffer);
void seek(int fd, size_t off, size_t whence);
int tell(int fd);
void close(int fd);
