#include "stdlib.h"
#include "syscall.h"

char *getcwd(char *cwd, int size) {
  size_t result = _syscall2(SYS_GETCWD, (size_t)cwd, size);

  return (char *)result;
}
