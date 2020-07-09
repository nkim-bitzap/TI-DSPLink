/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Kernel 5,2,5,44 09-06-2012 (cuda-u44)
 */
/*
 *  ======== dgn_prfl.c ========
 *
 *  "User" function for DGN /printfloat device.
 *!
 */

#include <std.h>
#include <stddef.h>
#include <sys.h>

/*
 *  ======== DGN_printFloat ========
 */
Void DGN_printFloat(Arg arg, Ptr addr, size_t size)
{
    Float       *buf = (Float *)addr;
        
    size = size / sizeof(Float);

    for (; size > 0; size--, buf++) {
        SYS_printf("%f\n", *buf);
    }
}

