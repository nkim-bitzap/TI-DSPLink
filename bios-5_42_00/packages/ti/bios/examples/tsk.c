/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Examples 5,4,1 02-08-2010 (biosEx-j14)
 */
/*
 *  ======== tsk.c =======
 *  In this example, 3 tasks have been created with the Configuration
 *  Tool.  Each task has a computation loop consisting of a LOG_printf()
 *  followed by a TSK_yield().  This causes a round robin scheduling for
 *  these tasks of equal priority.
 */

#include <std.h>

#include <log.h>
#include <tsk.h>

#include "tskcfg.h"

#define NLOOPS  5

Void task(Arg id_arg);  /* Function for tasks created with Config Tool */ 

/*
 *  ======== main ========
 */
Void main()
{
}

/*
 *  ======== task ========
 */
Void task(Arg id_arg)
{
    Int     id = ArgToInt (id_arg);
    Int     i;
    
    for (i = 0; i < NLOOPS ; i++) {
        LOG_printf(&trace, "Loop %d: Task %d Working", i, id);
        TSK_yield();
    }
    LOG_printf(&trace, "Task %d DONE", id);
}
