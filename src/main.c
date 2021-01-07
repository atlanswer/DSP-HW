/**
 * @file main.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief Task 6 main logic.
 * @version 0.1
 * @date 2021-01-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// DSP/BIOS API
#include <std.h>
#include <stdlib.h>
#include <log.h>
#include <mbx.h>
#include <tsk.h>
// Custom headers
#include "DSP-HWcfg.h"

// Number of messages
#define NUMMSGS     3
#define TIMEOUT     10

/**
 * @brief Message object
 * 
 */
typedef struct MsgObj {
    // Writer task id.
    Int     id;
    // Message value.
    Char    val;
} MsgObj, *Msg;

Void reader(Void);
Void writer(Arg id_arg);

// Main logic
Void main(void) {
    LOG_printf(&trace, "Hello world!");
    /* fall into DSP/BIOS idle loop */
    return;
}

Void reader(Void)
{
    MsgObj      msg;
    Int         i;

    for (i=0; ;i++) {

        /* wait for mailbox to be posted by writer() */
        if (MBX_pend(&mbx, &msg, TIMEOUT) == 0) {
            LOG_printf(&trace, "timeout expired for MBX_pend()");
            break;
        }

        /* print value */
        LOG_printf(&trace, "read '%c' from (%d).", msg.val, msg.id);
    }
    LOG_printf(&trace, "reader done.");
}

Void writer(Arg id_arg)
{
    MsgObj      msg;
    Int         i;
    Int id =    ArgToInt (id_arg);

    for (i=0; i < NUMMSGS; i++) {
        /* fill in value */
        msg.id = id;
        msg.val = i % NUMMSGS + (Int)('a');

        /* enqueue message */
        MBX_post(&mbx, &msg, TIMEOUT);
       
        LOG_printf(&trace, "(%d) writing '%c' ...", id, (Int)msg.val);

        /* what happens if you call TSK_yield() here? */
        /* TSK_yield(); */
    }

    LOG_printf(&trace, "writer (%d) done.", id);
}
