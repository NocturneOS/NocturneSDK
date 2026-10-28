#include "math.h"

double fmod(double x, double y) {
    if (y == 0.0) {
        return 0.0;
    }
    long long quotient = (long long)(x / y);
    double result = x - quotient * y;
    return result;
}

float fmodf(float x, float y) {
    if (y == 0.0f) {
        return 0.0f;
    }
    long long quotient = (long long)((double)x / (double)y);
    float result = x - (float)quotient * y;
    return result;
}
