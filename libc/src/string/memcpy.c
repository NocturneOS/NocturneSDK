// #include <stddef.h>
#include "string.h"

/*
void *memcpy(void *restrict destination, const void *restrict source,
             long unsigned int n) {
  size_t *tmp_dest = (size_t *)destination;
  size_t *tmp_src = (size_t *)source;
  size_t len = n / sizeof(size_t);
  size_t i = 0;
  size_t tail = n & (sizeof(size_t) - 1);

  for (; i < len; i++) {
    *tmp_dest++ = *tmp_src++;
  }

  if (tail) {
    char *dest = (char *)destination;
    const char *src = (const char *)source;

    for (i = n - tail; i < n; i++) {
      dest[i] = src[i];
    }
  }

  return destination;
}
*/
/*
void *memcpy(void *restrict destination, const void *restrict source,
             long unsigned int n) {
  unsigned char *d = destination;
  unsigned char *s = source;

  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return destination;
}
*/

void *memcpy(void *dest, const void *src, size_t len) {
  char *d = dest;
  const char *s = src;
  while (len--)
    *d++ = *s++;
  return dest;
}
