/*
 *  ======== LOG.xdc ========
 *
 *! Revision History
 *! ================
 *! 16-Oct-2008 cmcc Created.
 */

package ti.bios.rov

import xdc.rov.ViewInfo;

/*!
 *  ======== LOG ========
 *  This module provides support for the LOG module in BIOS 5 ROV.
 *
 *  It defines the target state structures used by the LOG module, and provides
 *  ROV views for displaying them.
 */
module LOG {

    /*!
     *  ======== LOG_Event_6x ========
     *  BIOS 5 target structure representing a LOG record for 6x targets.
     */
    struct LOG_Event_6x {
        UInt seqnum;
        IArg val1;
        IArg val2;
        IArg val3;
    }
    
    /*!
     *  ======== LOG_Event_28_55L ========
     *  BIOS 5 target structure representing a LOG record for 55L, 55H, and 28x
     *  targets.
     *
     *  In log.h, this applies to 55x targets with the symbol __LARGE_MODEL__ 
     *  set, and I believe this symbol is set in both large and huge apps.
     */
    struct LOG_Event_28_55L {
        UInt pad;
        UInt seqnum;
        IArg val1;
        IArg val2;
        IArg val3;
    }
    
    /*!
     *  ======== LOG_Event_55 ========
     *  BIOS 5 target structure representing a LOG record for 55 small model.
     *
     *  Only 55 Large has the explicit pad field.
     *
     *  In BIOS 5, the type 'Arg' is equal to a data pointer for 55 and 28. 
     *  This is different from the RTSC target definition, where IArg is large
     *  enough to a data or a code pointer. 
     *
     *  For the 55 small model, the type Arg is only 16-bits, so we type the
     *  arguments as Ptrs instead of IArgs.
     */
    struct LOG_Event_55 {
        UInt seqnum;
        Ptr val1;
        Ptr val2;
        Ptr val3;
    }
    
    /*!
     *  ======== LOG_Obj ========
     *  BIOS 5 target structure representing a LOG instance.
     */
    struct LOG_Obj {
        IArg* bufend;
        UInt flag;
        UInt seqnum;
        Ptr curptr;    // Ptr to LOG_Event
        UInt lenmask;
        Ptr bufbeg;    // Ptr to LOG_Event
    };
   
    /*!
     *  ======== LogRecordView ========
     *  BIOS 5 ROV representation of a single log record.
     */
    metaonly struct LogRecordView {
        UInt     seqnum;
        UInt     timestamp;
        String   message;
    }
        
    @Facet
    metaonly config ViewInfo.Instance rovViewInfo = 
        ViewInfo.create({
            viewMap: [
                ['Logs', {type: ViewInfo.INSTANCE_DATA, viewInitFxn: 'viewInitLogs', structName: 'LogRecordView'}]
            ],
            /* Nothing to show in the raw tab. */
            showRawTab: false
        });


}