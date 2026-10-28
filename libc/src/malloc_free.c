#include "string.h"
#include "syscall.h"

// TODO: Make a real heap implementation with alignment support.

void *malloc(int size) {
  size_t ptr = _syscall1(SYS_MREQUEST, (size_t)size);
  // size_t ptr = _syscall1(SYS_SBRK, (size_t)size);

  return (void *)ptr;
}

void free(void *ptr) {
  _syscall1(SYS_MFREE, (size_t)ptr);
  (void)ptr;
}
