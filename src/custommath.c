/**
 * @file custommath.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Custom math function implementations.
 * @version 0.1
 * @date 2020-11-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _CUSTOM_MATH_H_
#include "custommath.h"
#endif /* _CUSTOM_MATH_H_ */

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
