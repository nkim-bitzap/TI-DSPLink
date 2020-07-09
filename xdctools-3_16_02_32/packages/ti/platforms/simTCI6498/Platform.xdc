/*
 *  Copyright (c) 2009 by Texas Instruments and others.
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
 *  ======== Platform.xdc ========
 *
 */

/*!
 *  ======== Platform ========
 *  Platform support for the simTCI6498
 */
metaonly module Platform inherits xdc.platform.IPlatform
{
    readonly config xdc.platform.IPlatform.Board BOARD = {      
        id:             "0",
        boardName:      "simTCI6498",
        boardFamily:    "simTCI6498",
        boardRevision:  null,
    };
        
    readonly config xdc.platform.IExeContext.Cpu CPU = {        
        id:             "0",
        clockRate:      1000,
        catalogName:    "ti.catalog.c6000",
        deviceName:     "TMS320CTCI6498",
        revision:       "1.0",
    };
    
instance:

    override config string codeMemory  = "L2SRAM";
    override config string dataMemory  = "L2SRAM";
    override config string stackMemory = "L2SRAM";
};
/*
 *  @(#) ti.platforms.simTCI6498; 1, 0, 0, 0,40; 12-9-2009 17:31:52; /db/ztree/library/trees/platform/platform-k27x/src/
 */

