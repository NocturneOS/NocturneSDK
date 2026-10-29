#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define M_E 2.7182818284590452354         /* e */
#define M_LOG2E 1.4426950408889634074     /* log_2 e */
#define M_LOG10E 0.43429448190325182765   /* log_10 e */
#define M_LN2 0.69314718055994530942      /* log_e 2 */
#define M_LN10 2.30258509299404568402     /* log_e 10 */
#define M_PI 3.14159265358979323846       /* pi */
#define M_PI_2 1.57079632679489661923     /* pi/2 */
#define M_PI_4 0.78539816339744830962     /* pi/4 */
#define M_1_PI 0.31830988618379067154     /* 1/pi */
#define M_2_PI 0.63661977236758134308     /* 2/pi */
#define M_2_SQRTPI 1.12837916709551257390 /* 2/sqrt(pi) */
#define M_SQRT2 1.41421356237309504880    /* sqrt(2) */
#define M_SQRT1_2 0.70710678118654752440  /* 1/sqrt(2) */

#define ABS(a) ((a) >= 0 ? (a) : -(a))

#define MIN(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a < _b ? _a : _b;                                                         \
  })

#define MAX(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _a : _b;                                                         \
  })

#define NAN int2float(0x7fc00000)
#define INFINITY int2float(0x7f800000)

union intfloat32 {
  uint32_t i;
  float f;
};

union intfloat64 {
  uint64_t i;
  double f;
};

static inline float int2float(uint32_t i) {
  union intfloat32 v;
  v.i = i;
  return v.f;
}

static inline double int2double(uint64_t i) {
  union intfloat64 v;
  v.i = i;
  return v.f;
}

static inline bool is_nan(float value) {
  union intfloat32 value_union;
  value_union.f = value;

  int exponent = (value_union.i >> 23) & 0xFF;
  int fraction = value_union.i & 0x7FFFFF;

  return exponent == 0xFF && fraction != 0;
}

static inline bool is_inf(float value) {
  union intfloat32 value_union;
  value_union.f = value;

  unsigned int exponent = (value_union.i >> 23) & 0xFF;
  unsigned int fraction = value_union.i & 0x7FFFFF;

  return (exponent == 0xFF) && (fraction == 0);
}

static inline double floor(double x) {
  int intPart = (int)x;

  return intPart - (x < 0 && x != intPart);
}

static inline double ceil(double x) {
  int intPart = (int)x;

  return intPart + (x > 0 && x != intPart);
}

static inline float floorf(float x) {
  int intPart = (int)x;

  return (float)(intPart - (x < 0 && x != intPart));
}

static inline float ceilf(float x) {
  int intPart = (int)x;

  return (float)(intPart + (x > 0 && x != intPart));
}

static inline double fabs(double x) { return (x < 0) ? -x : x; }
static inline float fabsf(float x) { return (x < 0) ? -x : x; }

#define FP_NAN 0
#define FP_INFINITE 1
#define FP_ZERO 2
#define FP_SUBNORMAL 3
#define FP_NORMAL 4

static inline int fpclassify(double x) {
    if (is_nan((float)x)) {
        return FP_NAN;
    }
    if (is_inf((float)x)) {
        return FP_INFINITE;
    }
    if (x == 0.0) {
        return FP_ZERO;
    }
    return FP_NORMAL;
}

static inline int fpclassifyf(float x) {
    if (is_nan(x)) {
        return FP_NAN;
    }
    if (is_inf(x)) {
        return FP_INFINITE;
    }
    if (x == 0.0f) {
        return FP_ZERO;
    }
    return FP_NORMAL;
}

#define ASIN_STEPS 6000
#define ATAN_STEPS 6000

size_t fac(size_t x);

double deg2rad(double degrees);
double rad2deg(double radians);

double sin(double x);
double cos(double x);
double tan(double x);

double pow(double base, double exponent);

double trapezoidal_rule(double (*f)(double), double a, double b,
                        unsigned int steps);

double log(double x);
float logf(float x);
double log10(double x);
float log10f(float x);
double log2(double x);
float log2f(float x);
double exp(double x);

double asin(double x);
double acos(double x);
double atan(double x);
double atan2(double y, double x);

float atan2f(float y, float x);

double sinh(double x);
double cosh(double x);
double tanh(double x);

float sinhf(float x);
float coshf(float x);
float tanhf(float x);

double sqrt(double x);
float sqrtf(float x);
double cbrt(double x);
double modf(double value, double *intPart);
float modff(float value, float *intPart);
double frexp(double x, int *exp);
float frexpf(float x, int *exp);
double fmod(double x, double y);
float fmodf(float x, float y);

double copysign(double x, double y);
float copysignf(float x, float y);

double scalbn(double x, int n);
float scalbnf(float x, int n);

double fmax(double x, double y);
float fmaxf(float x, float y);

double fmin(double x, double y);
float fminf(float x, float y);

double ldexp(double x, int exp);
float ldexpf(float x, int exp);
