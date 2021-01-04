/**
 * @file imgproc.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Image processing algorithm implementations.
 * @version 1.1
 * @date 2021-01-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>

#ifndef _IMGPROC_H_
#include "imgproc.h"
#endif /* _IMGPROC_H_ */

BITMAP medfilt2(const PBITMAP restrict pbm, const int N) {
    LONG oW = pbm->bmi.bmiHeader.biWidth;
    LONG oH = pbm->bmi.bmiHeader.biHeight;
    BITMAP ximg = CreateBitmap(oW, oH, pbm);
    // Interpolation process.
    clock_t start_t = clock();
    if (N == 3) {
        medfilt3(pbm->bmcia, ximg.bmcia, oW, oH);
    } else if (N == 5) {
        medfilt5(pbm->bmcia, ximg.bmcia, oW, oH);
    } else {
        perror("[medfilt2] N could only be 3 or 5");
        exit(EXIT_FAILURE);
    }
    clock_t elapse_t = clock() - start_t;
    printf("[medfilt2] Median filtering took: %d cycles.\n", elapse_t);
    return ximg;
}
