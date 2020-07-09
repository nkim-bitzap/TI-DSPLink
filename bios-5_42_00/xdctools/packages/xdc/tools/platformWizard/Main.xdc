/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

package xdc.tools.platformWizard;

/*!
 *  ======== Main ========
 * @_nodoc
 */
metaonly module Main inherits xdc.tools.ICmd {

    override config String usage[] = [
        ' -r <repository for platform package>',
        ' -x <XML schema file>',
                '<platform package name>'
    ];

instance:
        
    @CommandOption("r")
    config String repositoryPath = null;
        
    @CommandOption("x")
    config String schemaFile = null;
        
    override Any run(xdc.tools.Cmdr.Instance cmdr, String args[]);
}
/*
 *  @(#) xdc.tools.platformWizard; 1,0,0,117; 8-27-2012 11:52:47; /db/ztree/library/trees/xdctools/xdctools-f15x/src/
 */

