#pragma once

#define EOF (-1)

#define FD_STDIN 0
#define FD_STDOUT 1
#define FD_STDERR 2

int puts(const char* text);

__attribute__((format(printf, 1, 2)))
int printf(const char *text, ...);
