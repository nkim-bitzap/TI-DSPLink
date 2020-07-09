/** ============================================================================
 *  @file   terminate.h
 *
 *  @path   $(DSPLINK)/gpp/src/inc/sys/
 *
 *  @desc   Driver functions for terminate support
 *
 *  @ver    1.65.02.09
 *  ============================================================================
 *  Copyright (C) 2002-2012, Texas Instruments Incorporated - http://www.ti.com/
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation version 2.
 *  
 *  This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 *  whether express or implied; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *  ============================================================================
 */

#ifndef dsplink_gpp_inc_sys_terminate_h
#define dsplink_gpp_inc_sys_terminate_h

#if defined(__cplusplus)
extern "C" {
#endif


/*
 *  ======== DSPLINK_sendTerminateEvent ========
 *  @func   DSPLINK_sendTerminateEvent
 *
 *  @desc   Send a terminate event to DSP if possible.
 */
void DSPLINK_sendTerminateEvent(void);


#if defined(__cplusplus)
}
#endif

#endif /* dsplink_gpp_inc_sys_terminate_h */
