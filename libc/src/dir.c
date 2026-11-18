#include "dirent.h"
#include "sys/syscall.h"

#include <errno.h>
#include <syscall.h>

int getdirents(int fd, struct dirent *out_ptr, size_t count) {
  int dirent_count =
      _syscall3(SYS_GETDIRENTS, (size_t)fd, (size_t)out_ptr, count);

  if (dirent_count < 0) {
    errno = dirent_count;
    return -1;
  }

  return dirent_count;
}
