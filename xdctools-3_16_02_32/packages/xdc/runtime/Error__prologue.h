/* --COPYRIGHT--,ESD
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * --/COPYRIGHT--*/
#include <xdc/runtime/Main.h>

/*
 *  ======== xdc_runtime_Error_Id ========
 */
typedef xdc_Bits32 xdc_runtime_Error_Id;

#ifdef __cplusplus
namespace xdc_runtime { namespace Error {
    typedef xdc_runtime_Error_Id Id;
}}
#endif


/*
 *  ======== Module__MID ========
 *  This definition allows non-module code to
 *  use the Error module.  This symbol is normally defined in each
 *  module internal header (i.e., package/internal/<mod>.xdc.h).
 */
#undef Module__MID
#define Module__MID xdc_runtime_Main_Module__id__C

/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,236; 12-18-2009 12:27:13; /db/ztree/library/trees/xdc/xdc-u16x/src/packages/
 */
