/**
 * @file main.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Task 3 main logic.
 * @version 0.1
 * @date 2020-12-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Custom headers
#include "imgproc.h"

// Cycle counting control registers
extern cregister volatile unsigned int TSCL;
extern cregister volatile unsigned int TSCH;
// Cycle counter
clock_t clock(void) {
    unsigned int low = TSCL;
    unsigned int high = TSCH;
    if (high) return (clock_t) -1;
    return low;
}

int main(void) {
    int s1, s2, s3;
    printf("Enter Y, Cb, Cr:");
    scanf("%d, %d, %d", &s1, &s2, &s3);
    unsigned char Y, Cb, Cr, Rc, Gc, Bc, R, G, B;
    if (s1 < 0 || s1 > 255 || s2 < 0 || s2 > 255 || s3 < 0 || s3 > 255) {
        fprintf(stderr, "[main] Out of range input(s).\n");
        return EXIT_FAILURE;
    } else {
        Y = s1;
        Cb = s2;
        Cr = s3;
    }
    // Cycle counter
    TSCL = 1;
    cvtColor_C(Y, Cb, Cr, &Rc, &Gc, &Bc);
    clock_t start_t = clock();
    cvtColor(Y, Cb, Cr, &R, &G, &B);
    clock_t elapse_t = clock() - start_t;
    printf("Y:%d, Cb:%d, Cr:%d --> R:%d, G:%d, B:%d\n", Y, Cb, Cr, Rc, Gc, Bc);
    printf("Y:%d, Cb:%d, Cr:%d --> R:%d, G:%d, B:%d\n", Y, Cb, Cr, R, G, B);
    printf("Conversion took %d cycles.\n", elapse_t);
    return EXIT_SUCCESS;
}
