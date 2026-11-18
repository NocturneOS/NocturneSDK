#pragma once

#include <stddef.h>
#include <sys/types.h>

void *sbrk(ssize_t increment);
int usleep(size_t usec);

int close(int fd);

int unlink(const char *path);
int rmdir(const char *path);

ssize_t read(int fd, void *buffer, size_t byte_count);
ssize_t write(int fd, const void *buffer, size_t byte_count);
int seek(int fd, size_t off, size_t whence);
off_t lseek(int fd, off_t offset, int whence);
int tell(int fd);
int flush(int fd);

int chdir(const char* path);

/* lseek() / fseek() whence values. */
#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif
