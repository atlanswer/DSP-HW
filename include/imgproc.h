/**
 * @file imgproc.h
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Color conversion function.
 * @version 0.1
 * @date 2020-12-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <math.h>

#ifndef _IMGPROC_H_
#define _IMGPROC_H_

void cvtColor_C(unsigned char const Y, unsigned char const Cb, unsigned char const Cr,
                unsigned char* const R, unsigned char* const G, unsigned char* const B);

void cvtColor(unsigned char const Y, unsigned char const Cb, unsigned char const Cr,
              unsigned char* const R, unsigned char* const G, unsigned char* const B);

#endif /** _IMGPROC_H_ **/
