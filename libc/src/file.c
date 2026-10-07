#include "file.h"
#include "syscall.h"

int open(const char *filename, size_t mode) {
  int fd = 0;
  _syscall3(SYS_OPEN, (size_t)filename, mode, (size_t)&fd);

  return fd;
}

void seek(int fd, size_t off, size_t whence) {
  _syscall3(SYS_SEEK, fd, off, whence);
}

int tell(int fd) {
  int value = 0;
  _syscall2(SYS_TELL, fd, (size_t)&value);

  return value;
}

int read(int fd, size_t size, size_t count, void *buffer) {
  return (int)_syscall3(SYS_READ, (size_t)fd, (size_t)buffer, size * count);
}

int write(int fd, size_t size, size_t count, const void *buffer) {
  return (int)_syscall3(SYS_WRITE, (size_t)fd, (size_t)buffer, size * count);
}

int flush(int fd) { return _syscall1(SYS_FLUSH, (size_t)fd); }

void close(int fd) { _syscall1(SYS_CLOSE, (size_t)fd); }
