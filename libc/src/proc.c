#include "sys/syscall.h"
#include <proc.h>

#include <errno.h>
#include <syscall.h>

#include <sys/types.h>

int proc_run(const char *path, const char **argv, size_t argc, size_t flags) {
  int result = _syscall4(SYS_PROCRUN, (size_t)path, (size_t)argv, argc, flags);

  if (result < 0) {
    errno = -result;
    return -1;
  }

  return result;
}

int waitpid(pid_t pid) {
  int result = _syscall1(SYS_WAITPID, pid);

  if (result < 0) {
    errno = -result;
    return -1;
  }

  return result;
}
