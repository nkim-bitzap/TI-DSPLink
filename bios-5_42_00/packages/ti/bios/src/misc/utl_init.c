/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Kernel 5,2,5,44 09-06-2012 (cuda-u44)
 */
/*
 *  ======== utl_init.c ========
 *
 */

#pragma CODE_SECTION(UTL_init, ".sysinit")

#include <std.h>
#include <sys.h>
#include <utl.h>
#include <string.h>

/*
 *  ======== UTL_init ========
 */
Void UTL_init(Void)
{
    /* clear circular buffer */
    memset((Ptr)&SYS_PUTCBEG, 0, &SYS_PUTCEND - &SYS_PUTCBEG + 1);
}


