/**
 * @file main.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Main logic.
 * @version 0.2
 * @date 2020-12-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

// Standard headers
#include <stdio.h>
#include <stdlib.h>
// Custom headers
#include "customwingdi.h"
// Image filename constant
const char OIMGNAME[] = "lena512.bmp";
const char XIMGNAME[] = "ximg.bmp";

int main(void) {
    /// Start CPU cycle counter.
    TSCL = 1;

    /// Read the original image.
    BITMAP oimg = bmRead(OIMGNAME);
    printf("[main] Read image completed.\n");

    /// Process images.
    BITMAP ximg = StretchBlt(&oimg, 1.5);
    printf("[main] Image interpolation completed.\n");

    /// Save the image.
    bmSave(&ximg, XIMGNAME);
    printf("[main] The image was saved.\n");

    /// Destory the image.
    bmDel(&oimg);
    bmDel(&ximg);

    printf("Program exited.\n");
	return EXIT_SUCCESS;
}
