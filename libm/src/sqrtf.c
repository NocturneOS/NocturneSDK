#include "math.h"

float sqrtf(float x) {
    if (x < 0) {
        return -1.0f;
    }
    
    float guess = x;
    float epsilon = 1e-7f;

    while ((guess * guess - x) > epsilon) {
        guess = 0.5f * (guess + x / guess);
    }
    
    return guess;
}
