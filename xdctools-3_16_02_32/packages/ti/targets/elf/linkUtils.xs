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
var coffUtils = xdc.loadCapsule("ti/targets/linkUtils.xs");

function genElfSections(prog)
{
    var nonSplitable = {
        ".bss": 1,
        ".pinit": 1,
        ".cinit": 1,
        ".stack": 1,
        ".sysstack": 1,
        ".sysmem": 1,
        ".esysmem": 1,
        ".ti.decompress": 1,
        ".ti.handler_table": 1
    };
    var res = "";

    /* the section map is constructed from the target and program info */
    var sectMap = prog.getSectMap();
    
    if (sectMap['xdc.meta'] == undefined) {
        sectMap['xdc.meta'] = new prog.SectionSpec(sectMap[".const"]);
        sectMap['xdc.meta'].type = "COPY";
    }

    if (xdc.om['xdc.runtime.Text'].isLoaded != true
        && sectMap['xdc.noload'] == undefined) {
        sectMap['xdc.noload'] = new prog.SectionSpec(sectMap[".text"]);
        sectMap['xdc.noload'].type = "COPY";
    }

    if (sectMap['.args'] != undefined) {
        sectMap['.args'].loadAlign = 4;
        sectMap['.args'].runAlign = 4;
    }

    /* if the target version is 0, this is an *old* compiler/linker that
     * probably does not support splitting; we may need a more precise
     * target-specific heuristic.
     */
    targetVers = prog.build.target.version.split(',')[2] - 0;
    useSplit = targetVers > 0;
    var bssGroupDone = false;
    for (var sn in sectMap) {
        if (sn == ".bss" || sn == ".rodata" || sn == ".neardata") {
            if (!bssGroupDone) {
                var allocation = coffUtils.sectLine(sectMap, sn, ">");
                allocation = allocation.replace(sn, "GROUP");
                res += "    " + allocation + "\n    {\n";
                res += "        " + ".bss:\n";
                res += "        " + ".neardata:\n";
                res += "        " + ".rodata:\n";
                res += "    }\n";
                bssGroupDone = true;

                /* Check if .bss, .rodata, and .neardata go to the same
                 * segment. If some of them are not defined, just assume
                 * they are allocated in the same way as one of the defined
                 * section to make the check simpler.
                 */
                if (sectMap[".neardata"] != null) {
                    var nearAlloc =
                        coffUtils.sectLine(sectMap, ".neardata", ">");
                    nearAlloc = nearAlloc.replace(".neardata", "");
                }
                else {
                    nearAlloc = coffUtils.sectLine(sectMap, sn, ">");
                    nearAlloc = nearAlloc.replace(sn, "");
                }
                if (sectMap[".bss"] != null) {
                    var bssAlloc = coffUtils.sectLine(sectMap, ".bss", ">");
                    bssAlloc = bssAlloc.replace(".bss", "");
                }
                else {
                    bssAlloc = coffUtils.sectLine(sectMap, sn, ">");
                    bssAlloc = bssAlloc.replace(sn, "");
                }
                if (sectMap[".rodata"] != null) {
                    var roAlloc = coffUtils.sectLine(sectMap, ".rodata", ">");
                    roAlloc = roAlloc.replace(".rodata", "");
                }
                else {
                    roAlloc = coffUtils.sectLine(sectMap, sn, ">");
                    roAlloc = roAlloc.replace(sn, "");
                }
                if(!(bssAlloc == nearAlloc && bssAlloc == roAlloc)) {
                    throw new Error("Allocations for sections '.bss', '.rodata'"
                        + " and '.neardata' must be same.");
                }
            }
        }
        else if (sn in nonSplitable) {
            res += "    " + coffUtils.sectLine(sectMap, sn, ">") + "\n";
        }
        else if (sn == ".args") {
            var argsFill = ", fill = 0";
            /* some linkers fail if you try to fill args with 0 */
            if ((prog.build.target.isa == "470"
                || prog.build.target.isa[0] == 'v')
                && targetVers >= 4.4 && targetVers <= 4.5) {
                argsFill = "";
            }

            res += "    " + coffUtils.sectLine(sectMap, sn, ">") + argsFill 
                + " {_argsize = " + utils.toHex(prog.argSize) + "; }\n";
        }
        else {
            res += "    "
                + coffUtils.sectLine(sectMap, sn, useSplit ? ">>" : ">") + "\n";
        }
    }
    return (res);
}
/*
 *  @(#) ti.targets.elf; 1, 0, 0,139; 12-18-2009 11:42:13; /db/ztree/library/trees/xdctargets/xdctargets-b30x/src/
 */
