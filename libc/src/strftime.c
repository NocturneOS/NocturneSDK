#include "time.h"
#include "string.h"

size_t strftime(char *restrict s, size_t max, const char *restrict format,
                const struct tm *restrict tm) {
    if (!s || !format || !tm || max == 0) {
        return 0;
    }

    size_t written = 0;
    const char *p = format;
    while (*p && written < max - 1) {
        if (*p != '%') {
            s[written++] = *p++;
            continue;
        }
        p++;
        if (*p == '\0') {
            break;
        }
        if (*p == '%') {
            s[written++] = '%';
            p++;
            continue;
        } else if (*p == 'Y') {
            // Write year (simplified as 1900 + tm_year)
            int year = tm->tm_year + 1900;
            char buf[16];
            int i = 0;
            if (year == 0) {
                buf[i++] = '0';
            } else {
                if (year < 0) {
                    year = -year;
                    if (written < max - 1) s[written++] = '-';
                }
                int tmp[16];
                int ti = 0;
                while (year > 0 && ti < 15) {
                    tmp[ti++] = year % 10;
                    year /= 10;
                }
                while (ti > 0 && written < max - 1) {
                    buf[i++] = '0' + tmp[--ti];
                }
            }
            buf[i] = '\0';
            for (int j = 0; buf[j] && written < max - 1; j++) {
                s[written++] = buf[j];
            }
            p++;
            continue;
        } else if (*p == 'y') {
            int year = (tm->tm_year % 100 + 100) % 100;
            if (written < max - 1) s[written++] = '0' + year / 10;
            if (written < max - 1) s[written++] = '0' + year % 10;
            p++;
            continue;
        } else if (*p == 'm') {
            int mon = tm->tm_mon + 1;
            if (written < max - 1) s[written++] = '0' + mon / 10;
            if (written < max - 1) s[written++] = '0' + mon % 10;
            p++;
            continue;
        } else if (*p == 'd') {
            int day = tm->tm_mday;
            if (written < max - 1) s[written++] = '0' + day / 10;
            if (written < max - 1) s[written++] = '0' + day % 10;
            p++;
            continue;
        } else if (*p == 'H') {
            int hour = tm->tm_hour;
            if (written < max - 1) s[written++] = '0' + hour / 10;
            if (written < max - 1) s[written++] = '0' + hour % 10;
            p++;
            continue;
        } else if (*p == 'M') {
            int min = tm->tm_min;
            if (written < max - 1) s[written++] = '0' + min / 10;
            if (written < max - 1) s[written++] = '0' + min % 10;
            p++;
            continue;
        } else if (*p == 'S') {
            int sec = tm->tm_sec;
            if (written < max - 1) s[written++] = '0' + sec / 10;
            if (written < max - 1) s[written++] = '0' + sec % 10;
            p++;
            continue;
        } else {
            s[written++] = '%';
            if (written < max - 1) s[written++] = *p;
            p++;
            continue;
        }
    }
    s[written] = '\0';
    return written;
}
