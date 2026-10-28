#include "math.h"

float atan2f(float y, float x) {
    if (x > 0) {
        return (float)atan((double)y / (double)x);
    } else if (x < 0 && y >= 0) {
        return (float)atan((double)y / (double)x) + (float)M_PI;
    } else if (x < 0 && y < 0) {
        return (float)atan((double)y / (double)x) - (float)M_PI;
    } else if (y > 0 && x == 0) {
        return (float)M_PI / 2.0f;
    } else if (y < 0 && x == 0) {
        return -(float)M_PI / 2.0f;
    }
    return 0.0f;
}
