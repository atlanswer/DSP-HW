/**
 * @file customwindef.h
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Basic Windows Type Definitions.
 * @version 0.1
 * @date 2020-11-19
 * 
 * @copyright Copyright (c) 2020
 * @see https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types
 * 
 */

#ifndef _CUSTOM_WINDEF_H_
#define _CUSTOM_WINDEF_H_

/*
 * TMS320C6000 C/C++ EABI ABI data types:
 * | Type           | Size
 * - char           : 8 bits
 * - short          : 16 bits
 * - int            : 32 bits
 * - long           : 32 bits
 * - __int40_t      : 40 bits
 * - long long      : 64 bits
 * - enum           : 32 bits
 * - float          : 32 bits
 * - double         : 64 bits
 * - long double    : 64 bits
 * - pointers,
 *   references,
 *   pointer to
 *   data members   : 32 bits
 */

/*
 * Windows data types
 * - BYTE       A bytes (8 bits)
 *                  typedef unsigned char BYTE;
 * - WORD       A 16-bit unsigned integer.
 *                  typedef unsigned short WORD;
 * - DWORD      A 32-bit unsigned integer.
 *                  typedef unsigned long DWORD;
 * - LONG       A 32-bit signed integer.
 *                  typedef long LONG;
 * - INT        A 32-bit signed integer.
 *              The range is -2147483648
 *              through 2147483647 decimal.
 *                  typedef int INT;
 * - UINT       An unsigned INT.
 *              The range is 0 through 4294967295 decimal.
 *                  typedef unsigned int UINT;
 * - VOID       Any type.
 *                  #define VOID void
 * - LPVOID     A pointer to any type.
 * - BOOL       A Boolean variable (should be TRUE or FALSE).
 */

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;
typedef int INT;
typedef unsigned int UINT;
#define VOID void
typedef int BOOL;

#endif /* _CUSTOM_WINDEF_H_ */
