#pragma once

#define __NOCTURNE__

// C++ doesn't have a `restrict` keyword, so use `__restrict` internally.
// THe `__restrict` keyword unfolds into nothing in C++, but unfolds into `restrict` in C.
#ifdef __cplusplus
#define __restrict
#else
#define __restrict restrict
#endif

/*
 * GCC's loop distribution / strlen optimizations can replace loops inside a
 * library implementation with calls to the very function being implemented
 * (e.g. memcpy -> memcpy), causing infinite recursion. Apply this attribute
 * to such implementations.
 */
#if defined(__GNUC__) && !defined(__clang__)
#define __LIBC_NO_LOOP_DISTRIBUTE                                          \
    __attribute__((optimize("no-tree-loop-distribute-patterns")))
#else
#define __LIBC_NO_LOOP_DISTRIBUTE
#endif
