/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Examples 5,4,1 02-08-2010 (biosEx-j14)
 */
/*
 *  ======== slice.c ========
 *  This example utilizes time-slice scheduling among three
 *  tasks of equal priority.  A fourth task of higher
 *  priority periodically preempts execution.
 *  
 *  A PRD object drives the time-slice scheduling. Every
 *  millisecond, the PRD object calls TSK_yield()
 *  which forces the current task to relinquish access to
 *  to the CPU.  The time slicing could also be driven by
 *  a CLK object (as long as the time slice was the same interval
 *  as the clock interrupt), or by another hardware
 *  interrupt.
 *
 *  The time-slice scheduling is best viewed in the Execution
 *  Graph with SWI logging and PRD logging turned off.
 *
 *  Because a task is always ready to run, this program
 *  does not spend time in the idle loop.  Calls to IDL_run()
 *  are added to force the update of the Real-Time Analysis
 *  tools.  Calls to IDL_run() are within a TSK_disable(),
 *  TSK_enable() block because the call to IDL_run()
 *  is not reentrant.
 */

#include <std.h>

#include <clk.h>
#include <idl.h>
#include <log.h>
#include <sem.h>
#include <swi.h>
#include <tsk.h>

#include "slicecfg.h"

Void task(Arg id_arg);
Void hi_pri_task(Arg id_arg);
Uns counts_per_us;      /* hardware timer counts per microsecond */

/*
 *  ======== main ========
 */
Void main()
{
    LOG_printf(&trace, "Slice example started!");
    counts_per_us = CLK_countspms() / 1000;
}


/*
 * ======== task ========
 */
Void task(Arg id_arg)
{
    Int id = ArgToInt(id_arg);
    LgUns time;
    LgUns prevtime;

    /*
     * The while loop below simulates the work load of
     * the time sharing tasks
     */
    for (;;) {

        time = CLK_gethtime() / counts_per_us;

        /* print time only every 200 usec */
        if (time >= prevtime + 200) {
            prevtime = time;
            LOG_printf(&trace, "Task %d: time is(us) Ox%x", id, (Int)time);
        }

        /* check for rollover */
        if (prevtime > time) {
            prevtime = time;
        }

        /*
         * pass through idle loop to pump data to the Real-Time
         * Analysis tools
         */
        TSK_disable();
        IDL_run();
        TSK_enable();
    }
}


/*
 * ======== hi_pri_task ========
 */
Void hi_pri_task(Arg id_arg)
{
    Int id = ArgToInt(id_arg);

    for (;;) {
        LOG_printf(&trace, "Task %d here", id);
        SEM_pend(&sem, SYS_FOREVER);
    }
}


Void prdfxn0()
{
    TSK_yield();
}


Void prdfxn1()
{
    SEM_post(&sem);
}


