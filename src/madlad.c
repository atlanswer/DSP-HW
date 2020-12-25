/**
 * @file madlad.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Optimized matrix operation.
 * @version 0.1
 * @date 2020-12-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _MADLAD_H_
#include "madlad.h"
#endif /** _MADLAD_H_ **/

void debugPrintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void parseYUV(const char* restrict const YUVPATH) {
    // Open file for IO
    int fYUV = open(YUVPATH, O_RDONLY, S_IRUSR);
    if (fYUV == -1) {
        perror("[parseYUV] Failed to open the YUV file.");
        exit(EXIT_FAILURE);
    }
    // Close file for IO
    int state = close(fYUV);
    if (state == -1) {
        perror("[parseYUV] Failed on closing the YUV file.");
        exit(EXIT_FAILURE);
    }
}

void printMAT(short MAT[][4], unsigned rows) {
    unsigned r, c;
    for (r = 0; r < rows; ++r) {
        for (c = 0; c < 4; ++c) {
            printf("%d\t", MAT[r][c]);
        }
        printf("\n");
    }
}
