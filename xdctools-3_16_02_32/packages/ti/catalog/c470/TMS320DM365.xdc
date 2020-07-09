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
 *  ======== TMS320DM365.xdc ========
 *
 */

metaonly module TMS320DM365 inherits ti.catalog.ICpuDataSheet
{
instance:
    override config string cpuCore           = "v5T";
    override config string isa               = "v5T";
    override config string cpuCoreRevision   = "1.0";
    override config int    minProgUnitSize   = 1;
    override config int    minDataUnitSize   = 1;
    override config int    dataWordSize      = 4;

    /*!
     *  ======== memMap ========
     *  The memory map returned be getMemoryMap().
     */
    config xdc.platform.IPlatform.Memory memMap[string] =
        ti.catalog.arm.TMS320CDM355.memMap;
}
/*
 *  @(#) ti.catalog.c470; 1, 0, 1, 1,214; 12-9-2009 17:22:30; /db/ztree/library/trees/platform/platform-k27x/src/
 */

