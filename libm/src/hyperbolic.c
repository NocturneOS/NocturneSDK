#include "math.h"

double sinh(double x) {
    double ex = exp(x);
    return (ex - 1.0 / ex) / 2.0;
}

double cosh(double x) {
    double ex = exp(x);
    return (ex + 1.0 / ex) / 2.0;
}

double tanh(double x) {
    if (x > 700) {
        return 1.0;
    }
    if (x < -700) {
        return -1.0;
    }
    double ex = exp(2.0 * x);
    return (ex - 1.0) / (ex + 1.0);
}

float sinhf(float x) {
    float ex = exp((double)x);
    return (float)((ex - 1.0 / ex) / 2.0);
}

float coshf(float x) {
    float ex = exp((double)x);
    return (float)((ex + 1.0 / ex) / 2.0);
}

float tanhf(float x) {
    if (x > 700.0f) {
        return 1.0f;
    }
    if (x < -700.0f) {
        return -1.0f;
    }
    double ex = exp(2.0 * (double)x);
    return (float)((ex - 1.0) / (ex + 1.0));
}
