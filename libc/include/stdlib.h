#pragma once

#include <stddef.h>

int atoi(const char *s);
__attribute__((noreturn)) void exit(int status);
__attribute__((noreturn)) void abort();

char *getcwd(char *cwd, int size);

void free(void *ptr);

__attribute__((alloc_size(1), malloc(free))) void *malloc(size_t size);
__attribute__((alloc_size(1, 2), malloc(free))) void *calloc(size_t nmemb,
                                                             size_t count);
