/**
 * @file counter.c
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief A counter that increses every second.
 * @version 0.1
 * @date 2021-01-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _COUNTER_H_
#include "counter.h"
#endif /* COUNTER_H_ */

Void incLogCounter(Void) {
    Uns counter = 0;
    LgUns currtimes = 0;
    while (TRUE) {
        currtimes = CLK_getltime();
        LOG_printf(&ctrLog, "T: 0x%x", currtimes);
        TSK_yield();
    }
}

Void my_prd(Void) {
    LOG_printf(&ctrLog, "In periodic function my_prd()");
}
