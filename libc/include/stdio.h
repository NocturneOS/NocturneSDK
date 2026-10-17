#pragma once

#define EOF (-1)

#define FD_STDIN 0
#define FD_STDOUT 1
#define FD_STDERR 2

typedef struct {
} FILE;

extern FILE *stderr;
extern FILE *stdout;
extern FILE *stdin;

int puts(const char *text);
int putchar(int ch);

__attribute__((format(printf, 1, 2))) int printf(const char *text, ...);
__attribute__((format(printf, 2, 3))) int fprintf(FILE *stream,
                                                  const char *text, ...);

void fflush(FILE *stream);
