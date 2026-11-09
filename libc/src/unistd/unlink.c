#include <errno.h>
#include <unistd.h>

int unlink(const char *path) {
  (void)path;

  errno = -ENOSYS;

  return -1;
}
