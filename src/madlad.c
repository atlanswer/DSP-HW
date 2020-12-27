/**
 * @file madlad.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Optimized matrix operation.
 * @version 0.3
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _MADLAD_H_
#include "madlad.h"
#endif /** _MADLAD_H_ **/

short src[S_ROW][H_COL] = {0};
short buf[H_ROW][H_COL] = {0};
short dst[S_ROW][H_COL] = {0};
const short H[H_ROW][H_COL] = {
    {1,  1,  1,  1},
    {2,  1, -1, -2},
    {1, -1, -1,  1},
    {1, -2,  2, -1}
};

void transform(void) {
    int i, r, c, j;
    for (i = 0; i < LCOUNT; ++i) {
        // X * H'
        for (r = 0; r < H_ROW; ++r) {
            for (c = 0; c < H_COL; ++c) {
                buf[r][c] = 0;
                for (j = 0; j < H_COL; ++j) {
                    buf[r][c] += src[r + 4 * i][j] * H[c][j];
                }
            }
        }
        // H * X * H'
        for (r = 0; r < H_ROW; ++r) {
            for (c = 0; c < H_COL; ++c) {
                for (j = 0; j < H_COL; ++j) {
                    dst[r + 4 * i][c] += H[r][j] * buf[j][c];
                }
            }
        }
    }
}

void parseYUV(const char* restrict const YUVPATH) {
    // Open file for IO: Binary readonly.
    FILE* fYUV = fopen(YUVPATH, "rb");
    if (!fYUV) {
        perror("[parseYUV] Failed to open the YUV file.");
        exit(EXIT_FAILURE);
    }
    short* restrict buffer = (void*) src;
    setvbuf(fYUV, NULL, _IOFBF, MATSIZE);
    int bytesRead = 0, i;
    unsigned char buf;
    for (i = 0; i < MATSIZE; ++i) {
        bytesRead += fread(&buf, 1, 1, fYUV);
        buffer[i] = (short) buf;
    }
    printf("[parseYUV] %d bytes read.\n", bytesRead);
    // Close file.
    int status = fclose(fYUV);
    if (status) {
        perror("[parseYUV] Failed on closing the file.");
        exit(EXIT_FAILURE);
    }
}

void writeYUV(const char* restrict const YUVPATH) {
    // Open file for IO: Binary writeonly.
    FILE* fYUV = fopen(YUVPATH, "wb");
    if (!fYUV) {
        perror("[writeYUV] Failed to open the output file.");
        exit(EXIT_FAILURE);
    }
    const char* buffer = (char*) dst[0];
    setvbuf(fYUV, NULL, _IOFBF, MATSIZE * 2);
    int bytesWritten = fwrite(buffer, 2, MATSIZE, fYUV);
    printf("[writeYUV] %d halfwords written.\n", bytesWritten);
    int status = fclose(fYUV);
    if (status) {
        perror("[writeYUV] Failed on closing the output file.");
        exit(EXIT_FAILURE);
    }
}
