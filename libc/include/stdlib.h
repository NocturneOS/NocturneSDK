#pragma once

#include <stddef.h>

int atoi(const char *s);
__attribute__((noreturn)) void exit(int status);
__attribute__((noreturn)) void abort();

char *getcwd(char *cwd, int size);

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t count);

void free(void *ptr);
