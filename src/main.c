// Standard headers
#include <stdio.h>
#include <stdlib.h>
// Custom headers
#include "customwingdi.h"
// Constant
// const char MIMGNAME[] = "redbrick.bmp";
const char OIMGNAME[] = "lena128.bmp";
// const char SIMGNAME[] = "6x6_24bit.bmp";

int main(void) {
    // Read the original image.
    BITMAP oimg = bmRead(OIMGNAME);
    printf("Read image completed.\n");

    // Process
    BITMAP ximg = StretchBlt(&oimg, 2);
    // BITMAP ximg = CreateBitmap(25, 25, &oimg);

    // Save the image.
    bmSave(&ximg, "ximg.bmp");
    printf("The image was saved.\n");

    // Release Image
    bmDel(&oimg);
    // bmDel(&ximg);
    printf("Program exited.");

	return EXIT_SUCCESS;
}
