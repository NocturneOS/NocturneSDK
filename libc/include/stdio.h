#pragma once

#include <stddef.h>
#include <stdbool.h>

#define EOF (-1)

#define FD_STDIN 0
#define FD_STDOUT 1
#define FD_STDERR 2

typedef struct {
  int __fd;

  bool __last_read_end;
} FILE;

extern FILE *stderr;
extern FILE *stdout;
extern FILE *stdin;

int puts(const char *text);
int putchar(int ch);

__attribute__((format(printf, 1, 2))) int printf(const char *text, ...);
__attribute__((format(printf, 2, 3))) int fprintf(FILE *stream,
                                                  const char *text, ...);

void fclose(FILE *stream);

__attribute__((malloc(fclose, 1))) FILE *fopen(const char *filename,
                                               const char *mode);
long unsigned int fread(void *buffer, long unsigned int size, long unsigned int count, FILE *stream);
long unsigned int fwrite(const void *buffer, long unsigned int size, long unsigned int count, FILE *stream);
int fseek(FILE *stream, long offset, int origin);
long int ftell(FILE *stream);

int feof(FILE* stream);