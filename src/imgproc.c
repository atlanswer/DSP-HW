/**
 * @file imgproc.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Image processing algorithm implementations.
 * @version 1.0
 * @date 2020-12-25
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdarg.h>

#ifndef _IMGPROC_H_
#include "imgproc.h"
#endif /* _IMGPROC_H_ */

const INT INTER_RESIZE_COEF_BITS = 11;
/// const INT INTER_RESIZE_COEF_SCALE = 1 << INTER_RESIZE_COEF_BITS;
const INT INTER_RESIZE_COEF_SCALE = 1 << 11;
/// const INT CAST_BITS = INTER_RESIZE_COEF_BITS << 1;
const INT CAST_BITS = 11 << 1;

void debugPrintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

clock_t clock() {
    unsigned int low = TSCL;
    unsigned int high = TSCH;
    if (high) return (clock_t) -1;
    return low;
}

// Implementation switch
#ifndef USE_SA_IMPL

void resize(BYTE** const src, BYTE** const dst,
            const LONG oW, const LONG oH,
            const LONG nW, const LONG nH,
            const float inv_scale) {
    /// Row and column index.
    LONG ri, ci;
    // Iterate over rows.
    for (ri = 0; ri < nH; ++ri) {
        dprintf(("\r[resize] Processing row index: %d\n", ri));
        // Convert pixel index to a location in the original image.
        float sr = (ri + 0.5f) * inv_scale - 0.5f;
        // Round towards the origin.
        LONG r = floor(sr);
        // Relative distance
        float u = sr - r;
        // Edge handling
        if (r < 0) {
            r = 0;
            u = 0;
        }
        if (r >= oH) {
            r = oH - 1;
            u = 0;
        }
        #ifdef USE_INT
        u = u * INTER_RESIZE_COEF_SCALE;
        INT U = rint(u);
        INT U1 = rint(INTER_RESIZE_COEF_SCALE - u);
        #endif /** USE_INT **/
        // Round towards the other end, edge case included.
        LONG r_ = min(r + 1, oH - 1);
        // Iterate over columns.
        for(ci = 0; ci < nW; ++ci) {
            float sc = (ci + 0.5f) * inv_scale - 0.5f;
            LONG c = floor(sc);
            float v = sc - c;
            if (c < 0) {
                c = 0;
                v = 0;
            }
            if (c >= oW) {
                c = oW - 1;
                v = 0;
            }
            #ifdef USE_INT
            v = v * INTER_RESIZE_COEF_SCALE;
            INT V = rint(v);
            INT V1 = rint(INTER_RESIZE_COEF_SCALE - v);
            #endif /** USE_INT **/
            LONG c_ = min(c + 1, oW - 1);
            // Fetch pixel values of the nearest four pixels
            BYTE pa = src[r][c];
            BYTE pb = src[r][c_];
            BYTE pc = src[r_][c];
            BYTE pd = src[r_][c_];
            // Bilinear interpolation
            #ifdef USE_INT
            DWORD val = U1 * V1 * pa
                        + U1 * V * pb
                        + U * V1 * pc
                        + U * V * pd;
            // Assign to the output image.
            dst[ri][ci] = (val + (1 << (CAST_BITS - 1))) >> CAST_BITS;
            #else
            float val2 = pa * (1 - u) * (1 - v)
                         + pb * (1 - u) * v
                         + pc * u * (1 - v)
                         + pd * u * v;
            dst[ri][ci] = floor(val2 + 0.5);
            #endif /** USE_INT **/
        }
    }
}

#endif
