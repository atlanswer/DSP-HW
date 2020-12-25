/**
 * @file madlad.h
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Matrix laboratory, but writes as MADLAD.
 * @version 0.1
 * @date 2020-12-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <file.h>
#include "debug.h"

#ifndef _MADLAD_H_
#define _MADLAD_H_

/**
 * @brief File access permission
 * @see https://man7.org/linux/man-pages/man2/open.2.html
 */
#define S_IRWXU 00700
#define S_IRUSR 00400
#define S_IWUSR 00200

// Buffer
extern unsigned char mat[25344][4] = {0};

// Helper functions
void parseYUV(const char* restrict const YUVPATH);
void printMAT(short MAT[][4], unsigned rows);

#endif /** _MADLAD_H_ **/
