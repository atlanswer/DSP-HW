/**
 * @file main.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Task 4 main logic.
 * @version 0.2
 * @date 2020-12-26
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
const char* restrict const SAVEPATH = "../res/output.yuv";

// Main logic
int main(void) {
    TSCL = 1;
    clock_t begin_t = clock();
    parseYUV(YUVPATH);
    clock_t start_t = clock();
    transform();
    clock_t elapse_t = clock() - start_t;
    printf("[main] Transformation took %d cycles.\n", elapse_t);
    writeYUV(SAVEPATH);
    clock_t lifetime_t = clock() - begin_t;
    printf("[main] All operations took %d cycles.\n", lifetime_t);
    printf("[main] Program exited.\n");
    return EXIT_SUCCESS;
}
