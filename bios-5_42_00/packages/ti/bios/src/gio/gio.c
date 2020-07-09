/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Kernel 5,2,5,44 09-06-2012 (cuda-u44)
 */
/*
 *  ======== gio.c ========
 *
 */

#pragma CODE_SECTION(GIO_init, ".sysinit")

#include <std.h>

#include <gio.h>
#include <sys.h>

GIO_Attrs GIO_ATTRS = {
    2,              /* nPackets */
    SYS_FOREVER,    /* timeout */
};


/*
 *  ======== GIO_init ========
 */
Void GIO_init()
{
}


