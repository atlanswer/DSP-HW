/**
 * @file randChar.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Generate and log random characters.
 * @version 0.1
 * @date 2021-01-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// DSP/BIOS API
#include <std.h>
#include <log.h>
#include <mbx.h>
#include <tsk.h>

#include "DSP-HWcfg.h"

#ifndef _RANDCHAR_H_
#define _RANDCHAR_H_

// Number of messages
extern const int NUM_MSGS;
extern const int TIMEOUT;

/**
 * @brief Message object
 * 
 */
typedef struct MsgObj {
    // Writer task id.
    Int     id;
    // Message value.
    Char    val;
} MsgObj, *pMsg;

Void readRandChar(Arg id_arg);
Void genRandChar(Arg id_arg);

#endif /* _RANDCHAR_H_ */
