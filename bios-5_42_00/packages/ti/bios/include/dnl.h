/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Kernel 5,2,5,44 09-06-2012 (cuda-u44)
 */
/*
 *  ======== dnl.h ========
 *  Null Device Module Interface
 *
 */

#ifndef DNL_
#define DNL_


#include <dev.h>
#include <fxn.h>

#ifdef __cplusplus
extern "C" {
#endif

extern DEV_Fxns DNL_FXNS;

#define DNL_init    ((Fxn)FXN_F_nop)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* DNL_ */
