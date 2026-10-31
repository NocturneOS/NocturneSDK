#include <stdlib.h>

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size,
              int (*compar)(const void *, const void *)) {
    if (nmemb == 0 || size == 0) {
        return NULL;
    }

    size_t left = 0;
    size_t right = nmemb;

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        const void *midptr = (const char *)base + mid * size;
        int cmp = compar(key, midptr);
        if (cmp == 0) {
            return (void *)midptr;
        } else if (cmp < 0) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return NULL;
}
