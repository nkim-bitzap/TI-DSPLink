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
/*!
 *  ======== Mingw.xdc ========
 *  MinGW native Windows target
 *
 *  This module defines a native target for Windows using the mingw compiler.
 *
 *  The mingw compiler is a freely available (www.mingw.org) port of GCC that
 *  can build Windows compatible libraries, DLLs, and executables.
 */
metaonly module Mingw inherits gnu.targets.ITarget {
    override readonly config string name                 = "Mingw";     
    override readonly config string os                   = "Windows";   
    override readonly config string suffix               = "86GW";
    override readonly config string isa                  = "x86";       
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "little"
    };

    override readonly config string rts = "gnu.targets.rts86GW";

    override config string platform = "host.platforms.PC";
    
    override config string LONGNAME = "/bin/mingw32-gcc.exe";

    /*!
     *  ======== cmdPrefix ========
     *  Prefix to put in front of each command
     *
     *  This string is put in front of every Command before being passed to
     *  the shell for execution.  This string can be used to run the compiler
     *  in emulation environments.  
     */
    config String cmdPrefix = "";
    
    override config ITarget.Options ccOpts = {
        prefix: "-Wunused",
        suffix: "-Dfar= "
    };

    override config ITarget.Options lnkOpts = {
        prefix: "",
        suffix: "-lstdc++ -L$(rootDir)/lib"
    };
        
    override readonly config xdc.bld.ITarget.StdTypes stdTypes = {
        t_IArg          : { size: 4, align: 4 },
        t_Char          : { size: 1, align: 1 },
        t_Double        : { size: 8, align: 4 },
        t_Float         : { size: 4, align: 4 },
        t_Fxn           : { size: 4, align: 4 },
        t_Int           : { size: 4, align: 4 },
        t_Int8          : { size: 1, align: 1 },
        t_Int16         : { size: 2, align: 2 },
        t_Int32         : { size: 4, align: 4 },
        t_Int64         : { size: 8, align: 4 },
        t_Long          : { size: 4, align: 4 },
        t_LDouble       : { size: 12, align: 4 },
        t_LLong         : { size: 8, align: 4 },
        t_Ptr           : { size: 4, align: 4 },
        t_Short         : { size: 2, align: 2 },
    };
}
/*
 *  @(#) gnu.targets; 1, 0, 1,374; 12-18-2009 11:42:01; /db/ztree/library/trees/xdctargets/xdctargets-b30x/src/
 */
