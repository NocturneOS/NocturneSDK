#include <errno.h>
#include <unistd.h>

int rmdir(const char *path) {
  (void)path;

  errno = -ENOSYS;

  return -1;
}
