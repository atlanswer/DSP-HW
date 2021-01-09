/**
 * @file counter.h
 * @author Atlanswer (atlanswer@gmail.com)
 * @brief A counter that increses every second.
 * @version 0.1
 * @date 2021-01-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// DSP/BIOS API
#include <std.h>
#include <log.h>
#include <tsk.h>
#include <clk.h>

#include "DSP-HWcfg.h"

#ifndef _COUNTER_H_
#define _COUNTER_H_

extern Uns counter;

Void incLogCounter(Void);

#endif /* _COUNTER_H_ */
