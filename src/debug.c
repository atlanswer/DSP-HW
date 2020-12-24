/**
 * @file debug.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Debug helper functions.
 * @version 0.1
 * @date 2020-12-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _DEBUG_H_
#include "debug.h"
#endif /** _DEBUG_H_ **/

void debugPrintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}
