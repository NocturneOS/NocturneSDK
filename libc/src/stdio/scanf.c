/*
 * scanf family implementation.
 *
 * Architecture mirrors sprintf.h / sprintf.c: the actual formatting is done by
 * one engine (_scanf_core) that never touches a string or a FILE directly.
 * Instead it pulls characters from a "source" abstraction consisting of a
 * single get() callback plus an internal pushback buffer.  The public
 * functions (vsscanf, vfscanf, vscanf) only construct the appropriate source
 * and hand it to the engine:
 *
 *   vsscanf -> string source (wraps const char *)
 *   vfscanf -> file source   (wraps FILE *)
 *   vscanf  -> file source   (wraps stdin)
 */

#include "file.h"
#include "stdio.h"

#include <ctype.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define SCANF_PUSHBACK_MAX 8

typedef struct {
  /* Returns the next byte (0..255) or EOF. Must be provided by the wrapper. */
  int (*get)(void *ctx);
  void *ctx;

  /* Internal pushback stack, so conversions can do lookahead. */
  int pushback[SCANF_PUSHBACK_MAX];
  int n_pushback;

  /* Number of characters consumed from the source (used by %n). */
  size_t n_read;
} scanf_source;

static int src_get(scanf_source *src) {
  int c;

  if (src->n_pushback > 0) {
    c = src->pushback[--src->n_pushback];
  } else {
    c = src->get(src->ctx);
  }

  if (c != EOF) {
    src->n_read++;
  }

  return c;
}

static void src_unget(scanf_source *src, int c) {
  if (c == EOF) {
    return;
  }

  if (src->n_read > 0) {
    src->n_read--;
  }

  if (src->n_pushback < SCANF_PUSHBACK_MAX) {
    src->pushback[src->n_pushback++] = c;
  }
}

static int src_peek(scanf_source *src) {
  int c = src_get(src);
  src_unget(src, c);
  return c;
}

static void skip_whitespace(scanf_source *src) {
  int c;

  while ((c = src_peek(src)) != EOF && isspace((unsigned char)c)) {
    src_get(src);
  }
}

/* ------------------------------------------------------------------------- */
/* Sources                                                                   */
/* ------------------------------------------------------------------------- */

typedef struct {
  const char *ptr;
} string_source_ctx;

static int string_source_get(void *ctx) {
  string_source_ctx *s = (string_source_ctx *)ctx;
  unsigned char c = (unsigned char)*s->ptr;

  if (c == '\0') {
    return EOF;
  }

  s->ptr++;

  return c;
}

typedef struct {
  FILE *stream;
} file_source_ctx;

// It's a `fgetc`!
static int file_source_get(void *ctx) {
  file_source_ctx *f = (file_source_ctx *)ctx;
  unsigned char c;

  if (fread(&c, 1, 1, f->stream) != 1) {
    return EOF;
  }

  return c;
}

/* ------------------------------------------------------------------------- */
/* Conversion helpers                                                        */
/* ------------------------------------------------------------------------- */

enum length_modifier {
  LEN_NONE,
  LEN_HH,
  LEN_H,
  LEN_L,
  LEN_LL,
  LEN_BIG_L,
  LEN_J,
  LEN_Z,
  LEN_T
};

static int digit_value(int c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 10;
  }
  if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 10;
  }
  return -1;
}

/*
 * Reads an integer in the given base (0 = auto-detect).
 * Returns 1 on success, 0 on matching failure.
 */
static int read_integer(scanf_source *src, int base, unsigned long long *out,
                        int *negative) {
  int sign = 1;
  int c = src_get(src);
  int autodetect = (base == 0);
  unsigned long long acc = 0;
  int any = 0;

  if (c == '+' || c == '-') {
    sign = (c == '-') ? -1 : 1;
    c = src_get(src);
  }

  if (autodetect) {
    base = 10;
  }

  if (c == '0') {
    if (autodetect) {
      int next = src_get(src);

      if (next == 'x' || next == 'X') {
        int d = digit_value(src_peek(src));

        if (d >= 0 && d < 16) {
          base = 16;
          c = src_get(src);
        } else {
          src_unget(src, next);
          base = 8;
        }
      } else {
        src_unget(src, next);
        base = 8;
      }
    } else if (base == 16) {
      int next = src_get(src);

      if (next == 'x' || next == 'X') {
        int d = digit_value(src_peek(src));

        if (d >= 0 && d < 16) {
          c = src_get(src);
        } else {
          src_unget(src, next);
        }
      } else {
        src_unget(src, next);
      }
    }
  }

  while (c != EOF) {
    int d = digit_value(c);

    if (d < 0 || d >= base) {
      break;
    }

    any = 1;
    acc = acc * (unsigned long long)base + (unsigned long long)d;
    c = src_get(src);
  }

  src_unget(src, c);

  if (!any) {
    return 0;
  }

  *out = acc;
  *negative = (sign < 0);

  return 1;
}

static double pow10_int(int exponent) {
  double result = 1.0;

  if (exponent > 0) {
    while (exponent-- > 0) {
      result *= 10.0;
    }
  } else {
    while (exponent++ < 0) {
      result /= 10.0;
    }
  }

  return result;
}

/*
 * Reads a floating point number.
 * Returns 1 on success, 0 on matching failure.
 */
static int read_float(scanf_source *src, double *out) {
  double value = 0.0;
  int negative = 0;
  int any = 0;
  int c = src_peek(src);

  if (c == '+' || c == '-') {
    src_get(src);
    negative = (c == '-');
  }

  while (isdigit(src_peek(src))) {
    value = value * 10.0 + (double)(src_get(src) - '0');
    any = 1;
  }

  if (src_peek(src) == '.') {
    double scale = 0.1;

    src_get(src);

    while (isdigit(src_peek(src))) {
      value += (double)(src_get(src) - '0') * scale;
      scale *= 0.1;
      any = 1;
    }
  }

  if (!any) {
    return 0;
  }

  c = src_peek(src);

  if (c == 'e' || c == 'E') {
    int e_char = src_get(src);
    int sign_char = 0;
    int exponent = 0;
    int exponent_any = 0;
    int p = src_peek(src);

    if (p == '+' || p == '-') {
      sign_char = src_get(src);
    }

    while (isdigit(src_peek(src))) {
      exponent = exponent * 10 + (src_get(src) - '0');
      exponent_any = 1;
    }

    if (exponent_any) {
      if (sign_char == '-') {
        exponent = -exponent;
      }
      value *= pow10_int(exponent);
    } else {
      /* Not an exponent after all: give back what we consumed. */
      if (sign_char != 0) {
        src_unget(src, sign_char);
      }
      src_unget(src, e_char);
    }
  }

  *out = negative ? -value : value;

  return 1;
}

static void store_signed(va_list *ap, enum length_modifier len, long long v) {
  switch (len) {
  case LEN_HH:
    *va_arg(*ap, signed char *) = (signed char)v;
    break;
  case LEN_H:
    *va_arg(*ap, short *) = (short)v;
    break;
  case LEN_L:
    *va_arg(*ap, long *) = (long)v;
    break;
  case LEN_LL:
    *va_arg(*ap, long long *) = v;
    break;
  case LEN_J:
    *va_arg(*ap, intmax_t *) = (intmax_t)v;
    break;
  case LEN_Z:
    *va_arg(*ap, size_t *) = (size_t)v;
    break;
  case LEN_T:
    *va_arg(*ap, ptrdiff_t *) = (ptrdiff_t)v;
    break;
  default:
    *va_arg(*ap, int *) = (int)v;
    break;
  }
}

static void store_unsigned(va_list *ap, enum length_modifier len,
                           unsigned long long v) {
  switch (len) {
  case LEN_HH:
    *va_arg(*ap, unsigned char *) = (unsigned char)v;
    break;
  case LEN_H:
    *va_arg(*ap, unsigned short *) = (unsigned short)v;
    break;
  case LEN_L:
    *va_arg(*ap, unsigned long *) = (unsigned long)v;
    break;
  case LEN_LL:
    *va_arg(*ap, unsigned long long *) = v;
    break;
  case LEN_J:
    *va_arg(*ap, uintmax_t *) = (uintmax_t)v;
    break;
  case LEN_Z:
    *va_arg(*ap, size_t *) = (size_t)v;
    break;
  case LEN_T:
    *va_arg(*ap, ptrdiff_t *) = (ptrdiff_t)v;
    break;
  default:
    *va_arg(*ap, unsigned int *) = (unsigned int)v;
    break;
  }
}

static void store_float(va_list *ap, enum length_modifier len, double v) {
  if (len == LEN_BIG_L) {
    *va_arg(*ap, long double *) = (long double)v;
  } else if (len == LEN_L) {
    *va_arg(*ap, double *) = v;
  } else {
    *va_arg(*ap, float *) = (float)v;
  }
}

/* ------------------------------------------------------------------------- */
/* The engine                                                                */
/* ------------------------------------------------------------------------- */

static int _scanf_core(const char *format, va_list ap, scanf_source *src) {
  const char *f = format;
  int assigned = 0;
  int input_failure = 0;
  /*
   * Work on a private copy. This also makes &args a valid va_list pointer on
   * targets where va_list is an array type (e.g. x86_64 System V ABI), so the
   * store_* helpers below stay portable.
   */
  va_list args;

  va_copy(args, ap);

  while (*f != '\0') {
    if (isspace((unsigned char)*f)) {
      while (isspace((unsigned char)*f)) {
        f++;
      }
      skip_whitespace(src);
      continue;
    }

    if (*f != '%') {
      int c = src_get(src);

      if (c == EOF) {
        input_failure = 1;
        break;
      }
      if (c != (unsigned char)*f) {
        src_unget(src, c);
        break;
      }
      f++;
      continue;
    }

    f++;

    if (*f == '%') {
      int c = src_get(src);

      if (c == EOF) {
        input_failure = 1;
        break;
      }
      if (c != '%') {
        src_unget(src, c);
        break;
      }
      f++;
      continue;
    }

    int suppress = 0;

    if (*f == '*') {
      suppress = 1;
      f++;
    }

    int width = 0;
    int has_width = 0;

    while (isdigit((unsigned char)*f)) {
      has_width = 1;
      width = width * 10 + (*f - '0');
      f++;
    }

    enum length_modifier len = LEN_NONE;

    switch (*f) {
    case 'h':
      f++;
      if (*f == 'h') {
        len = LEN_HH;
        f++;
      } else {
        len = LEN_H;
      }
      break;
    case 'l':
      f++;
      if (*f == 'l') {
        len = LEN_LL;
        f++;
      } else {
        len = LEN_L;
      }
      break;
    case 'L':
      len = LEN_BIG_L;
      f++;
      break;
    case 'j':
      len = LEN_J;
      f++;
      break;
    case 'z':
      len = LEN_Z;
      f++;
      break;
    case 't':
      len = LEN_T;
      f++;
      break;
    default:
      break;
    }

    char conversion = *f;

    if (conversion == '\0') {
      break;
    }

    f++;

    /* %c, %[ and %n do not skip leading whitespace. */
    if (conversion != 'c' && conversion != '[' && conversion != 'n') {
      skip_whitespace(src);
    }

    switch (conversion) {
    case 'd':
    case 'i': {
      unsigned long long acc;
      int negative;

      if (!read_integer(src, (conversion == 'd') ? 10 : 0, &acc, &negative)) {
        input_failure = 1;
        goto done;
      }

      if (!suppress) {
        long long value = negative ? -(long long)acc : (long long)acc;
        store_signed(&args, len, value);
        assigned++;
      }
      break;
    }

    case 'u':
    case 'o':
    case 'x':
    case 'X': {
      unsigned long long acc;
      int negative;
      int base = (conversion == 'u') ? 10 : (conversion == 'o') ? 8 : 16;

      if (!read_integer(src, base, &acc, &negative)) {
        input_failure = 1;
        goto done;
      }

      if (!suppress) {
        store_unsigned(&args, len, negative ? (unsigned long long)(-acc) : acc);
        assigned++;
      }
      break;
    }

    case 'p': {
      unsigned long long acc;
      int negative;

      if (!read_integer(src, 16, &acc, &negative)) {
        input_failure = 1;
        goto done;
      }

      if (!suppress) {
        *va_arg(args, void **) = (void *)(uintptr_t)acc;
        assigned++;
      }
      break;
    }

    case 'f':
    case 'F':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
    case 'a':
    case 'A': {
      double value;

      if (!read_float(src, &value)) {
        input_failure = 1;
        goto done;
      }

      if (!suppress) {
        store_float(&args, len, value);
        assigned++;
      }
      break;
    }

    case 'c': {
      int count = has_width ? width : 1;
      char *buffer = suppress ? NULL : va_arg(args, char *);
      int i;

      for (i = 0; i < count; i++) {
        int c = src_get(src);

        if (c == EOF) {
          break;
        }

        if (buffer != NULL) {
          buffer[i] = (char)c;
        }
      }

      if (i == 0) {
        input_failure = 1;
        goto done;
      }

      if (!suppress) {
        assigned++;
      }
      break;
    }

    case 's': {
      char *buffer = suppress ? NULL : va_arg(args, char *);
      int limit = has_width ? width : 0x7fffffff;
      int i = 0;
      int c;

      while (i < limit && (c = src_peek(src)) != EOF &&
             !isspace((unsigned char)c)) {
        if (buffer != NULL) {
          buffer[i] = (char)src_get(src);
        } else {
          src_get(src);
        }
        i++;
      }

      if (i == 0) {
        input_failure = 1;
        goto done;
      }

      if (!suppress) {
        if (buffer != NULL) {
          buffer[i] = '\0';
        }
        assigned++;
      }
      break;
    }

    case '[': {
      unsigned char set[256] = {0};
      int negate = 0;
      int first = 1;
      int c;

      if (*f == '^') {
        negate = 1;
        f++;
      }

      while (*f != '\0' && (*f != ']' || first)) {
        if (*f == ']' && first) {
          /* A ']' immediately after '[' or '[^' is a literal. */
          set[(unsigned char)']'] = 1;
          f++;
          first = 0;
          continue;
        }

        if (f[1] == '-' && f[2] != '\0' && f[2] != ']') {
          int start = (unsigned char)f[0];
          int end = (unsigned char)f[2];
          int ch;

          for (ch = start; ch <= end; ch++) {
            set[ch] = 1;
          }
          f += 3;
        } else {
          set[(unsigned char)*f] = 1;
          f++;
        }

        first = 0;
      }

      if (*f == ']') {
        f++;
      }

      if (negate) {
        int i;
        for (i = 0; i < 256; i++) {
          set[i] = (unsigned char)!set[i];
        }
      }

      char *buffer = suppress ? NULL : va_arg(args, char *);
      int limit = has_width ? width : 0x7fffffff;
      int i = 0;

      while (i < limit && (c = src_peek(src)) != EOF && set[(unsigned char)c]) {
        if (buffer != NULL) {
          buffer[i] = (char)src_get(src);
        } else {
          src_get(src);
        }
        i++;
      }

      if (i == 0) {
        input_failure = 1;
        goto done;
      }

      if (!suppress) {
        if (buffer != NULL) {
          buffer[i] = '\0';
        }
        assigned++;
      }
      break;
    }

    case 'n': {
      if (!suppress) {
        *va_arg(args, int *) = (int)src->n_read;
      }
      break;
    }

    default:
      /* Unknown conversion: treat the '%' literally. */
      break;
    }
  }

done:

  va_end(args);

  if (assigned == 0 && input_failure) {
    return EOF;
  }

  return assigned;
}

/* ------------------------------------------------------------------------- */
/* Public API                                                                */
/* ------------------------------------------------------------------------- */

int vsscanf(const char *str, const char *format, va_list ap) {
  string_source_ctx ctx;
  scanf_source src;
  va_list copy;
  int result;

  ctx.ptr = str;

  src.get = string_source_get;
  src.ctx = &ctx;
  src.n_pushback = 0;
  src.n_read = 0;

  va_copy(copy, ap);
  result = _scanf_core(format, copy, &src);
  va_end(copy);

  return result;
}

int vfscanf(FILE *stream, const char *format, va_list ap) {
  file_source_ctx ctx;
  scanf_source src;
  va_list copy;
  int result;

  ctx.stream = stream;

  src.get = file_source_get;
  src.ctx = &ctx;
  src.n_pushback = 0;
  src.n_read = 0;

  va_copy(copy, ap);
  result = _scanf_core(format, copy, &src);
  va_end(copy);

  return result;
}

int vscanf(const char *format, va_list ap) {
  return vfscanf(stdin, format, ap);
}

int sscanf(const char *str, const char *format, ...) {
  va_list ap;
  int result;

  va_start(ap, format);
  result = vsscanf(str, format, ap);
  va_end(ap);

  return result;
}

int fscanf(FILE *stream, const char *format, ...) {
  va_list ap;
  int result;

  va_start(ap, format);
  result = vfscanf(stream, format, ap);
  va_end(ap);

  return result;
}

int scanf(const char *format, ...) {
  va_list ap;
  int result;

  va_start(ap, format);
  result = vfscanf(stdin, format, ap);
  va_end(ap);

  return result;
}
