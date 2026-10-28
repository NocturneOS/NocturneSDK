#pragma once

#include "stdio.h"
#include "stdlib.h"

#define __ASSERT_FUNCTION __extension__ __PRETTY_FUNCTION__

#define assert(expr)                                                           \
  ((void)sizeof((expr) ? 1 : 0), __extension__({                               \
     if (expr)                                                                 \
       ; /* empty */                                                           \
     else                                                                      \
       __assert_fail(#expr, __FILE__, __LINE__, __ASSERT_FUNCTION);            \
   }))

#if !defined(__cplusplus)
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
/* C11 and later: static_assert is a keyword, but define macro for compatibility */
#ifndef static_assert
#define static_assert _Static_assert
#endif
#endif
#endif

inline static void __assert_fail(const char *assertion, const char *file,
                                 unsigned int line, const char *function) {
  // TODO: Use stderr and fprintf.
  printf("assert(): assertion failed `%s` (%s at %u:%s)", assertion, file, line,
         function);

  __builtin_abort();
}
