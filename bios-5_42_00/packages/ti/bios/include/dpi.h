/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Kernel 5,2,5,44 09-06-2012 (cuda-u44)
 */
/*
 *  ======== dpi.h ========
 *  New Pipe Module Interface
 *
 */

#ifndef DPI_
#define DPI_

#include <dev.h>

#ifdef __cplusplus
extern "C" {
#endif

extern  Void        DPI_init();

extern  DEV_Fxns    DPI_FXNS;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  /* DPI_ */
