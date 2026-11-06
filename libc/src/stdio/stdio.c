#include "stdio.h"
#include "sprintf.h"
#include "string.h"
#include "unistd.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>


int puts(const char *text) {
  const char newline = '\n';

  int length = strlen(text);

  int result = write(FD_STDOUT, text, length);

  result += write(FD_STDOUT, &newline, 1);

  return result;
}

int putchar(int ch) {
  int result = write(FD_STDOUT, &ch, 1);

  return result;
}

static void __print(char character, void *arg) {
  (void)arg;

  write(FD_STDOUT, &character, 1);
}

int printf(const char *text, ...) {
  va_list args;
  va_start(args, text);

  int result = vfctprintf(__print, 0, text, args);

  va_end(args);

  return result;
}

