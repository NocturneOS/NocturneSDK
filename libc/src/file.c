#include "errno.h"
#include "syscall.h"
#include "unistd.h"

int open(const char *filename, size_t mode, ...) {
  int fd = _syscall2(SYS_OPEN, (size_t)filename, mode);

  if (fd < 0) {
    errno = fd;

    return -1;
  }

  return fd;
}

int seek(int fd, size_t off, size_t whence) {
  int result = _syscall3(SYS_SEEK, fd, off, whence);

  if (result < 0) {
    errno = result;

    return -1;
  }

  return result;
}

int tell(int fd) {
  int value = 0;
  _syscall2(SYS_TELL, fd, (size_t)&value);

  return value;
}

ssize_t read(int fd, void *buffer, size_t byte_count) {
  int result = (int)_syscall3(SYS_READ, (size_t)fd, (size_t)buffer, byte_count);

  if (result < 0) {
    errno = result;

    return 0;
  }

  return result;
}

ssize_t write(int fd, const void *buffer, size_t byte_count) {
  int result =
      (int)_syscall3(SYS_WRITE, (size_t)fd, (size_t)buffer, byte_count);

  if (result < 0) {
    errno = result;

    return 0;
  }

  return result;
}

int flush(int fd) { return _syscall1(SYS_FLUSH, (size_t)fd); }

int close(int fd) {
  _syscall1(SYS_CLOSE, (size_t)fd);
  return 0;
}
