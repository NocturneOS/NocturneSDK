#pragma once

#include <stdbool.h>
#include <stddef.h>

// Include sprintf.h for vsnprintf
#include "sprintf.h"
#include <stdarg.h>

#define EOF (-1)

#define FD_STDIN 0
#define FD_STDOUT 1
#define FD_STDERR 2

typedef struct {
  int __fd;

  size_t __mode;

  bool __last_read_end;
} FILE;

extern FILE *stderr;
extern FILE *stdout;
extern FILE *stdin;

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

int puts(const char *text);
int putchar(int ch);

__attribute__((format(printf, 1, 2))) int printf(const char *text, ...);

int scanf(const char *format, ...);
int sscanf(const char *str, const char *format, ...);
int vscanf(const char *format, va_list ap);
int vfscanf(FILE *stream, const char *format, va_list ap);
int vsscanf(const char *str, const char *format, va_list ap);

void fclose(FILE *stream);

__attribute__((malloc(fclose, 1))) FILE *fopen(const char *filename,
                                               const char *mode);
FILE *fdopen(int fd, const char *mode);
long unsigned int fread(void *buffer, long unsigned int size,
                        long unsigned int count, FILE *stream);
long unsigned int fwrite(const void *buffer, long unsigned int size,
                         long unsigned int count, FILE *stream);
int fseek(FILE *stream, long offset, int origin);
long int ftell(FILE *stream);

int fputs(const char *__restrict str, FILE *__restrict stream);

int feof(FILE *stream);
int fflush(FILE *stream);

int fputc(int c, FILE *stream);
int fscanf(FILE *stream, const char *format, ...);
__attribute__((format(printf, 2, 3))) int fprintf(FILE *stream,
                                                  const char *text, ...);
