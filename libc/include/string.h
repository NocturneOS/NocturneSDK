#pragma once

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void *memcpy(void *restrict destination, const void *restrict source,
             long unsigned int n);
void *memset(void *ptr, int value, long unsigned num);
void *memmove(void *dest, const void *src, long unsigned count);
int memcmp(const void *s1, const void *s2, long unsigned n);
void *memchr(const void *s, int c, size_t n);

char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, long unsigned int n);
long unsigned int strlen(const char *str);
size_t struntil(const char *str, const char find);
int strcmp(const char *s1, const char *s2);
long unsigned int strspn(const char *s, const char *accept);
int strncmp(const char *s1, const char *s2, long unsigned int num);
char *strtok(char *s, const char *delim);
char *strcat(char *destination, const char *source);
void substr(char * /*restrict*/ dest, const char * /*restrict*/ source,
            int from, int length);
char *strchr(const char *_s, int _c);
void strtolower(char *as);
void strtoupper(char *as);
void strver(char *str);
size_t itoa(int32_t n, char *buffer);
size_t itou(size_t n, char *buffer);
size_t itoh(size_t i, char *buffer);
size_t strcount(const char *string, char character);
char *strstr(const char *haystack, const char *needle);
unsigned long strtoul(const char *str, char **endptr, int base);
long strtol(const char *str, char **endptr, int base);
unsigned long long strtoull(const char *str, char **endptr, int base);
long long strtoll(const char *str, char **endptr, int base);
double strtod(const char *str, char **endptr);
char *strrchr(const char *s, int c);
size_t strcspn(const char *s, const char *reject);

char* strerror(int errnum);
