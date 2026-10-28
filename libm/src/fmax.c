#include "math.h"

double fmax(double x, double y) {
  if (is_nan(x)) {
    return y;
  }
  if (is_nan(y)) {
    return x;
  }
  if (x > y) {
    return x;
  }
  return y;
}

float fmaxf(float x, float y) {
  if (is_nan(x)) {
    return y;
  }
  if (is_nan(y)) {
    return x;
  }
  if (x > y) {
    return x;
  }
  return y;
}
