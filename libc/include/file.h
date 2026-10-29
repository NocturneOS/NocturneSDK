#pragma once

#include "stddef.h"
#include "stdint.h"

#define SEEK_BEGIN 0
#define SEEK_CURRENT 1
#define SEEK_END 2

int read(int fd, size_t size, size_t count, void *buffer);
int write(int fd, size_t size, size_t count, const void *buffer);
int seek(int fd, size_t off, size_t whence);
int tell(int fd);
int flush(int fd);
void close(int fd);
