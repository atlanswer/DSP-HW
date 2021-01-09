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

#ifndef _RANDCHAR_H_
#include "randChar.h"
#endif /* _RANDCHAR_H_ */

const int NUM_MSGS = 10;
const int TIMEOUT = 10;

Void readRandChar(Arg id_arg) {
    Int id = ArgToInt(id_arg);
    LOG_printf(&randCharLog, "[readRandChar](%d) spawned.", id);
    MsgObj msg;
    while (TRUE) {
        // Wait for mailbox
        if (MBX_pend(&mbx, &msg, TIMEOUT) == FALSE) {
            LOG_printf(&randCharLog, "[readRandChar](%d) timeout.", id);
            break;
        }
        LOG_printf(&randCharLog,
                   "[readRandChar](%d) read '%c' form genRandChar(%d).", id, msg.val, msg.id);
        TSK_yield();
    }
    LOG_printf(&randCharLog, "[readRandChar](%d) died.");
    TSK_exit();
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
        TSK_yield();
    }
    LOG_printf(&randCharLog, "[genRandChar](%d) died.", id);
    TSK_exit();
}
