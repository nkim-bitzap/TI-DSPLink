/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Kernel 5,2,5,44 09-06-2012 (cuda-u44)
 */
/*
 *  ======== utl_doab.c ========
 *
 *  An abort function, typically configured in the SYS module.
 *
 */

#pragma CODE_SECTION(UTL_doAbort, ".bios")

#include <std.h>
#include <sys.h>
#include <log.h>
#include <stdarg.h>
#include <utl.h>

/*
 *  ======== UTL_doAbort ========
 */
Void UTL_doAbort(String fmt, va_list ap)
{
#if UTL_USESYS
    SYS_vprintf(fmt, ap);
#else
    LOG_error("SYS abort called with message '%s'", (Arg)fmt);
#endif
    UTL_halt();
}

