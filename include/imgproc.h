/**
 * @file imgproc.h
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Image processing algorithms.
 * @version 0.2
 * @date 2020-12-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <math.h>
#include <time.h>

#ifndef _CUSTOM_WINDEF_H_
#include "customwindef.h"
#endif /* _CUSTOM_WINDEF_H_ */
#ifndef _CUSTOM_MATH_H_
#include "custommath.h"
#endif /* _CUSTOM_MATH_H_ */

#ifndef _IMGPROC_H_
#define _IMGPROC_H_

/**
 * @brief DEBUG only printf function.
 * Usage: dprintf(("message %d", var))
 * The double-parentheses are crucial.
 * 
 */
#ifdef DEBUG
#define dprintf(x) debugPrintf x;
#else
#define dprintf(x) do { if (0) debugPrintf x; } while (0)
#endif

/**
 * @brief WIP, C optimization.
 * @see https://github.com/opencv/opencv/blob/master/modules/imgproc/src/resize.cpp#L905
 * 
 */
extern const INT INTER_RESIZE_COEF_BITS;
extern const INT INTER_RESIZE_COEF_SCALE;
extern const INT CAST_BITS;

/**
 * @brief CPU time stamp counter control register. 
 * 
 */
extern cregister volatile unsigned int TSCL;
extern cregister volatile unsigned int TSCH;

/**
 * @brief Get the current CPU cycle stamp.
 * 
 * @return clock_t: unsigned int
 */
clock_t clock(void);

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
 * Inspired by OpenCL's implementation resizeLN.
 * @see https://github.com/opencv/opencv/blob/master/modules/imgproc/src/opencl/resize.cl#L176-L208
 *
 */
void resize(BYTE** const src, BYTE** const dst,
            const LONG oW, const LONG oH,
            const LONG nW, const LONG nH,
            const float inv_scale);

#endif /* _IMGPROC_H_ */
