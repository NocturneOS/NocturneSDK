#include "math.h"

double atan2(double y, double x) {
    if (x > 0) {
        return atan(y / x);
    } else if (x < 0 && y >= 0) {
        return atan(y / x) + M_PI;
    } else if (x < 0 && y < 0) {
        return atan(y / x) - M_PI;
    } else if (y > 0 && x == 0) {
        return M_PI / 2.0;
    } else if (y < 0 && x == 0) {
        return -M_PI / 2.0;
    }
    return 0;
}
