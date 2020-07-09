/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Examples 5,4,1 02-08-2010 (biosEx-j14)
 */
/*
 *  ======== clk.c =======
 *  In this example, a task goes to sleep # number of ticks and 
 *  prints the time after it wakes up.
 *
 */

#include <std.h>

#include <log.h>
#include <clk.h>
#include <tsk.h>
#include <gbl.h>

#include "clkcfg.h"

/*
 *  ======== main ========
 */
Void main()
{
    LOG_printf(&trace, "clk example started.\n");
}

Void taskFxn(Arg value_arg)
{
    Int value = ArgToInt (value_arg); 
    LgUns freq; 
    Float timeout, milliSecsPerIntr, cycles;

    LOG_printf(&trace, "The time in task is: %d ticks", (Int)TSK_time());

    /* get frequency of platform */    
    freq = GBL_getFrequency();

    /* get cpu cycles per ltime interrupt */
    cycles = CLK_cpuCyclesPerLtime();
    
    /* computer milliseconds per ltime interrupt */
    milliSecsPerIntr = cycles/(Float)freq;

    /* compute timeout */
    timeout = value/milliSecsPerIntr;

    LOG_printf(&trace, "task going to sleep for %d ticks... ", (Int)timeout);

    TSK_sleep((LgUns)timeout);

    LOG_printf(&trace, "...awake! Time is: %d ticks", (Int)TSK_time());
}
