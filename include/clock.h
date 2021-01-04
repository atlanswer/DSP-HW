/**
 * @file clock.h
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Cycle counter.
 * @version 0.2
 * @date 2021-01-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <time.h>

#ifndef _CLOCK_H_
#define _CLOCK_H_

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

#endif /** _CLOCK_H_ **/
