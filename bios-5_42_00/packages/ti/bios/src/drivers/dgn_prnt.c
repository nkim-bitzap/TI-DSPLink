/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Kernel 5,2,5,44 09-06-2012 (cuda-u44)
 */
/*
 *  ======== dgn_prnt.c ========
 *
 *  "User" function for DGN /printInt device.
 *!
 */
    

#include <std.h>
#include <stddef.h>
#include <sys.h>

/*
 *  ======== DGN_printInt ========
 */
Void DGN_printInt(Arg arg, Ptr addr, Uns size)
{
    Int16       *buf = (Int16 *)addr;
        
    size = size / sizeof(Int16);

    for (; size > 0; size--, buf++) {
        SYS_printf("%d\n", *buf);
    }
}
