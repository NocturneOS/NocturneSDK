#include <stddef.h>
#include <time.h>

static struct tm tm_buf;

struct tm *gmtime(const time_t *timer) {
  if (!timer) {
    return NULL;
  }
  time_t t = *timer;
  // Simple approximation - just set seconds
  tm_buf.tm_sec = t % 60;
  t /= 60;
  tm_buf.tm_min = t % 60;
  t /= 60;
  tm_buf.tm_hour = t % 24;
  // Very rough defaults for other fields
  tm_buf.tm_mday = 1;
  tm_buf.tm_mon = 0;
  tm_buf.tm_year = 70;
  tm_buf.tm_wday = 0;
  tm_buf.tm_yday = 0;
  tm_buf.tm_isdst = 0;
  return &tm_buf;
}

struct tm *localtime(const time_t *timer) { return gmtime(timer); }

time_t mktime(struct tm *tm) {
  if (!tm) {
    return (time_t)-1;
  }
  // Very rough calculation
  time_t t = 0;
  t += tm->tm_sec;
  t += tm->tm_min * 60;
  t += tm->tm_hour * 3600;
  t += tm->tm_mday * 86400;
  t += tm->tm_mon * 30 * 86400;
  t += (tm->tm_year - 70) * 365 * 86400;
  return t;
}
