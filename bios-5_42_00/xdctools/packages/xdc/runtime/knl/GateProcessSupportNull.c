/*
 *  ======== GateProcessSupportNull.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Error.h>

#include "package/internal/GateProcessSupportNull.xdc.h"

/*
 *  ======== GateProcessSupportNull_enter ========
 */
IArg GateProcessSupportNull_enter(GateProcessSupportNull_Handle gate)
{
    return (0);
}

/*
 *  ======== GateProcessSupportNull_leave ========
 */
Void GateProcessSupportNull_leave(GateProcessSupportNull_Handle gate, IArg key)
{
}

/*
 *  ======== GateProcessSupportNull_getReferenceCount ========
 */
Int GateProcessSupportNull_getReferenceCount(GateProcessSupportNull_Handle gate,   Error_Block* eb)
{
    return (0);
}

/*
 *  ======== GateProcessSupportNull_query ========
 */
Bool GateProcessSupportNull_query(Int qual)
{
    return (TRUE);
}
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,194; 9-3-2012 16:22:17; /db/ztree/library/trees/xdc/xdc-y35x/src/packages/
 */

