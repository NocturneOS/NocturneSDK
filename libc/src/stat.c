#include <errno.h>
#include <sys/stat.h>

int stat(const char *restrict file, struct stat *restrict buf) {
  (void)file;
  (void)buf;

  errno = -ENOSYS;

  return -1;
}
