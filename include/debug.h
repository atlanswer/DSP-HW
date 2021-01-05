/**
 * @file debug.h
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Debug helper functions.
 * @version 0.1
 * @date 2020-12-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdarg.h>

#ifndef _DEBUG_H_
#define _DEBUG_H_

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
#endif /** DEBUG **/

#endif /** _DEBUG_H_ **/
