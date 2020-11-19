#ifndef _CUSTOM_MATH_
#include "custommath.h"
#endif

int min(int x, int y) {
    return (x > y) ? y : x;
}

int rint(float arg) {
    int x = arg;
    int y = arg + 0.5;
    if (x == y) {
        return is_odd(x) ? (x + 1) : x;
    } else {
        return is_odd(x) ? y : x;
    }
}
