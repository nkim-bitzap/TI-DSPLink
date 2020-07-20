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
 *  ======== Platform.xs ========
 *
 */

/*
 *  ======== Platform.getCpuDataSheet ========
 *  This Platform's implementation xdc.platform.IPlatform.getCpuDataSheet.
 *
 *  Return the xdc.platform.ICpuDataSheet.Instance object that corresponds
 *  to the device that runs executables loaded on the specified cpuId.
 */
function getCpuDataSheet(cpuId)
{
    var Utils = xdc.useModule('xdc.platform.Utils');
    return (Utils.getCpuDataSheet(this.$module.CPU));
}

/*
 *  ======== Platform.getCreateArgs ========
 */
function getCreateArgs()
{
    return (this.$private.args);
}

/*
 *  ======== Platform.getExeContext ========
 *  This Platform's implementation xdc.platform.IPlatform.getExeContext.
 *
 *  Return the xdc.platform.IPlatform.ExeContext object that will run the 
 *  specified program prog.
 */
function getExeContext(prog)
{
    var Utils = xdc.useModule('xdc.platform.Utils');
    var args = this.$private.args;

    if (args.verbose > 0) {
        print(this.$module.$name + "('"
            + this.$private.name + "') selecting ExeContext for program '"
            + prog.name + "' ...");
        print("    endian = "    + prog.endian);
        print("    codeModel = " + prog.codeModel);
        print("    cpuId = "   + prog.build.cpuId);
    }

    var ExeContext = xdc.useModule('xdc.platform.ExeContext');

    /* create a default ExeContext execution context */
    var cpu = ExeContext.create(this.$module.CPU, this.$module.BOARD);

    /* Set the initial memory map from the cpu datasheet. Check if the user
     * tried to set cpuArgs, and if it's the case print a deprecation
     * warning message.
     */
    if (prog.build.cpuArgs != null) {
        this.$module.$logWarning("The parameter 'cpuArgs' in xdc.bld.Executable " +
            "is deprecated and will not be supported in future releases. " +
            "Please, use corresponding platform instance parameters to set " +
            "the initial register settings.", this.$module, null);
        
        for (var prop in prog.build.cpuArgs) {
            if (!(prop in this.$private.args)) {
                this.$private.args[prop] = prog.build.cpuArgs[prop];
            }
        }
    }

    if (this.$private.extMap != undefined) {
        this.externalMemoryMap = this.$private.extMap;  
    }
    else {
        if (this.$private.args.mapMode == 0) {
            this.externalMemoryMap["SBSRAM"].base = 0x0;
        }
    }

    cpu.memoryMap = Utils.assembleMemoryMap(cpu, this);

    // check for the overlap in the memory map
    var overlap = Utils.checkOverlap(cpu.memoryMap);

    if (overlap != null) {
        this.$module.$logError("Memory objects " + overlap + " overlap", this,
            overlap);
    }

    Utils.checkDefaults(this, cpu.memoryMap);
    this.$seal();

    return (cpu);
}

/*
 *  ======== Platform.getExecCmd ========
 *  This Platform's implementation xdc.platform.IPlatform.getExecCmd.
 */
function getExecCmd(prog)
{
    var os = environment["xdc.hostOS"];
    var updateComment = "@$(ECHO) Check for updates to this package at:\n" +
    "@$(ECHO) https://www-a.ti.com/downloads/sds_support/targetcontent/" +
    "rtsc/index.html";

    if (os == "Windows") {
        return("cscript runtest.js " + 
               java.io.File(prog.name).getCanonicalPath());
    }
    else {
        return("@$(ECHO) " + this.$package.$name + " platform package " +
               "cannot execute " + java.io.File(prog.name).getCanonicalPath() +
               " on " + os + "\n" + updateComment + "\n\t:");
    }
}

/*
 *  ======== Platform.getLinkTemplate ========
 *  This is Platform's implementation xdc.platform.IPlatform.getLinkTemplate
 */
function getLinkTemplate(prog)
{
    return ("ti/targets/linkcmd.xdt");
}

/*
 *  ======== Platform.Instance.init ========
 *  This function is called to initialize a newly created instance of a
 *  platform.  Platform instances are created just prior to running
 *  program configuration scripts.
 *
 *  Platform instances may also be created in the build domain.
 *
 *  this.$args.args is the object configured in config.bld via
 *  Build.platformTable.  This is an untyped object that may specify
 *  platform specific parameters.
 *
 *  this.$args.name is the name used to identify this instance (without
 *  the package name prefix).
 */
function instance$meta$init(name, args)
{
    /* cache the platform creation args and platform instance name for the
     * getExeContext method above.
     */
    this.$private.name = name;                      /* instance name */
    this.$private.args = args == null ? {} : args;  /* instance args */

    if (args != null) {
        if ("sectMap" in args) {
            this.sectMap = args.sectMap;
        }

        if ("customMemoryMap" in args) {
            this.customMemoryMap = args.customMemoryMap;
        }
        
        if ("renameMap" in args) {
            this.renameMap = args.renameMap;
        }

        if ("externalMemoryMap" in args) {
            this.$private.extMap = new xdc.om['xdc.platform.IPlatform'].
                MemoryMap(args.externalMemoryMap);
        }
        
        if("codeMemory" in args) {
            this.codeMemory = args.codeMemory;  
        }

        if("dataMemory" in args) {
            this.dataMemory = args.dataMemory;  
        }

        if("stackMemory" in args) {
            this.stackMemory = args.stackMemory;
        }
    }
};
/*
 *  @(#) ti.platforms.sim62xx; 1, 0, 0,265; 12-9-2009 17:21:29; /db/ztree/library/trees/platform/platform-k27x/src/
 */
