/**
 * @file customwingdi.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Custom bitmap processing functions.
 * @version 0.1
 * @date 2020-11-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _CUSTOM_WINGDI_H_
#include "customwingdi.h"
#endif /* _CUSTOM_WINGDI_H_ */

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
    // https://docs.microsoft.com/en-us/windows/win32/gdi/storing-an-image
    // The width must be DWORD aligned unless the bitmap is RLE 
    // compressed.
    LONG storageWidth = ((nWidth * 8 + 31) & ~31) / 8;
    bm.bmi.bmiHeader.biSizeImage = storageWidth * nHeight;
    // Set RGBQUAD array.
    bm.bmi.bmiColors = pbmo->bmi.bmiColors;
    // Set color-index array.
    // Allocate memory for the color-index array.
    size_t sizepix = sizeof(BYTE) * bm.bmi.bmiHeader.biHeight
                     * storageWidth;
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
    for (; row != 0;) {
        bm.bmcia[row] = bm.bmcia[row--] + storageWidth;
    }
    // Calculate the file size.
    bm.bmfh.bfSize = bm.bmi.bmiHeader.biSizeImage
                     + bm.bmfh.bfOffBits;

    return bm;
}

BITMAP StretchBlt(const PBITMAP pbm, float scale) {
    LONG oW = pbm->bmi.bmiHeader.biWidth;
    LONG oH = pbm->bmi.bmiHeader.biHeight;
    LONG nW = ceil(oW * scale);
    LONG nH = ceil(oH * scale);
    BITMAP ximg = CreateBitmap(nW, nH, pbm);
    // Interpolation process.
    resize(pbm->bmcia, ximg.bmcia, oW, oH, nW, nH, scale);
    return ximg;
}

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
    for (; row != 0;) {
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

void bmDel(const PBITMAP pbm) {
    // Deallocates the memory and dereferences the pointers.
    free(pbm->bmi.bmiColors);
    pbm->bmi.bmiColors = NULL;
    free(pbm->bmcia);
    pbm->bmcia = NULL;
}

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
    LONG storageWidth = ((pbm->bmi.bmiHeader.biWidth * 8 + 31) & ~31) / 8;
    size_t sizepix = sizeof(BYTE) * pbm->bmi.bmiHeader.biHeight
                     * storageWidth;
    // Start writing
    fwrite(pbm->bmcia[pbm->bmi.bmiHeader.biHeight - 1],
           sizepix, 1, pImg);
    // Close file
    fclose(pImg);
}
