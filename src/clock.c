/**
 * @file clock.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Cycle counter implementation.
 * @version 0.2
 * @date 2021-01-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _CLOCK_H_
#include "clock.h"
#endif /** _CLOCK_H_ **/

clock_t clock(void) {
    unsigned int low = TSCL;
    unsigned int high = TSCH;
    if (high) return (clock_t) -1;
    return low;
}
