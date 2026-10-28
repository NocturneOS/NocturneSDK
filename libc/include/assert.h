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

#if (defined __USE_ISOC11 &&                                                   \
     (!defined __STDC_VERSION__ ||                                             \
      __STDC_VERSION__ <= 201710L && !defined __cplusplus))
#undef static_assert
#define static_assert _Static_assert
#endif

inline static void __assert_fail(const char *assertion, const char *file,
                                 unsigned int line, const char *function) {
  // TODO: Use stderr and fprintf.
  printf("assert(): assertion failed `%s` (%s at %u:%s)", assertion, file, line,
         function);

  __builtin_abort();
}
