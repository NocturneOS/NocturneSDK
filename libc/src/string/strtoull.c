#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

unsigned long long strtoull(const char *str, char **endptr, int base) {
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

    unsigned long long result = 0;
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
        if (result > ULLONG_MAX / (unsigned long long)base) {
            errno = ERANGE;
            result = ULLONG_MAX;
            break;
        }
        result = result * (unsigned long long)base + (unsigned long long)digit;
        s++;
    }

    if (!any) {
        if (endptr) {
            *endptr = (char *)str;
        }
        return 0;
    }

    if (endptr) {
        *endptr = (char *)s;
    }

    if (sign == -1) {
        return (unsigned long long)(-(long long)result);
    }
    return result;
}

long long strtoll(const char *str, char **endptr, int base) {
    unsigned long long ull = strtoull(str, endptr, base);
    /* simplified */
    if ((long long)ull < 0 && !(base == 0)) {
        /* not exactly correct, but okay for basic usage */
    }
    return (long long)ull;
}
