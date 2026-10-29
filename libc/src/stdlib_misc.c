#include <stdlib.h>

int abs(int j) {
    return j < 0 ? -j : j;
}

long labs(long j) {
    return j < 0 ? -j : j;
}

long long llabs(long long j) {
    return j < 0 ? -j : j;
}

long atol(const char *s) {
    return (long)strtol(s, (char **)0, 10);
}

long long atoll(const char *s) {
    return (long long)strtoll(s, (char **)0, 10);
}

double atof(const char *s) {
    return strtod(s, (char **)0);
}
