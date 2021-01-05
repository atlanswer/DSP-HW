/**
 * @file imgproc.h
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Image processing algorithms.
 * @version 0.3
 * @date 2021-01-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <math.h>

#ifndef _CUSTOM_WINDEF_H_
#include "customwindef.h"
#endif /* _CUSTOM_WINDEF_H_ */
#ifndef _CUSTOM_WINGDI_H_
#include "customwingdi.h"
#endif /* _CUSTOM_WINGDI_H_ */
#ifndef _CLOCK_H_
#include "clock.h"
#endif /* _CLOCK_H_ */
#ifndef _DEBUG_H_
#include "debug.h"
#endif /* _DEBUG_H_ */

#ifndef _IMGPROC_H_
#define _IMGPROC_H_

/**
 * @brief Median filter, 1D, N = 3.
 * 
 * @param src Input image array
 * @param dst Output image array
 * @param oW Input image width
 * @param oH Input image height
 * 
 * @warning Only capable of 8-bit greyscale image.
 *
 */
void medfilt3(BYTE** const restrict src,
              BYTE** const restrict dst,
              const LONG oW, const LONG oH);

/**
 * @brief Median filter, 1D, N = 5.
 * 
 * @param src Input image array
 * @param dst Output image array
 * @param oW Input image width
 * @param oH Input image height
 * 
 * @warning Only capable of 8-bit greyscale image.
 *
 */
void medfilt5(BYTE** const restrict src,
              BYTE** const restrict dst,
              const LONG oW, const LONG oH);

/**
 * @brief Reconstruct a image using median filter.
 * 
 * @param pbm The pointer to the original image.
 * @param N Filter size (3 or 5).
 * @return BITMAP The reconstructed image.
 * 
 */
BITMAP medfilt2(const PBITMAP restrict pbm, const int N);

#endif /* _IMGPROC_H_ */
