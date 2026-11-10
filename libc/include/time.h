#pragma once

#include <common.h>
#include <stddef.h>
#include <stdint.h>

#include <sys/types.h>

#define CLOCKS_PER_SEC 1000

typedef uint64_t time_t;

typedef int32_t suseconds_t;
typedef uint32_t useconds_t;

typedef size_t clock_t;

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

struct timespec {
  time_t tv_sec;
  long int tv_nsec;
};

clock_t clock(void);

struct tm *gmtime(const time_t *timer);
struct tm *localtime(const time_t *timer);
time_t mktime(struct tm *tm);
time_t time(time_t *tloc);

size_t strftime(char *__restrict s, size_t max, const char *__restrict format,
                const struct tm *__restrict tm);
