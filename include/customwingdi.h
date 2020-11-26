/**
 * @file customwingdi.h
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Bitmap Header Definition.
 * @version 0.1
 * @date 2020-11-19
 * 
 * @copyright Copyright (c) 2020
 * @see https://docs.microsoft.com/en-us/windows/win32/gdi/bitmaps
 * 
 */

// System headers
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
// Custom headers
#ifndef _CUSTOM_WINDEF_H_
#include "customwindef.h"
#endif /* _CUSTOM_WINDEF_H_ */
#ifndef _IMGPROC_H_
#include "imgproc.h"
#endif /* _IMGPROC_H_ */

#ifndef _CUSTOM_WINGDI_H_
#define _CUSTOM_WINGDI_H_

/**
 * @brief Structure-Layout Pragma
 * Pushes the current alignment setting on an internal
 * stack and then optionally sets the new alignment.
 * @see https://en.cppreference.com/w/c/preprocessor/impl
 * 
 */
#pragma pack(push, 1)

/**
 * Information about the type, size,
 * and layout of a file that contains a DIB.
 * 
 * @brief BITMAPFILEHEADER structure
 * @see https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
 * 
 */
typedef struct tagBITMAPFILEHEADER {
    /// The file type; must be BM.
    WORD    bfType;
    /// The size, in bytes, of the bitmap file.
    DWORD   bfSize;
    /// Reserved, must be zero.
    WORD    bfReserved1;
    /// Reserved, must be zero.
    WORD    bfReserved2;
    /**
     * The offset, in bytes, from the
     * beginning of the BITMAPFILEHEADER
     * structure to the bitmap bits.
     * 
     */
    DWORD bfOffBits; 
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

/**
 * Contains information about
 * the dimensions and color format of a DIB.
 * 
 * @brief BITMAPINFOHEADER structure
 * @see https://docs.microsoft.com/en-us/previous-versions//dd183376(v=vs.85)
 * 
 */
typedef struct tagBITMAPINFOHEADER {
    /// The number of bytes required by the structure.
    DWORD   biSize;
    /// The width of the bitmap, in pixels.
    LONG    biWidth;
    /// The height of the bitmap, in pixels.
    LONG    biHeight;
    /**
     * The number of planes for the target device.
     * This value must be set to 1.
     */
    WORD    biPlanes;
    /// The number of bits-per-pixel.
    WORD    biBitCount;
    /// The type of compression for a compressed bottom-up bitmap.
    DWORD   biCompression;
    /// The size, in bytes, of the image. This may be set to zero for BI_RGB bitmaps.
    DWORD   biSizeImage;
    /// The horizontal resolution, in pixels-per-meter, of the target device for the bitmap.
    LONG    biXPelsPerMeter;
    /// The vertical resolution, in pixels-per-meter, of the target device for the bitmap.
    LONG    biYPelsPerMeter;
    /// The number of color indexes in the color table that are actually used by the bitmap.
    DWORD   biClrUsed;
    /// The number of color indexes that are required for displaying the bitmap.
    DWORD   biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

/**
 * Describes a color consisting of relative
 * intensities of red, green, and blue.
 * 
 * @brief RGBQUAD structure
 * @see https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-rgbquad
 * 
 */
typedef struct tagRGBQUAD {
    /// The intensity of blue in the color.
    BYTE    rgbBlue;
    /// The intensity of green in the color.
    BYTE    rgbGreen;
    /// The intensity of red in the color.
    BYTE    rgbRed;
    /// This member is reserved and must be zero.
    BYTE    rgbReserved;
} RGBQUAD, *PRGBQUAD;

/**
 * Defines the dimensions and color information for a DIB.
 * 
 * @brief BITMAPINFO structure
 * @see https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfo
 * 
 */
typedef struct tagBITMAPINFO {
    /**
     * A BITMAPINFOHEADER structure that contains
     * information about the dimensions of color format.
     */
    BITMAPINFOHEADER    bmiHeader;
    /// An array of RGBQUAD.
    PRGBQUAD            bmiColors;
} BITMAPINFO, *PBITMAPINFO;

/**
 * Defines a bitmap.
 * @warning Custom structure, works only for 8 bits bitmap.
 * @brief BITMAP structure
 * 
 */
typedef struct tagBITMAP {
    BITMAPFILEHEADER    bmfh;
    BITMAPINFO          bmi;
    /**
     * @brief Bitmap color-index array
     * @see https://docs.microsoft.com/en-us/windows/win32/gdi/bitmap-storage
     */
    BYTE**              bmcia;
} BITMAP, *PBITMAP;

/**
 * @brief Create a Bitmap object.
 * 
 * @param nWidth The bitmap width, in pixels.
 * @param nHeight The bitmap height, in pixels.
 * @param pbmo A pointer to an existing bitmap,
 *  new image copys its properties.
 * @return BITMAP 
 * 
 * @see https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createbitmap
 * @warning The number of planes must be set to 1,
 *  The number of bits-per-pixel must be 8.
 * 
 */
BITMAP CreateBitmap(int nWidth, int nHeight,
                    const PBITMAP pbmo);

/**
 * @brief Resize a image using bilinear interpolation.
 * 
 * @param pbm The pointer to the original image.
 * @param scale Resize factor.
 * @return BITMAP The interpolated image.
 * 
 * @see https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-stretchblt
 * @warning This function has nothing to do with the wingdi.h version.
 */
BITMAP StretchBlt(const PBITMAP pbm, float scale);

// Custom healper functions:

/**
 * @brief Read a bitmap file.
 * 
 * @param filename The bitmap filepath.
 * @return BITMAP The formatted image struct.
 *  
 * @warning 8 bits image only.
 */
BITMAP bmRead(const char* filename);

/**
 * @brief Destory a bitmap, release the memory previously allocated.
 * 
 * @param pbm The pointer to the bitmap struct.
 */
void bmDel(const PBITMAP pbm);

/**
 * @brief Save a bitmap.
 * 
 * @param pbm The pointer to the bitmap struct.
 * @param filename The output filepath 
 */
void bmSave(const PBITMAP pbm, const char* filename);

#endif /* _CUSTOM_WINGDI_H_ */
