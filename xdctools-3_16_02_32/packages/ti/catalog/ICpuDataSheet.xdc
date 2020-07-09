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
 *  ======== ICpuDataSheet.xdc ========
 */


package ti.catalog;

metaonly interface ICpuDataSheet inherits xdc.platform.ICpuDataSheet {

instance:

    /*!
     *  ======== cpuCore ========
     *  An array of strings identifying the compatible ISA for the device.
     *
     *  @_nodoc
     */
    config string isa;

}
/*
 *  @(#) ti.catalog; 1, 0, 0,82; 12-9-2009 17:20:06; /db/ztree/library/trees/platform/platform-k27x/src/
 */

