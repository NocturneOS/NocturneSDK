#include <string.h>

size_t strcspn(const char *s, const char *reject) {
    size_t count = 0;
    while (s[count]) {
        const char *r = reject;
        while (*r) {
            if (s[count] == *r) {
                return count;
            }
            r++;
        }
        count++;
    }
    return count;
}
