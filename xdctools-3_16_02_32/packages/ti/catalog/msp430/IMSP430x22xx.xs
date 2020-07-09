/* 
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * */

/*
 *  ======== getMemoryMap ========
 *  Returns the memory map as seen by a program running on this device
 *  when the registers are set as specified by the regs hash.
 */
function getMemoryMap(regs)
{
    /* add common memory blocks to this device's memory map */
    for (var key in this.commonMap) {
        this.memMap[key] = this.commonMap[key];
    }
    return (this.memMap);
}
/*
 *  @(#) ti.catalog.msp430; 1, 0, 0,5; 12-9-2009 17:22:28; /db/ztree/library/trees/platform/platform-k27x/src/
 */

