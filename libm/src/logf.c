#include "math.h"

float logf(float x) {
    if (x <= 0.0f) {
        return -1e30f;
    }
    return (float)log((double)x);
}
