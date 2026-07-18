#pragma once

#define NULL (0)

#define _INLINE static inline __attribute__((always_inline))

#define KB (1 << 10)
#define MB (1 << 20)
#define GB (1 << 30)

#define ALIGN(value, align) ((value) + ((-(value)) & ((align) - 1)))
#define IS_ALIGNED(value, align) ((value) % (align) == 0)

#include <stdint.h>

#if defined __x86_64
typedef uint64_t size_t;
typedef int64_t ssize_t;
#else
typedef uint32_t size_t;
typedef int32_t ssize_t;

#endif

typedef int32_t wchar_t;

typedef ssize_t ptrdiff_t;

