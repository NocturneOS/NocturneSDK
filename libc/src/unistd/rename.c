#include <errno.h>
#include <stdio.h>

int rename(const char *old_path, const char *new_path) {
  (void)old_path;
  (void)new_path;

  errno = -ENOSYS;

  return -1;
}
