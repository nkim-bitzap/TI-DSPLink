/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Kernel 5,2,5,44 09-06-2012 (cuda-u44)
 */
/*
 *  ======== gio_cntl.c ========
 *
 */

#include <std.h>

#include <gio.h>

#pragma CODE_SECTION(GIO_control, ".bios")

#ifdef _BIOSROM_
#pragma DATA_SECTION(GIO_controlPtr, ".biosjmp")
Int (*GIO_controlPtr)(GIO_Handle gioChan, Uns cmd, Ptr args) = GIO_control;
#endif

/*
 *  ======== GIO_control ========
 */
Int GIO_control(GIO_Handle gioChan, Uns cmd, Ptr args)
{
    /* call mini-driver control fxn */
    return (gioChan->fxns->mdControlChan(gioChan->mdChan, cmd, args));
}

