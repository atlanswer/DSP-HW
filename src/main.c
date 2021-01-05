/**
 * @file main.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Task 5 main logic.
 * @version 0.2
 * @date 2021-01-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Standard headers
#include <stdio.h>
#include <stdlib.h>
// Custom headers
#include "clock.h"
#include "customwingdi.h"
#include "imgproc.h"
// Image filepath constant
const char LENAPATH[] = "../res/lena2.bmp";
const char GIRLPATH[] = "../res/girl2.bmp";
const char LENA3PATH[] = "../res/lena_mf3.bmp";
const char GIRL3PATH[] = "../res/girl_mf3.bmp";
const char GIRL5PATH[] = "../res/girl_mf5.bmp";
// Main logic
int main(void) {
    /// Start CPU cycle counter.
    TSCL = 1;
    /// Read images.
    BITMAP lena = bmRead(LENAPATH);
    BITMAP girl = bmRead(GIRLPATH);
    printf("[main] Images loaded.\n");
    /// Median filtering
    BITMAP lena3 = medfilt2(&lena, 3);
    BITMAP girl3 = medfilt2(&girl, 3);
    BITMAP girl5 = medfilt2(&girl, 5);
    printf("[main] Median filtering completed.\n");
    // Save images.
    bmSave(&lena3, LENA3PATH);
    bmSave(&girl3, GIRL3PATH);
    bmSave(&girl5, GIRL5PATH);
    printf("[main] Images saved.\n");
    /// Release the images.
    bmDel(&lena);
    bmDel(&girl);
    bmDel(&lena3);
    bmDel(&girl3);
    bmDel(&girl5);

    printf("[main] Program exited.\n");
    return EXIT_SUCCESS;
}
