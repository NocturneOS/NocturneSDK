#include "math.h"

double scalbn(double x, int n) {
    double result = x;
    if (n > 0) {
        for (int i = 0; i < n; i++) {
            result *= 2.0;
        }
    } else if (n < 0) {
        for (int i = 0; i < -n; i++) {
            result /= 2.0;
        }
    }
    return result;
}

float scalbnf(float x, int n) {
    float result = x;
    if (n > 0) {
        for (int i = 0; i < n; i++) {
            result *= 2.0f;
        }
    } else if (n < 0) {
        for (int i = 0; i < -n; i++) {
            result /= 2.0f;
        }
    }
    return result;
}
