/**
 * @file main.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Task 4 main logic.
 * @version 0.1
 * @date 2020-12-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

// Standard headers
#include <stdio.h>
#include <stdlib.h>
// Custom headers
#include "madlad.h"
#include "clock.h"
// YUV filepath
const char* restrict const YUVPATH = "../res/data.yuv";

// Main logic
int main(void) {
    TSCL = 1;
    clock_t start_t = clock();
    parseYUV(YUVPATH);
    clock_t elapse_t = clock() - start_t;
    printf("[main] Operations took %d cycles.\n", elapse_t);
    return EXIT_SUCCESS;
}
