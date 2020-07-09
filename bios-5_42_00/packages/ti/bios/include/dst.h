/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Kernel 5,2,5,44 09-06-2012 (cuda-u44)
 */
/*
 *  ======== dst.h ========
 *  Stacking "Split" Device
 *
 */

#ifndef DST_
#define DST_

#include <dev.h>
#include <fxn.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DST_init        ((Fxn)FXN_F_nop)

extern DEV_Fxns DST_FXNS;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* DST_ */
