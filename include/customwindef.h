/*
 * customminwindef.h - Basic Windows Type Definitions.
 */

#ifndef _CUSTOM_WINDEF_
#define _CUSTOM_WINDEF_

/*
 * The C6000 compiler defines a size for each data type:
 * - char      : 8 bits
 * - short     : 16 bits
 * - int       : 32 bits
 * - float     : 32 bits
 * - long      : 40 bits
 * - long long : 64 bits
 * - double    : 64 bits
 */

/*
 * Windows data types
 * - BYTE       A bytes (8 bits)
 *              typedef unsigned char BYTE;
 * - WORD       A 16-bit unsigned integer.
 *              typedef unsigned short WORD;
 * - DWORD      A 32-bit unsigned integer.
 *              typedef unsigned long DWORD;
 * - LONG       A 32-bit signed integer.
 *              typedef long LONG;
 * - INT        A 32-bit signed integer.
 *              The range is -2147483648
 *              through 2147483647 decimal.
 * - UINT       An unsigned INT.
 *              The range is 0 through 4294967295 decimal.
 * - VOID       Any type.
 * - LPVOID     A pointer to any type.
 * - BOOL       A Boolean variable (should be TRUE or FALSE).
 */

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;
typedef unsigned int UINT;
#define VOID void
typedef void *LPVOID;
typedef int BOOL;

#endif
