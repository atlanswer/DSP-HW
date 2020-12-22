/**
 * @file imgproc.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Color conversion function.
 * @version 0.1
 * @date 2020-12-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _IMGPROC_H_
#include "imgproc.h"
#endif

int max(float a, float b) {
    return a > b ? a : b;
}

unsigned char min(int a, unsigned char b) {
    return a > b ? b : a;
}

void cvtColor(unsigned char const Y, unsigned char const Cb, unsigned char const Cr,
              unsigned char* const pR, unsigned char* const pG, unsigned char* const pB) {
    *pR = min(max(0, round(1.164 * Y                      + 1.402 * (Cr - 128))), 255);
    *pG = min(max(0, round(1.164 * Y - 0.344 * (Cb - 128) - 0.714 * (Cr - 128))), 255);
    *pB = min(max(0, round(1.164 * Y + 1.772 * (Cb - 128)                     )), 255);
}
