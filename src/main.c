/**
 * @file main.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Task 6 main logic.
 * @version 0.2
 * @date 2021-01-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// DSP/BIOS API
#include <std.h>
#include <log.h>
#include <sio.h>
#include <mbx.h>
#include <tsk.h>
// Custom headers
#include "DSP-HWcfg.h"

// Number of messages
const int NUM_MSGS = 3;
const int TIMEOUT = 1;

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

// Main logic
Void main(void) {
    /* fall into DSP/BIOS idle loop */
    return;
}

Void readRandChar(Arg id_arg) {
    MsgObj msg;
    Int id = ArgToInt(id_arg);
    LOG_printf(&randCharLog, "[readRandChar](%d) spawned.", id);
    while (TRUE) {
        // Wait for mailbox
        if (MBX_pend(&mbx, &msg, TIMEOUT) == FALSE) {
            LOG_printf(&randCharLog, "[readRandChar](%d) Mailbox timeout.", id);
            break;
        }
        LOG_printf(&randCharLog,
                   "[readRandChar](%d) Read '%c' form (%d).", id, msg.val, msg.id);
    }
    LOG_printf(&randCharLog, "[readRandChar](%d) died.");
}

Void genRandChar(Arg id_arg) {
    MsgObj msg;
    Int cMsg;
    Int id = ArgToInt(id_arg);
    LOG_printf(&randCharLog, "[genRandChar](%d) spawned.", id);
    for (cMsg = 0; cMsg < NUM_MSGS; ++cMsg) {
        msg.id = id;
        msg.val = 'a' + cMsg;
        if (MBX_post(&mbx, &msg, TIMEOUT) == FALSE) {
            LOG_printf(&randCharLog, "[genRandChar](%d) Mailbox full.", id);
            continue;
        }
        LOG_printf(&randCharLog,
                   "[genRandChar](%d) is writing '%c'.", id, msg.val);
    }
    LOG_printf(&randCharLog, "[genRandChar](%d) died.", id);
}
