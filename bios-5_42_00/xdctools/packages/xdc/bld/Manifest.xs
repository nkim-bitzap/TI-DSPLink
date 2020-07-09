/*
 *  ======== getAllFiles ========
 */
function getAllFiles(excludeDirs)
{
    if (xdc.om.$name != "rel") {
        throw new Error(
            "Manifest.getAllFiles can only be called from within a release script");
    }

    /* clear current files list */
    this.files = [];

    /* re-populate based on excludeDirs */
    /* rcl is alredy loaded by the release model initialization rcl.js */
    rcl.getFiles(this.files, excludeDirs);
}
/*
 *  @(#) xdc.bld; 1, 0, 2,388; 9-3-2012 16:22:03; /db/ztree/library/trees/xdc/xdc-y35x/src/packages/
 */

