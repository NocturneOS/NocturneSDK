#include "math.h"

double fmin(double x, double y) {
  if (is_nan(x)) {
    return y;
  }
  if (is_nan(y)) {
    return x;
  }
  if (x < y) {
    return x;
  }
  return y;
}

float fminf(float x, float y) {
  if (is_nan(x)) {
    return y;
  }
  if (is_nan(y)) {
    return x;
  }
  if (x < y) {
    return x;
  }
  return y;
}
