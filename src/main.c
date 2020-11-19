// Standard headers
#include <stdio.h>
#include <stdlib.h>
// Custom headers
#include "customwingdi.h"
// Image filename constant
const char OIMGNAME[] = "lena512.bmp";

int main(void) {
    // Read the original image.
    BITMAP oimg = bmRead(OIMGNAME);
    printf("[main] Read image completed.\n");

    // Process images.
    BITMAP ximg = StretchBlt(&oimg, 1.5);
    printf("[main] Image interpolation completed.\n");

    // Save the image.
    bmSave(&ximg, "ximg.bmp");
    printf("[main] The image was saved.\n");

    // Destory the image.
    bmDel(&oimg);
    bmDel(&ximg);

    printf("Program exited.");
	return EXIT_SUCCESS;
}
