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
/*
 *  ======== xdc_runtime_Diags_query ========
 *  Returns true iff: 
 *      1. the current module's included diags intersect evt's mask, and
 *      2. either the permanently enabled diags intersect evt's mask or
 *         the runtime controllable diags intersect evt's mask.
 */
#define xdc_runtime_Diags_query(evt) \
    (Module__DGSINCL & (evt) \
        && (Module__DGSENAB & (evt) || *Module__DGSMASK & (evt)))



/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,236; 12-18-2009 12:27:13; /db/ztree/library/trees/xdc/xdc-u16x/src/packages/
 */

