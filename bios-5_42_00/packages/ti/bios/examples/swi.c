/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Examples 5,4,1 02-08-2010 (biosEx-j14)
 */
/*
 *  ======== swi.c =======
 *
 */

#include <std.h>

#include <log.h>
#include <swi.h>
#include <sys.h>

#include "swicfg.h"

Void swiFxn0(Void);
Void swiFxn1(Void);

/*
 *  ======== main ========
 */
Void main(Int argc, Char *argv[])
{
    LOG_printf(&trace,"swi example started!\n");    
    LOG_printf(&trace,"Main posts SWI0\n");
    SWI_post(&SWI0);
        LOG_printf(&trace,"Main done!\n");
}

/*
 *  ======== swiFxn0 ========
 */
Void swiFxn0(Void)
{
    LOG_printf(&trace,"swiFxn0 posts SWI1\n");  
        SWI_post(&SWI1);
        LOG_printf(&trace,"SWI0 done!\n");
}

/*
 *  ======== swiFxn1 ========
 */
Void swiFxn1(Void)
{
        LOG_printf(&trace,"SWI1 done!\n");
}

