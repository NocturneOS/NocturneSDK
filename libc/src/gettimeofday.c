#include <assert.h>

#include <sys/time.h>
#include <time.h>

#include <syscall.h>

int gettimeofday(struct timeval *restrict tv, void *restrict tz) {
  assert(tv != NULL);

  int result = _syscall2(SYS_GETTIMEOFDAY, (size_t)tv, (size_t)tz);

  return result;
}
