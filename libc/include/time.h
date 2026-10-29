#pragma once

#include <stddef.h>
#include <stdint.h>

typedef uint64_t time_t;

#include <sys/types.h>

typedef int32_t suseconds_t;
typedef uint32_t useconds_t;

struct tm {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
};

size_t strftime(char *restrict s, size_t max, const char *restrict format,
                const struct tm *restrict tm);
