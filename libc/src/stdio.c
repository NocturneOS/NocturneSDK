#include "stdio.h"
#include "file.h"
#include "sprintf.h"
#include "stdint.h"
#include "string.h"
#include <stdarg.h>

int puts(const char *text) {
  const char newline = '\n';

  int length = strlen(text);

  int result = write(FD_STDOUT, 1, length, text);

  result += write(FD_STDOUT, 1, 1, &newline);

  return result;
}

int putchar(int ch) {
  int result = write(FD_STDOUT, 1, 1, &ch);

  return result;
}

/**
 * @brief Подфункция-обработчик для tty_printf
 *
 * @param format - строка форматов
 * @param args - аргументы
 */
static void __print(char character, void *arg) {
  (void)arg;

  write(FD_STDOUT, 1, 1, &character);
}

int printf(const char *text, ...) {
  va_list args;
  va_start(args, text);

  int result = vfctprintf(__print, 0, text, args);

  va_end(args);

  return result;
}
