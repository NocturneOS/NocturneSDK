#include <syscall.h>
#include <unistd.h>

int usleep(size_t usec) {
  unsigned long long nanos = usec * 1000;

  unsigned int high_part = nanos >> 32;
  unsigned int low_part = nanos & ((1ull << 32) - 1);

  _syscall2(SYS_NANOSLEEP, high_part, low_part);

  return 0;
}
