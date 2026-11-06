#pragma once

#include <stddef.h>
#include <sys/types.h>

void *sbrk(ssize_t increment);
int usleep(size_t usec);

int close(int fd);

ssize_t read(int fd, void *buffer, size_t byte_count);
ssize_t write(int fd, const void *buffer, size_t byte_count);
int seek(int fd, size_t off, size_t whence);
int tell(int fd);
int flush(int fd);
