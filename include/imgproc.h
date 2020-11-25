/**
 * @file imgproc.h
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Image processing algorithms.
 * @version 0.1
 * @date 2020-11-25
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _CUSTOM_WINDEF_H_
#include "customwindef.h"
#endif /* _CUSTOM_WINDEF_H_ */

#ifndef _IMGPROC_H_
#define _IMGPROC_H_

/**
 * @brief Resize an image using bilinear interpolation.
 * 
 * @param src Input image array
 * @param dst Output image array
 * @param oW Input image width
 * @param oH Input image height
 * @param nW Output image width
 * @param nH Output image height
 * 
 * @warning Only capable of 8-bit greyscale image.
 */
void resize(const BYTE** const src, BYTE** const dst,
            const LONG oW, const LONG oH,
            const LONG nW, const LONG nH);

#endif /* _IMGPROC_H_ */
