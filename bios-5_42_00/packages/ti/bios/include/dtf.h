/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Kernel 5,2,5,44 09-06-2012 (cuda-u44)
 */
/*
 * ======== dtf.h ========
 * compatibility file for .cfg files that use DTF.  DTR now works for both
 * integer and floating point DSPs.
 *
 */

#include <dtr.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DTF     DTR

#define DTF_Params DTR_Params

#define DTF_SCALE       DTR_SCALE
#define DTF_USER        DTR_USER

#ifdef __cplusplus
}
#endif /* extern "C" */

