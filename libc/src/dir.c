#include "dirent.h"
#include "sys/syscall.h"

#include <syscall.h>

int getdirents(int fd, struct dirent *out_ptr, size_t count) {
  int dirent_count =
      _syscall3(SYS_GETDIRENTS, (size_t)fd, (size_t)out_ptr, count);

  return dirent_count;
}
