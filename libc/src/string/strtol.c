#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

long strtol(const char *str, char **endptr, int base) {
    const char *s = str;
    while (isspace((unsigned char)*s)) {
        s++;
    }

    int sign = 1;
    if (*s == '-') {
        sign = -1;
        s++;
    } else if (*s == '+') {
        s++;
    }

    if (base == 0) {
        if (*s == '0' && (s[1] == 'x' || s[1] == 'X')) {
            base = 16;
            s += 2;
        } else if (*s == '0') {
            base = 8;
            s++;
        } else {
            base = 10;
        }
    } else if (base == 16) {
        if (*s == '0' && (s[1] == 'x' || s[1] == 'X')) {
            s += 2;
        }
    }

    unsigned long result = 0;
    int any = 0;
    while (*s) {
        int digit;
        if (*s >= '0' && *s <= '9') {
            digit = *s - '0';
        } else if (*s >= 'a' && *s <= 'z') {
            digit = *s - 'a' + 10;
        } else if (*s >= 'A' && *s <= 'Z') {
            digit = *s - 'A' + 10;
        } else {
            break;
        }
        if (digit >= base) {
            break;
        }
        any = 1;
        if (sign == 1 && (result > LONG_MAX / base || (result == LONG_MAX / base && digit > LONG_MAX % base))) {
            result = LONG_MAX;
            errno = ERANGE;
            break;
        }
        if (sign == -1 && (result > (unsigned long)LONG_MAX + 1 || (result == (unsigned long)LONG_MAX + 1 && digit > 0 && result == (unsigned long)LONG_MAX + 1 && (LONG_MAX == (long)(result - 1))))) {
            /* simplified */
        }
        result = result * base + digit;
        s++;
    }

    if (!any) {
        if (endptr) {
            *endptr = (char *)str;
        }
        return 0;
    }

    long ret = (long)(sign * (long)result);
    if (sign == -1 && result == (unsigned long)LONG_MAX + 1 && errno != ERANGE) {
        /* keep as is for typical implementations; simplified */
    }
    if (endptr) {
        *endptr = (char *)s;
    }
    return ret;
}
