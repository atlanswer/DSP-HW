#ifndef _CUSTOM_WINGDI_
#include "customwingdi.h"
#endif

const INT INTER_RESIZE_COEF_BITS = 11;
// const INT INTER_RESIZE_COEF_SCALE = 1 << INTER_RESIZE_COEF_BITS;
const INT INTER_RESIZE_COEF_SCALE = 1 << 11;
// const INT CAST_BITS = INTER_RESIZE_COEF_BITS << 1;
const INT CAST_BITS = 11 << 1;

/* Create an empty bitmap,
 * The number of planes must be set to 1,
 * The number of bits-per-pixel must be 8.
 */
BITMAP CreateBitmap(int nWidth, int nHeight,
                    const PBITMAP pbmo) {
    // Assertion: Image format.
    assert(nWidth > 0);
    assert(nHeight > 0);
    assert(pbmo != NULL);
    // Create an empty bitmap.
    BITMAP bm;
    // Set BITMAPFILEHEADER.
    bm.bmfh = pbmo->bmfh;
    // Set BITMAPINFOHEADER.
    bm.bmi.bmiHeader = pbmo->bmi.bmiHeader;
    bm.bmi.bmiHeader.biWidth = nWidth;
    bm.bmi.bmiHeader.biHeight = nHeight;
    // 8 bit image only
    bm.bmi.bmiHeader.biSizeImage = nWidth * nHeight;
    // Set RGBQUAD array.
    bm.bmi.bmiColors = pbmo->bmi.bmiColors;
    // Set color-index array.
    // Allocate memory for the color-index array.
    size_t sizepix = sizeof(BYTE) * bm.bmi.bmiHeader.biHeight
                     * bm.bmi.bmiHeader.biWidth;
    size_t sizecia = sizeof(BYTE*) * bm.bmi.bmiHeader.biHeight
                     + sizepix;
    bm.bmcia = malloc(sizecia);
    // Assertion: allocation succeed.
    assert(bm.bmcia != NULL);
    /* The first part is an array of pointers to pointers to rows.
     * The second part is the actual data, referenced by
     * aforementioned row pointers.
     */
    // Set the pointers to the correct positions
    size_t row = bm.bmi.bmiHeader.biHeight - 1;
    bm.bmcia[row] = (BYTE*) (bm.bmcia + bm.bmi.bmiHeader.biHeight);
    for (; row != SIZE_MAX;) {
        bm.bmcia[row] = bm.bmcia[row--]
                        + bm.bmi.bmiHeader.biWidth;
    }
    // Calculate the file size.
    bm.bmfh.bfSize = bm.bmi.bmiHeader.biSizeImage
                     + bm.bmfh.bfOffBits;
    return bm;
}

// Bilinear image interpolation implementation
BITMAP StretchBlt(PBITMAP pbm, float scale) {
    LONG oW = pbm->bmi.bmiHeader.biWidth;
    LONG oH = pbm->bmi.bmiHeader.biHeight;
    LONG nW = ceil(oW * scale);
    LONG nH = ceil(oH * scale);
    BITMAP ximg = CreateBitmap(nW, nH, pbm);
    // Shortcut to the color-index array.
    BYTE** oi = pbm->bmcia;
    BYTE** xi = ximg.bmcia;
    // Interpolation process.
    // Inspired by OpenCL resize:
    // https://github.com/opencv/opencv/blob/master/modules/imgproc/src/opencl/resize.cl
    // Iterators for rows and cols in the new image.
    LONG ri = 0;
    LONG ci = 0;
    printf("Processing image...\n");
    for (ri = 0; ri < nH; ++ri) {
        // Convert a new pixel location to the original one.
        float sr = ((float) ri + 0.5) / scale - 0.5;
        // Row index to its up.
        LONG r = floor(sr);
        // Relative to the row index
        float u = sr - r;
        // Edge handling
        if (r < 0) {
            r = 0;
            u = 0;
        }
        if (r >= oH) {
            r = oH - 1;
            u = 0;
        }
        u = u * INTER_RESIZE_COEF_SCALE;
        INT U = rint(u);
        INT U1 = rint(INTER_RESIZE_COEF_SCALE - u);
        // Calculate the row index to its down.
        LONG r_ = min(r + 1, oH - 1);
        printf("Processing row = %d\n", ri);
        for (ci = 0; ci < nW; ++ci) {
            // Process columns in a similar way
            float sc = ((float) ci + 0.5) / scale - 0.5;
            LONG c = floor(sc);
            float v = sc - c;
            if (c < 0) {
                c = 0;
                v = 0;
            }
            if (c >= oW) {
                c = oW - 1;
                v = 0;
            }
            v = v * INTER_RESIZE_COEF_SCALE;
            INT V = rint(v);
            INT V1 = rint(INTER_RESIZE_COEF_SCALE - v);
            LONG c_ = min(c + 1, oW - 1);
            // Pixel values of the nearest four pixels
            BYTE pa = oi[r][c];
            BYTE pb = oi[r][c_];
            BYTE pc = oi[r_][c];
            BYTE pd = oi[r_][c_];
            // Bilinear interpolation
            DWORD val = U1 * V1 * pa
                       + U * V1 * pb
                       + U1 * V * pc
                       + U * V * pd;
            xi[ri][ci] = (val + (1 << (CAST_BITS - 1))) >> CAST_BITS;
            // xi[ri][ri] = 255;
        }
    }
    return ximg;
}

// Read a bitmap, 8 bits image only.
BITMAP bmRead(const char* filename) {
    // Open file stream, binary read mode.
    FILE* pImg = fopen(filename, "rb");
    // File existence check
    if (!pImg) {
        perror("[bmRead] Image file opening failed.");
        exit(EXIT_FAILURE);
    }
    /* Read bitmap, create a bitmap struct.
     * The bitmap file structure:
     * - BITMAPFILEHEADER
     * - BITMAPINFOHEADER
     * - RGBQUAD array
     * - Color-index array
     */
    BITMAP bm;
    // Read BITMAPFILEHEADER.
    fread(&(bm.bmfh), sizeof(BITMAPFILEHEADER), 1, pImg);
    // Fetch the position of the color-index array.
    fpos_t bmciaStart = (fpos_t) bm.bmfh.bfOffBits;
    // Read BITMAPINFO.
    // Read BITMAPINFOHEADER.
    fread(&(bm.bmi.bmiHeader), sizeof(BITMAPINFOHEADER), 1, pImg);
    // Assertion: 8 bits image.
    assert(bm.bmi.bmiHeader.biBitCount == 8);
    // Assertion: Bottom-up DIB
    assert(bm.bmi.bmiHeader.biHeight > 0);
    // Fetch current position.
    fpos_t bmiHeaderEnd = 0;
    fgetpos(pImg, &bmiHeaderEnd);
    // Read RGBQUAD array.
    // Calculate the size of the RGBQUAD array.
    size_t sizergbquad = bmciaStart - bmiHeaderEnd;
    // Allocate memory for the RGBQUAD array
    size_t numrgbquad = sizergbquad / sizeof(RGBQUAD);
    bm.bmi.bmiColors = calloc(numrgbquad, sizeof(RGBQUAD));
    // Assertion: allocation succeed.
    assert(bm.bmi.bmiColors != NULL);
    // Start reading
    fread(bm.bmi.bmiColors, sizeof(RGBQUAD), numrgbquad, pImg);
    // Read color-index array.
    // Allocate memory for the color-index array.
    size_t sizepix = sizeof(BYTE) * bm.bmi.bmiHeader.biHeight
                     * bm.bmi.bmiHeader.biWidth;
    size_t sizecia = sizeof(BYTE*) * bm.bmi.bmiHeader.biHeight
                     + sizepix;
    bm.bmcia = malloc(sizecia);
    // Assertion: allocation succeed.
    assert(bm.bmcia != NULL);
    /* The first part is an array of pointers to pointers to rows.
     * The second part is the actual data, referenced by
     * aforementioned row pointers.
     */
    // Set the pointers to the correct positions
    size_t row = bm.bmi.bmiHeader.biHeight - 1;
    bm.bmcia[row] = (BYTE*) (bm.bmcia + bm.bmi.bmiHeader.biHeight);
    for (; row != SIZE_MAX;) {
        bm.bmcia[row] = bm.bmcia[row--]
                        + bm.bmi.bmiHeader.biWidth;
    }
    // Start reading
    fread(bm.bmcia[bm.bmi.bmiHeader.biHeight - 1],
          sizepix, 1, pImg);
    // Check end of file.
    // I don't know why there were two bytes left at the end of the file.
    // fseek(pImg, 2, SEEK_CUR);
    // assert(fgetc(pImg) == EOF);
    // Close file
    fclose(pImg);
    return bm;
}

// Release the memory previously allocated.
void bmDel(const PBITMAP pbm) {
    // Deallocates the memory and dereferences the pointers.
    free(pbm->bmi.bmiColors);
    pbm->bmi.bmiColors = NULL;
    free(pbm->bmcia);
    pbm->bmcia = NULL;
}

// Save a bitmap to a file
void bmSave(const PBITMAP pbm, const char* filename) {
    // Open file stream, binary write mode.
    FILE* pImg = fopen(filename, "wb");
    // File existence check.
    if (!pImg) {
        perror("[bmSave] Image saving failed.");
        exit(EXIT_FAILURE);
    }
    // Save BITMAPFILEHEADER.
    fwrite(&(pbm->bmfh), sizeof(BITMAPFILEHEADER), 1, pImg);
    // Fetch the position of the color-index array.
    fpos_t bmciaStart = (fpos_t) pbm->bmfh.bfOffBits;
    // Save BITMAPINFOHEADER.
    fwrite(&(pbm->bmi.bmiHeader), sizeof(BITMAPINFOHEADER), 1, pImg);
    // Fetch current position.
    fpos_t bmiHeaderEnd = 0;
    fgetpos(pImg, &bmiHeaderEnd);
    // Save RGBQUAD array.
    // Calculate the size of the RGBQUAD array.
    size_t sizergbquad = bmciaStart - bmiHeaderEnd;
    // Start writing
    fwrite(pbm->bmi.bmiColors, sizergbquad, 1, pImg);
    // Write color-index array.
    // Calculate the size of color-index array.
    size_t sizepix = sizeof(BYTE) * pbm->bmi.bmiHeader.biHeight
                     * pbm->bmi.bmiHeader.biWidth;
    // Start writing
    fwrite(pbm->bmcia[pbm->bmi.bmiHeader.biHeight - 1],
           sizepix, 1, pImg);
    // Close file
    fclose(pImg);
}
