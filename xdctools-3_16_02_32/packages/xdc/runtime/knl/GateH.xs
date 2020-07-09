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
 *  ======== GateH.xs ========
 */

var GateH = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    GateH = this;

    if ((GateH.Proxy == undefined) || (GateH.Proxy == null)) {
        GateH.Proxy = xdc.module("xdc.runtime.knl.GateThread");
    }

    
    /* 
     * If cfg file has not set abstractInstances$ for GateH.Proxy
     * then set it to true by default.
     */
    if (GateH.Proxy.$written("abstractInstances$") == false) {
        GateH.Proxy.abstractInstances$ = true;
    }
}

 /*
 *! Revision History
 *! ================
 *! 17-Apr-2009 nitya   Review updates
 */
 /*
 *  @(#) xdc.runtime.knl; 1, 0, 0,45; 12-18-2009 12:27:12; /db/ztree/library/trees/xdc/xdc-u16x/src/packages/
 */

