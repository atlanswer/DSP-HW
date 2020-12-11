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

#include <math.h>

#ifndef _CUSTOM_WINDEF_H_
#include "customwindef.h"
#endif /* _CUSTOM_WINDEF_H_ */
#ifndef _CUSTOM_MATH_H_
#include "custommath.h"
#endif /* _CUSTOM_MATH_H_ */

#ifndef _IMGPROC_H_
#define _IMGPROC_H_

/**
 * @brief WIP
 * @see https://github.com/opencv/opencv/blob/master/modules/imgproc/src/resize.cpp#L905
 * 
 */
extern const INT INTER_RESIZE_COEF_BITS;
extern const INT INTER_RESIZE_COEF_SCALE;
extern const INT CAST_BITS;

/**
 * @brief Resize an image using bilinear interpolation.
 * 
 * @param src Input image array
 * @param dst Output image array
 * @param oW Input image width
 * @param oH Input image height
 * @param nW Output image width
 * @param nH Output image height
 * @param scale Resize factor
 * 
 * @warning Only capable of 8-bit greyscale image.
 * 
 * Inspired by OpenCL's implementation resizeNN.
 * @see https://github.com/opencv/opencv/blob/master/modules/imgproc/src/opencl/resize.cl
 *
 */
void resize(BYTE** const src, BYTE** const dst,
            const LONG oW, const LONG oH,
            const LONG nW, const LONG nH,
            const float scale);

#endif /* _IMGPROC_H_ */
