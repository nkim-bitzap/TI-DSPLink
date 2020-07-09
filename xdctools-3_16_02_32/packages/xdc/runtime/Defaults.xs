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
 *  ======== Default.xs ========
 *
 *! Revision History
 *! ================
 *! 19-Feb-2008 sasha	created
 */

/*
 *  ======== getCommon ========
 */
function getCommon(mod, param)
{
    if (mod.common$[param] !== undefined) {
        return (mod.common$[param]);
    }
    else {
        return (this.common$[param]);
    }
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,236; 12-18-2009 12:27:13; /db/ztree/library/trees/xdc/xdc-u16x/src/packages/
 */

