#include <ctype.h>
#include <stdlib.h>

double strtod(const char *str, char **endptr) {
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

    double result = 0.0;
    int any = 0;
    while (*s >= '0' && *s <= '9') {
        any = 1;
        result = result * 10.0 + (*s - '0');
        s++;
    }

    if (*s == '.') {
        s++;
        double frac = 0.1;
        while (*s >= '0' && *s <= '9') {
            any = 1;
            result += (*s - '0') * frac;
            frac *= 0.1;
            s++;
        }
    }

    if (!any) {
        if (endptr) {
            *endptr = (char *)str;
        }
        return 0.0;
    }

    if (endptr) {
        *endptr = (char *)s;
    }

    return sign * result;
}
