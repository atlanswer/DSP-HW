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
// Main logic
Void main(void) {
    LOG_printf(&trace, "Hello world!");
    /* fall into DSP/BIOS idle loop */
    return;
}
