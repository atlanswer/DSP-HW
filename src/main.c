// Standard headers
#include <stdio.h>
#include <stdlib.h>
// Custom headers
#include "customwingdi.h"
// Constant
const char MIMGNAME[] = "redbrick.bmp";
const char OIMGNAME[] = "lena512.bmp";
const char SIMGNAME[] = "6x6_24bit.bmp";

int main(void) {
    // Read the original image.
    BITMAP oimg = bmRead(OIMGNAME);
    printf("Read image completed.\n");

    // Save the image.
    bmSave(&oimg, "nimg.bmp");
    printf("The image was saved.\n");

    // Release Image
    bmDel(&oimg);
    printf("Program exited.");

	return EXIT_SUCCESS;
}
