/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Examples 5,4,1 02-08-2010 (biosEx-j14)
 */
/*
 *  ======== streaming.c ========
 *  In this program two tasks are created that exchange data through a pipe
 *  device. The source task reads sine wave data from a DGN device through
 *  a DTR device stacked on the sine device, and then writes it to a pipe
 *  device. The sink task reads the data from the pipe device and writes it
 *  to the printData DGN device. The data exchange between the tasks and
 *  the devices is done in a device independent fashion using the SIO module
 *  APIs.
 *
 *  The streams in this example follow the SIO_STANDARD streaming model and
 *  are created with the Configuration Tool.
 *
 */

#include <std.h>

#include <dtr.h>
#include <log.h>
#include <mem.h>
#include <sio.h>
#include <sys.h>
#include <tsk.h>

#include "streamingcfg.h"

#define BUFSIZE 128

/* Parameters for the stacking device  "/scale" */
DTR_Params DTR_PRMS = {
    10,   /* Scaling factor */
    NULL,
    NULL
};

Void source(Arg nloops_arg);    /* function body for sourceTask above */
Void sink(Arg nloops_arg);      /* function body for sinkTask above */

static Void doStreaming(SIO_Handle input, SIO_Handle output, Uns nloops);

Void DGN_print2log(Arg arg, Ptr addr, Uns nbytes);

/*
 *  ======== main ========
 */
Void main()
{
    LOG_printf(&trace, "Start SIO example #5");
}

/*
 *  ======== source ========
 *  This function forms the body of the sourceTask TSK thread.
 */
Void source(Arg nloops_arg)
{
    Int nloops = ArgToInt (nloops_arg);

    SIO_Handle input = &inStreamSrc;
    SIO_Handle output = &outStreamSrc;
    
    /* Do I/O */
    doStreaming(input, output, nloops);
}

/*
 *  ======== sink ========
 *  This function forms the body of the sinkTask TSK thread.
 */
Void sink(Arg nloops_arg)
{
    Int nloops = ArgToInt (nloops_arg);

    SIO_Handle input = &inStreamSink;
    SIO_Handle output = &outStreamSink;
    
    /* Do I/O */
    doStreaming(input, output, nloops);

    LOG_printf(&trace, "End SIO example #5");
}

/*
 *  ======== doStreaming ========
 *  I/O function for the sink and source tasks.
 */
static Void doStreaming(SIO_Handle input, SIO_Handle output, Uns nloops)
{
    Ptr    buf;
    Int    i, nbytes;
    
    if ( SIO_staticbuf(input, &buf) == 0) {
        SYS_abort("Error reading buffer");
    }
    
    for (i = 0; i < nloops; i++) {
        if ((nbytes = SIO_get(input, &buf)) < 0) {
            SYS_abort("Error reading buffer %d", i);
        }
        if (SIO_put(output, &buf, nbytes) < 0) {
            SYS_abort("Error writing buffer %d", i);
        }
    }
}

/*
 *  ======== DGN_print2log ========
 *  User function for the DGN user device printData. It takes as an argument
 *  the address of the LOG object where the data stream should be printed.
 */
Void DGN_print2log(Arg arg, Ptr addr, Uns nbytes)
{
    Int16      i;

#if defined(_FLOAT_)
    Float     *buf = (Float *)addr;
#else
    Int16      *buf = (Int16 *)addr;
#endif

    for (i = 0; i < nbytes / sizeof(Int16); i++) {
        LOG_printf((LOG_Obj *)arg, "%d", (Int16)buf[i]);
    }
}
