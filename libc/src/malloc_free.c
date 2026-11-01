#include "string.h"
#include "syscall.h"

// TODO: Make a real heap implementation with alignment support.

void *malloc(long unsigned size) {
  size_t ptr = _syscall1(SYS_MREQUEST, (size_t)size);
  // size_t ptr = _syscall1(SYS_SBRK, (size_t)size);

  return (void *)ptr;
}

void free(void *ptr) {
  _syscall1(SYS_MFREE, (size_t)ptr);
  (void)ptr;
}

void *realloc(void *ptr, long unsigned new_size) {
  if (ptr == NULL) {
    return malloc(new_size);
  }

  if (new_size == 0) {
    free(ptr);
    return NULL;
  }

  void *n = malloc(new_size);

  if (n == NULL) {
    return NULL;
  }

  memcpy(n, ptr, new_size);

  free(ptr);

  return n;
}
