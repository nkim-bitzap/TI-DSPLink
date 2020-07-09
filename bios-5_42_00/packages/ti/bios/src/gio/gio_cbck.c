/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Kernel 5,2,5,44 09-06-2012 (cuda-u44)
 */
/*
 *  ======== gio_cbck.c ========
 *
 */

#include <std.h>

#include <gio.h>
#include <iom.h>
#include <que.h>

#include "_gio.h"

#pragma CODE_SECTION(_GIO_iomCallback, ".bios")

/*
 *  ======== _GIO_iomCallback ========
 *  This function is called by the mini-driver when I/O completes.
 */
Void _GIO_iomCallback(Ptr cbArg, IOM_Packet *packet)
{
    GIO_Handle          gioChan = (GIO_Handle)cbArg;
    GIO_AppCallback     *appCallback = (GIO_AppCallback *)packet->misc;
    Int                 status;
    Ptr                 addr;
    size_t              size;
 
    if (appCallback == NULL) {
        /* this was a synchronous call -- post semaphore (or alternate sync) */
        GIO->SEMPOST(gioChan->syncObj);
    }
    else {
        status = packet->status;
        addr = packet->addr;
        size = packet->size;
        
        /* recycle packet back onto free list */
        QUE_putJ(&gioChan->freeList, packet);

        /* callback into application with status and size */
        (*appCallback->fxn)(appCallback->arg, status, addr, size);
    }
}
