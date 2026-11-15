#include "string.h"
#include "common.h"

/* size_t stores may alias any object, just like char stores do. */
#if defined(__GNUC__)
typedef size_t __attribute__((may_alias)) memcpy_word;
#else
typedef size_t memcpy_word;
#endif

// Avoid replacing memcpy's code with call to itself
__LIBC_NO_LOOP_DISTRIBUTE
void *memcpy(void *restrict destination, const void *restrict source,
             long unsigned int n) {
  unsigned char *dest = destination;
  const unsigned char *src = source;

  // If both pointers are machine-word aligned, copy whole words first.
  // Otherwise fall back to a byte copy.
  if ((((uintptr_t)dest | (uintptr_t)src) & (sizeof(size_t) - 1)) == 0) {
    memcpy_word *word_dest = (memcpy_word *)dest;
    const memcpy_word *word_src = (const memcpy_word *)src;
    size_t words = n / sizeof(size_t);

    while (words--) {
      *word_dest++ = *word_src++;
    }

    dest = (unsigned char *)word_dest;
    src = (const unsigned char *)word_src;
    n &= sizeof(size_t) - 1;
  }

  while (n--) {
    *dest++ = *src++;
  }

  return destination;
}
