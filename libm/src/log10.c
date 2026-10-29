#include "math.h"

double log10(double x) {
    if (x <= 0) {
        return -1e30;
    }
    return log(x) / log(10.0);
}

float log10f(float x) {
    if (x <= 0.0f) {
        return -1e30f;
    }
    return (float)log10((double)x);
}
