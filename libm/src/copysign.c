#include "math.h"

double copysign(double x, double y) {
    union intfloat64 ux, uy;
    ux.f = x;
    uy.f = y;
    ux.i = (ux.i & 0x7fffffffffffffffULL) | (uy.i & 0x8000000000000000ULL);
    return ux.f;
}

float copysignf(float x, float y) {
    union intfloat32 ux, uy;
    ux.f = x;
    uy.f = y;
    ux.i = (ux.i & 0x7fffffff) | (uy.i & 0x80000000);
    return ux.f;
}
