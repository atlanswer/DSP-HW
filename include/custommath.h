/**
 * @file custommath.h
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Common mathematical functions.
 * @version 0.1
 * @date 2020-11-19
 * 
 * @copyright Copyright (c) 2020
 * @see https://www.khronos.org/files/opencl-quick-reference-card.pdf
 * 
 */

#ifndef _CUSTOM_MATH_H_
#define _CUSTOM_MATH_H_

/**
 * @brief Macro function, determine if odd or not.
 * 
 */
#define is_odd(x) x & 1 

/**
 * @brief Min of x and y.
 * 
 * @param x 
 * @param y 
 * @return int 
 */
int min(int x, int y);

/**
 * @brief Round integer to nearest even integer.
 * 
 * @param arg 
 * @return int 
 */
int rint(float arg);

#endif /* _CUSTOM_MATH_H_ */
