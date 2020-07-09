/*
 *  ======== SWI.xdc ========
 *
 *! Revision History
 *! ================
 *! 23-Oct-2008  cmcc  Created.
 */
 
package ti.bios.rov

import xdc.rov.ViewInfo;

/*!
 *  ======== SWI ========
 *  Represents BIOS 5 SWI module in BIOS 5 ROV.
 */
module SWI
{
    /*!
     *  ======== SWI_Obj ========
     *  BIOS 5 target representation of a single SWI instance.
     */
    struct SWI_Obj {
        Int         lock;
        Ptr         ready;
        UInt        mask;
        Ptr         link;
        UInt        initkey;
        UInt        mailbox;
        Fxn         fxn;
        IArg        arg1;
        IArg        arg0;
        Int         stslock;
        Ptr         *sts;           /* pointer to STS_Obj */
    };

    /*!
     *  ======== SWI_Obj_55 ========
     *  BIOS 5 target representation of a single SWI instance on 55 small model
     *  targets.
     *
     *  The arg fields have a different size on 55 small model.
     *
     *  In BIOS 5, the type 'Arg' is equal to a data pointer for 55 and 28. 
     *  This is different from the RTSC target definition, where IArg is large
     *  enough to a data or a code pointer. For 28x, 55L, and 55H, these sizes
     *  match up.
     *
     *  For the 55 small model, though, the data pointer is only 1 16-bit MAUs,
     *  so we type the arguments as Ptrs instead of IArgs.
     *
     *  See also LOG.LOG_Event_55
     */
    struct SWI_Obj_55 {
        Int         lock;
        Ptr         ready;
        UInt        mask;
        Ptr         link;
        UInt        initkey;
        UInt        mailbox;
        Fxn         fxn;
        Ptr         arg1;
        Ptr         arg0;
        Int         stslock;
        Ptr         *sts;           /* pointer to STS_Obj */
    };   
    
    /*!
     *  ======== InstanceData ========
     *  ROV view representation of a single SWI instance.
     */
    metaonly struct InstanceData {
        String      name;
        Ptr         handle;
        String      state;
        Int         priority;
        Int         mailboxVal;
        String      fxn;
        IArg        arg0;
        IArg        arg1;
        Ptr         fxnAddr;
    };
    
    @Facet
    metaonly config ViewInfo.Instance rovViewInfo = 
        ViewInfo.create({
            viewMap: [
                ['Instances', {type: ViewInfo.MODULE_DATA, viewInitFxn: 'viewInitInstances', structName: 'InstanceData'}]
            ],
            /* Nothing to show in the raw tab. */
            showRawTab: false
        });


    /*!
     *  ======== getNickName ========
     *  Returns a "nick name" (a name to display to represent the instance) 
     *  for the instance at the given address.
     */
    metaonly String getNickName(Int addr);
    
    /*!
     *  ======== fxnToHandle ========
     *  The SWI LOG events log the SWI's fxn address rather than its handle. This
     *  function returns the handle for the given swi fxn.
     */
    metaonly Ptr fxnToHandle(Ptr fxn);
}