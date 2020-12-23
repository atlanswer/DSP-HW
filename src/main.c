/**
 * @file main.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Task 3 main logic.
 * @version 01.0
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
// Main logic
int main(void) {
    // Fetch user's input.
    int s1, s2, s3;
    printf("Enter Y, Cb, Cr (comma seprated): ");
    scanf("%d, %d, %d", &s1, &s2, &s3);
    // Input check
    unsigned char Y, Cb, Cr;
    unsigned char YCbCr[4];
    if (s1 < 0 || s1 > 255 || s2 < 0 || s2 > 255 || s3 < 0 || s3 > 255) {
        fprintf(stderr, "[main] Out of range input(s).\n");
        return EXIT_FAILURE;
    } else {
        Y = YCbCr[2] = s1;
        Cb = YCbCr[1] = s2;
        Cr = YCbCr[0] = s3;
    }
    printf("Y:%d, Cb:%d, Cr:%d\n", Y, Cb, Cr);
    // Cycle counter
    TSCL = 1;
    // C implementation
    unsigned char Rc, Gc, Bc;
    clock_t start_t1 = clock();
    cvtColor_C(Y, Cb, Cr, &Rc, &Gc, &Bc);
    clock_t elapse_t1 = clock() - start_t1;
    printf("-- C (floating-point multiply) ---> R:%d, G:%d, B:%d | ", Rc, Gc, Bc);
    printf("took %d cycles.\n", elapse_t1);
    // Linear assembly implementation: 32 bits
    unsigned char Rl, Gl, Bl;
    clock_t start_t2 = clock();
    cvtColor(Y, Cb, Cr, &Rl, &Gl, &Bl);
    clock_t elapse_t2 = clock() - start_t2;
    printf("-- Linear ASM (16-bit multiply) --> R:%d, G:%d, B:%d | ", Rl, Gl, Bl);
    printf("took %d cycles.\n", elapse_t2);
    // Linear assembly implementation: 16 bits
    unsigned char Rs, Gs, Bs;
    clock_t start_t3 = clock();
    cvtColor_16b(YCbCr, &Rs, &Gs, &Bs);
    clock_t elapse_t3 = clock() - start_t3;
    printf("-- Linear ASM (8-bit multiply) ---> R:%d, G:%d, B:%d | ", Rs, Gs, Bs);
    printf("took %d cycles.\n", elapse_t3);
    return EXIT_SUCCESS;
}
