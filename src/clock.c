/**
 * @file clock.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _CLOCK_H_
#include "clock.h"
#endif /** _CLOCK_H_ **/

clock_t clock() {
    unsigned int low = TSCL;
    unsigned int high = TSCH;
    if (high) return (clock_t) -1;
    return low;
}
