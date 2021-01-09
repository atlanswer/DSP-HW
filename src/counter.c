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

Uns counter = 0;

Void incLogCounter(Void) {
    ++counter;
    LOG_printf(&ctrLog, "[incLogCounter] Counter = %d.", counter);
}
