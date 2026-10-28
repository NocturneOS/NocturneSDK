#include <string.h>

char *strrchr(const char *s, int c) {
    const char *last = NULL;
    char cc = (char)c;
    while (*s) {
        if (*s == cc) {
            last = s;
        }
        s++;
    }
    if (cc == '\0') {
        return (char *)s;
    }
    return (char *)last;
}
