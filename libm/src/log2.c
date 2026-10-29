#include "math.h"

double log2(double x) {
    if (x <= 0) {
        return -1e30;
    }
    return log(x) / log(2.0);
}

float log2f(float x) {
    if (x <= 0.0f) {
        return -1e30f;
    }
    return (float)log2((double)x);
}
