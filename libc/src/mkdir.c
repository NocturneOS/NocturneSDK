#include <errno.h>
#include <sys/stat.h>

int mkdir(const char *path, mode_t mode) {
  (void)path;
  (void)mode;

  errno = -ENOSYS;

  return -1;
}
