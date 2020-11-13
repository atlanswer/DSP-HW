/* customwingdi.h - Bitmap Header Definition */

// System headers
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
// Custom headers
#include "customwindef.h"

#ifndef _CUSTOM_WINGDI_
#define _CUSTOM_WINGDI_
/* Structure-Layout Pragma
 * Pushes the current alignment setting on
 * an internal stack and then optionally
 * sets the new alignment.
 * https://en.cppreference.com/w/c/preprocessor/impl
 */ 
#pragma pack(push, 1)

/* The BITMAPFILEHEADER structure contains information
 * about the type, size, and layout of a file that
 * contains a DIB.
 * https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
 */
typedef struct tagBITMAPFILEHEADER {
    // The file type; must be BM.
    WORD    bfType;
    // The size, in bytes, of the bitmap file.
    DWORD   bfSize;
    // Reserved, must be zero.
    WORD    bfReserved1;
    // Reserved, must be zero.
    WORD    bfReserved2;
    // The offset, in bytes, from the
    // beginning of the BITMAPFILEHEADER
    // structure to the bitmap bits.
    DWORD bfOffBits; 
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

/* The BITMAPINFOHEADER structure contains information
 * about the dimensions and color format of a DIB.
 * https://docs.microsoft.com/en-us/previous-versions//dd183376(v=vs.85)
 */
typedef struct tagBITMAPINFOHEADER {
    // The number of bytes required by the structure.
    DWORD   biSize;
    // The width of the bitmap, in pixels.
    LONG    biWidth;
    // The height of the bitmap, in pixels.
    LONG    biHeight;
    // The number of planes for the target device.
    // This value must be set to 1.
    WORD    biPlanes;
    // The number of bits-per-pixel.
    WORD    biBitCount;
    // The type of compression for a compressed bottom-up bitmap.
    DWORD   biCompression;
    // The size, in bytes, of the image. This may be set to zero for BI_RGB bitmaps.
    DWORD   biSizeImage;
    // The horizontal resolution, in pixels-per-meter, of the target device for the bitmap.
    LONG    biXPelsPerMeter;
    // The vertical resolution, in pixels-per-meter, of the target device for the bitmap.
    LONG    biYPelsPerMeter;
    // The number of color indexes in the color table that are actually used by the bitmap.
    DWORD   biClrUsed;
    // The number of color indexes that are required for displaying the bitmap.
    DWORD   biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

/*
 * The RGBQUAD structure describes a color
 * consisting of relative intensities of
 * red, green, and blue.
 * https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-rgbquad
 */
typedef struct tagRGBQUAD {
    // The intensity of blue in the color.
    BYTE    rgbBlue;
    // The intensity of green in the color.
    BYTE    rgbGreen;
    // The intensity of red in the color.
    BYTE    rgbRed;
    // This member is reserved and must be zero.
    BYTE    rgbReserved;
} RGBQUAD, *PRGBQUAD;

/* The BITMAPINFO structure defines the
 * dimensions and color information for a DIB.
 */
typedef struct tagBITMAPINFO {
    /* A BITMAPINFOHEADER structure that contains
     * information about the dimensions of color format.
     * https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfo
     * MODIFIED
     */
    BITMAPINFOHEADER    bmiHeader;
    // An array of RGBQUAD.
    PRGBQUAD            bmiColors;
} BITMAPINFO, *PBITMAPINFO;

/* The BITMAP structure defines a bitmap.
 * Custom structure, works only for 8 bits bitmap.
 */
typedef struct tagBITMAP {
    BITMAPFILEHEADER    bmfh;
    BITMAPINFO          bmi;
    // Bitmap color-index array.
    // https://docs.microsoft.com/en-us/windows/win32/gdi/bitmap-storage
    BYTE**              bmcia;
} BITMAP, *PBITMAP;

/* Create a bitmap.
 * https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createbitmap
 */
BITMAP CreateBitmap(int nWidth, int nHeight,
                    const PBITMAP pbmo);
/* The GetDIBColorTable function retrieves RGB
 * (red, green, blue) color values from a range
 * of entries in the color table of the DIB section
 * bitmap that is currently selected into a specified
 * device context.
 * https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getdibcolortable
 * MODIFIED
 */
UINT GetDIBColorTable(UINT iStart, UINT cEntries,
                      PRGBQUAD prgbq);
/* The GetDIBits function retrieves the bits of the
 * specified compatible bitmap and copies them into
 * a buffer as a DIB using the specified format.
 * https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getdibits
 * MODIFIED
 */
int GetBIBits(PBITMAP pbm, UINT start, UINT cLines,
              LPVOID pvBits, PBITMAPINFO pbmi);
/* The SetDIBits function sets the pixels in a
 * compatible bitmap (DDB) using the color data
 * found in the specified DIB.
 * https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setdibits
 * MODIFIED
 */
int SetDIBits(PBITMAP pbm, UINT start, UINT cLines,
              const VOID* pBits, const PBITMAPINFO pbmi);
/* The StretchBlt function copies a bitmap from a
 * source rectangle into a destination rectangle,
 * stretching or compressing the bitmap to fit
 * the dimensions of the destination rectangle, if necessary.
 * https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-stretchblt
 * HEAVILY MODIFIED: Using bilinear method to
 * interpolate the image.
 */
BITMAP StretchBlt(PBITMAP, float);

// Custom healper functions:
// Read a bitmap.
BITMAP bmRead(const char* filename);
// Destory a bitmap
void bmDel(const PBITMAP pbm);
// Save a bitmap
void bmSave(const PBITMAP pbm, const char* filename);

#endif
