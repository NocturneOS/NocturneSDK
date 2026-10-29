#include "math.h"

double modf(double value, double *intPart) {
    if (intPart == 0) {
        return value;
    }
    if (value >= 0) {
        *intPart = (double)(long long)value;
        return value - *intPart;
    } else {
        *intPart = (double)(long long)value;
        return value - *intPart;
    }
}

float modff(float value, float *intPart) {
    if (intPart == 0) {
        return value;
    }
    if (value >= 0) {
        *intPart = (float)(long long)value;
        return value - *intPart;
    } else {
        *intPart = (float)(long long)value;
        return value - *intPart;
    }
}

double frexp(double x, int *exp) {
    if (x == 0.0) {
        if (exp) *exp = 0;
        return 0.0;
    }
    int e = 0;
    double val = x;
    if (val >= 1.0) {
        while (val >= 1.0) {
            val /= 2.0;
            e++;
        }
    } else if (val < 0.5 && val > -0.5) {
        while (val >= -0.5 && val < 0.5 && val != 0.0) {
            val *= 2.0;
            e--;
        }
    }
    if (exp) *exp = e;
    return val;
}

float frexpf(float x, int *exp) {
    if (x == 0.0f) {
        if (exp) *exp = 0;
        return 0.0f;
    }
    int e = 0;
    float val = x;
    if (val >= 1.0f) {
        while (val >= 1.0f) {
            val /= 2.0f;
            e++;
        }
    } else if (val < 0.5f && val > -0.5f) {
        while (val >= -0.5f && val < 0.5f && val != 0.0f) {
            val *= 2.0f;
            e--;
        }
    }
    if (exp) *exp = e;
    return val;
}
