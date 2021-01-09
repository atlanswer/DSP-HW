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
const int NUM_MSGS = 100;
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
    Int id = ArgToInt(id_arg);
    LOG_printf(&randCharLog, "[readRandChar](%d) spawned.", id);
    MsgObj msg;
    while (TRUE) {
        // Wait for mailbox
        if (MBX_pend(&mbx, &msg, TIMEOUT) == FALSE) {
            LOG_printf(&randCharLog, "[readRandChar](%d) Mailbox timeout.", id);
            break;
        }
        LOG_printf(&randCharLog,
                   "[readRandChar](%d) read '%c' form genRandChar(%d).", id, msg.val, msg.id);
    }
    LOG_printf(&randCharLog, "[readRandChar](%d) died.");
}

Void genRandChar(Arg id_arg) {
    Int id = ArgToInt(id_arg);
    LOG_printf(&randCharLog, "[genRandChar](%d) spawned.", id);
    MsgObj msg;
    Int cMsg;
    Char* buf;
    Int status = SIO_staticbuf(&SIO_rand, (Ptr*) &buf);
    if (status < SYS_OK) {
        SYS_abort("[genRandChar](%d) Could not acquire static frame.", id);
    }
    for (cMsg = 0; cMsg < NUM_MSGS; ++cMsg) {
        msg.id = id;
        if (SIO_get(&SIO_rand, (Ptr*) &buf) < 0) {
            SYS_abort("[genRandChar](%d) Error reading buffer.", id);
        }
        if (buf[0] > 'Z') {
            buf[0] = buf[0] - 'Z' + '`';
        }
        msg.val = buf[0];
        if (MBX_post(&mbx, &msg, TIMEOUT) == FALSE) {
            LOG_printf(&randCharLog,
                       "[genRandChar](%d) Mailbox full till timeout.", id);
            continue;
        }
        LOG_printf(&randCharLog,
                   "[genRandChar](%d) is writing '%c'.", id, msg.val);
    }
    LOG_printf(&randCharLog, "[genRandChar](%d) died.", id);
}
