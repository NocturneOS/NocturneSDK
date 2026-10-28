#include "math.h"

double ldexp(double x, int exp) {
    return scalbn(x, exp);
}

float ldexpf(float x, int exp) {
    return scalbnf(x, exp);
}
