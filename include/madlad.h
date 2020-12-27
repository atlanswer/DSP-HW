/**
 * @file madlad.h
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Matrix laboratory, but writes as MADLAD.
 * @version 0.3
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef _MADLAD_H_
#define _MADLAD_H_

/**
 * @brief Buffers.
 * Matrix size: 352 * 288 = 101376
 * Row: 352 * 288 / 4 = 25344
 * Loop count: 352 * 288 / 4 / 4 = 6336
 * @see https://stackoverflow.com/questions/1674032/static-const-vs-define-vs-enum
 * 
 */
enum { H_ROW = 4, H_COL = 4,
       MATSIZE = 352 * 288,
       S_ROW = MATSIZE / 4,
       LCOUNT = S_ROW / 4};
extern short src[S_ROW][H_COL];
extern short buf[H_ROW][H_COL];
extern short dst[S_ROW][H_COL];
// Transformation matrix
extern const short H[H_ROW][H_COL];
// Transform
void transform(void);
// Helper functions
void parseYUV(const char* restrict const YUVPATH);
void writeYUV(const char* restrict const YUVPATH);

#endif /** _MADLAD_H_ **/
