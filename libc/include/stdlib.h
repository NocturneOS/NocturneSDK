#pragma once

#include <stddef.h>

long strtol(const char *str, char **endptr, int base);
unsigned long strtoul(const char *str, char **endptr, int base);
long long strtoll(const char *str, char **endptr, int base);
unsigned long long strtoull(const char *str, char **endptr, int base);
double strtod(const char *str, char **endptr);

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *));

int atoi(const char *s);
long atol(const char *s);
long long atoll(const char *s);
double atof(const char *s);
int abs(int j);
long labs(long j);
long long llabs(long long j);

__attribute__((noreturn)) void exit(int status);
__attribute__((noreturn)) void abort();

char *getcwd(char *cwd, int size);

void free(void *ptr);

__attribute__((alloc_size(1), malloc(free))) void *malloc(long unsigned size);
__attribute__((alloc_size(1, 2), malloc(free))) void *calloc(size_t nmemb,
                                                             size_t count);
void *realloc(void *ptr, long unsigned new_size);
