var wrapThreshold;

/*
 *  ======== viewInitLogs ========
 *  Displays all of the logs using an INSTANCE_DATA view.
 */
function viewInitLogs(view, obj)
{
    var Program = xdc.useModule('xdc.rov.Program');
    var ROV = xdc.useModule('ti.bios.rov.ROV');
    
    /* Retrieve all of the LOG instances. */
    try {
        var logs = getLogs();
    }
    catch (e) {
        throw (new Error("Problem retrieving LOG instances: " + 
                         Program.exToString(e)));
    }
    
    /* Determine whether the app supports timestamps. */
    var supportsTimestamp = false;
    
    /* On 6x targets, check the LOG_ts symbol. */
    if ((ROV.getISA() != '28') && (ROV.getISA() != '55')) {

        /* If the symbol doesn't exist, this will throw an exception. */
        var value;
        try {
            value = Program.getSymbolValue("LOG_ts");
        }
        catch (e) {
            // Do nothing.
        }
        if (value == 1) {
            supportsTimestamp = true;
        }
    }        
    
    /* 
     * The wrapThreshold is the maximum allowed distance between two
     * sequence numbers before it is assumed that the sequence numbers
     * have wrapped.
     * 
     * Dividing the sequence number range in half gives us a balanced 
     * approach. We want to recognize a wrap when the difference is
     * "large", but not when the difference is "small".
     */
    wrapThreshold = getMaxSequenceNumber() / 2; 
        
    /* Process the view for each of the LOG instances. */
    var instViews = new Array();
    for each (var log in logs) {
        instViews[instViews.length] = getLogView(log, supportsTimestamp);
    }
    
    return (instViews);
}

/*
 *  ======== getMaxSequenceNumber ========
 *  Returns the maximum sequence number for the current ISA.
 */        
function getMaxSequenceNumber()
{
    var ROV = xdc.useModule('ti.bios.rov.ROV');
    
    if ((ROV.getISA() == '55') || (ROV.getISA() == '28')) {
        return(65534); // 2^16 - 2
    }
    else {
        return(4294967294); // 2^32 - 2
    }
}

/*
 *  ======== getLogs ========
 *  Retrieves all of the LOG instances.
 */
function getLogs()
{
    var Program = xdc.useModule('xdc.rov.Program');
    var LOG = xdc.useModule('ti.bios.rov.LOG');
    
    Program.debugPrint("LOG -- Retrieving all of the LOG instances...");
    
    /* Get the base address of the LOG table. */
    var tabBegAddr = Program.getSymbolValue('LOG_A_TABBEG');
    Program.debugPrint("LOG -- tabBegAddr = 0x" + 
                       Number(tabBegAddr).toString(16));
    
    /* Get the length of the LOG table. */
    var tabLen = Program.getSymbolValue('LOG_A_TABLEN');
    Program.debugPrint("LOG -- tabLen = " + tabLen);
    
    /* Retrieve the LOG table. */
    var logs = Program.fetchArray(LOG.LOG_Obj$fetchDesc, tabBegAddr, tabLen);
    
    return (logs);
}

/*
 *  ======== getLogView ========
 *  Processes the view for a single LOG instance.
 *
 *  log - A LOG_Obj structure.
 */
function getLogView(log, supportsTimestamp)
{
    var Program = xdc.useModule('xdc.rov.Program');
    var ScalarStructs = xdc.useModule('xdc.rov.support.ScalarStructs');
    var ROV = xdc.useModule('ti.bios.rov.ROV');
    var LOG = xdc.useModule('ti.bios.rov.LOG');
    
    var view = new Program.InstDataView;
    
    Program.debugPrint("LOG -- Processing LOG 0x" + Number(log.$addr).toString(16));
    
    /* Retrieve the LOG's name. */
    view.label = getName(Number(log.$addr));

    /* Array of all of the record views. */
    var elements = new Array();
    
    /* If no name was found... */
    if (view.label == null) {
        /* Create a view element to display the error. */
        var viewElem = Program.newViewStruct('ti.bios.rov.LOG', 'Logs');
        
        /* Display the error. */
        Program.displayError(viewElem, 'seqnum', 
                             "No name was found for the LOG at 0x" +
                             Number(log.$addr).toString(16));
                             
        /* Add the view element and return. */
        elements[elements.length] = viewElem;
        view.elements = elements;
        return (view);
    }
    
    /* Retrieve the records based on the target. */
    /* 64 */
    if (ROV.getISA() == '64') {
        var logSize = LOG.LOG_Event_6x.$sizeof();
        var fetchDesc = LOG.LOG_Event_6x$fetchDesc;
        var emptyRec = 0xFFFFFFFF;
    }
    /* 55 small model */
    else if (ROV.getTargetName().equals("C55")) {
        var logSize = LOG.LOG_Event_55.$sizeof();
        var fetchDesc = LOG.LOG_Event_55$fetchDesc;
        var emptyRec = 0xFFFF;        
    }
    /* 28 or 55 */
    else if ((ROV.getISA() == '28') || (ROV.getISA() == '55')) {
        var logSize = LOG.LOG_Event_28_55L.$sizeof();
        var fetchDesc = LOG.LOG_Event_28_55L$fetchDesc;
        var emptyRec = 0xFFFF;
    }
    
    /* Get the total size of LOG buffer. */
    var numLogs = (log.lenmask + 1) / logSize;
    
    /* Retrieve the array of LOG records. */
    Program.debugPrint("LOG -- Retrieving " + numLogs + " records at 0x" + 
                       Number(log.bufbeg).toString(16));
    try {
        var records = Program.fetchArray(fetchDesc, log.bufbeg, numLogs);
    }
    catch (e) {
        Program.displayError(view, 'elements', "Problem retrieving LOG " +
                             "records: " + Program.exToString(e));
        return (view);
    }

    /* Get the type of the LOG so we know how to decode the records. */
    var logType = Program.getSymbolValue(view.label + "$datatype");   
    
    /* Decode each record. */
    for (var i = 0; i < records.length; i++) {
        var rec = records[i];
    
        /* Skip if this is an empty record. */
        if ((rec.seqnum == emptyRec) || (rec.seqnum == 0)) {
            break;
        }
        
        var viewElem = Program.newViewStruct('ti.bios.rov.LOG', 'Logs');
        
        /* BIOS 5 Message log starts the count from 0 instead of 1. */
        viewElem.seqnum = (rec.seqnum / 2) - 1;
        
        /* 
         * If this app supports timestamps...
         * Otherwise, leave the timestamp field undefined.
         */
        if (supportsTimestamp) {
            /* The timestamp is in the next record. */
            var tsRec = records[i + 1];

            /* 
             * The upper 32-bits of the 64-bit timestamp are stored in val3
             * and the lower 32-bits are stored in val2.
             */             
            var tsh = tsRec.val3;
            var tsl = tsRec.val2;
            
            /* 
             * The arguments are signed IArgs, so the values may be negative and
             * need to be converted.
             */
            if (tsh < 0) {
                tsh += Math.pow(2, 32);    
            }
            if (tsl < 0) {
                tsl += Math.pow(2, 32);
            }
            
            /*
             * The shift operator in JavaScript only works on 32-bit values, so we
             * need to use Math.pow and multiply to get a 64-bit timestamp.
             */
            viewElem.timestamp = (Math.pow(2, 32) * tsh) + tsl;
            
            /* Increment 'i' to skip over the timestamp record. */
            i++;
        }
        
        /* Get the LOG record's message. */
        try {
            /* logType 0 is System LOG */
            if (logType == 0) {
                viewElem.message = decodeEvent(rec);
            }
            /* logType 1 is user LOG_printf */
            else if (logType == 1) {
                var args = [Number(rec.val1), Number(rec.val2)];               
                
                var fmtStrAddr = rec.val3;
                /* 
                 * Convert address to unsigned.
                 * The arguments are signed IArgs, so the address may be negative and
                 * need to be converted.
                 */
                if (fmtStrAddr < 0) {
                    fmtStrAddr += Math.pow(2, 32);    
                }
                
                viewElem.message = getMessage(fmtStrAddr, args);
            }
        }
        catch (e) {
            Program.displayError(viewElem, 'message', "Problem retrieving " +
                                 "record message: " + Program.exToString(e));
        }
        
        elements[elements.length] = viewElem;
    }

    /* Sort the decoded records by sequence number */
    elements.sort(compareRecords);
    
    /* Display the sorted records. */
    view.elements = elements;
    
    return (view);
}

/*
 *  ======== getName =========
 *  Helper function which determines the name of the LOG at addr.
 *
 *  We don't use ROV.getName here because there are no dynamic instances, and 
 *  we need to be certain that we choose the right name.
 *
 *  To correctly determine which of the symbols at the address is the LOG name,
 *  we look for the symbol for which a symbol containing the suffix "$datatype"
 *  also exists.
 */
function getName(addr)
{
    /* Retrieve LOG module's private data. */
    var data = Program.getPrivateData('ti.bios.rov.LOG');
    
    /* Check the LOG module's addrToName map first. */
    if (data.addrToName != undefined) {
        if (data.addrToName[addr] != undefined) {
            return (data.addrToName[addr]);
        }
    }
    else {
        data.addrToName = {};
    }
    
    /* Lookup the list of symbols at the address. */
    var syms = Program.lookupDataSymbol(Number(addr));
    
    /* Look through the symbols to find the correct one. */
    for each (var sym in syms) {
        if (Program.getSymbolValue(sym + "$datatype") != -1) {
            return (sym);
        }
    }

    /* Return null to indicate the symbol was not found. */
    return (null);
}

/*
 *  ======== compareRecords ========
 *  Compares the sequence numbers of two records to determine their
 *  order for sorting.
 *  This logic takes sequence number wrapping into account. If the difference
 *  between r1 and r2 is greater than 'wrapThreshold', then it is assumed that
 *  a wrap has occurred and that the smaller sequence number is actually larger.
 */
function compareRecords(r1, r2)
{
    /* 
     * If we think that a wrap has occurred, then the smaller
     * sequence number is actually the larger.
     */
    if (Math.abs(r1.seqnum - r2.seqnum) > wrapThreshold) {
        /*
         * If 1 > 2 ret -
         * If 1 < 2 ret +
         * If 1 = 2 ret 0
         */
        return (r2.seqnum - r1.seqnum);
    }
    
    /*
     * If 1 > 2 ret +
     * If 1 < 2 ret -
     * If 1 = 2 ret 0
     */
    return (r1.seqnum - r2.seqnum);
}
 
/*
 *  ======== getMessage ========
 *  Returns the formatted message string from a LOG_printf call.
 */
function getMessage(addr, args)
{
    var System = xdc.useModule('xdc.runtime.System');
    var Program = xdc.useModule('xdc.rov.Program');
    var ROV = xdc.useModule('ti.bios.rov.ROV');
    
    /* Retrieve the format string from the target. */
    var fmtStr = "";
    
    /* 
     * If we're using 3.16, we can retrieve the string using the ofreader.
     * Otherwise, just read it dynamically. 
     */
    if ('fetchStaticString' in Program) {
        fmtStr = Program.fetchStaticString(Number(addr));
    }
    else {
        fmtStr = Program.fetchString(Number(addr));
    }
    
    var nArgs;
    /* 
     * On the 28x, 55L, and 55H the arguments may need to be unpacked.
     * On the 55 small model, the args are only 16-bits and don't have
     * room for packing.
     */
    if ((ROV.getISA() == '28') ||
        ((ROV.getISA() == '55') && (!ROV.getTargetName().equals("C55")))) {
        nArgs = unpackArgs(fmtStr, args);
    }
    else {
        nArgs = args;
    }

    /* Format the string using mprintf and return the formatted string. */
    return(Packages.xdc.rta.Formatter.doPrint(fmtStr, nArgs));
}

/*
 *  ======== decodeEvent ========
 *  Returns the formatted message from the specified system event.
 *
 *  The decoding of the events comes from _log.h in the cuda tree and the vbd
 *  source code (CCS 3 RTA) in /db/ztree/library/trees/sarta-d05/src/vbd
 */ 
function decodeEvent(rec)
{
    var TSK = xdc.useModule('ti.bios.rov.TSK');
    var SWI = xdc.useModule('ti.bios.rov.SWI');
    var SEM = xdc.useModule('ti.bios.rov.SEM');
    var ROV = xdc.useModule('ti.bios.rov.ROV');

    /* Decode the event based on rec.val3 */
    switch (Number(rec.val3)) {
        
        case 0:
            /* 
             * _log.h: #define _LOG_PRDBEGIN    0   // handle = prd, arg0 = 0
             * _VSM_systemFormats[_LOG_PRDBEGIN] = "PRD: begin %s (0x%04x)%s";
             * example: "PRD: begin prdClock0 (0x13de8)"
             * 
             * PRD doesn't have dynamic name.
             */
            var addr = Number(rec.val2);
            var nickName = ROV.getNickName(ROV.getStaticName(addr), addr); 
            return("PRD: begin " + nickName);
        
        case 1:
            /* 
             * _log.h: #define _LOG_PRDEND    1   // handle = 0, arg0 = 0
             * _VSM_systemFormats[_LOG_PRDEND]   = "PRD: end";
             * example: "PRD: end"
             */
            return("PRD: end");
        
        case 2:
            /*
             * _log.h: #define _LOG_SWIPOST    2   // handle = swi, arg0 = 0
             * _VSM_systemFormats[_LOG_SWIPOST]  = "SWI: post  %s (0x%04x)%s";
             * example: "SWI: post PRD_swi (0x13a4c)"
             */
             var addr = Number(rec.val2);
             return("SWI: post " + SWI.getNickName(addr));
        
        case 3:
            /*
             * _log.h: #define _LOG_SWIBEGIN   3   // handle = swi, arg0 = 0
             * _VSM_systemFormats[_LOG_SWIBEGIN] = "SWI: begin %s (0x%04x)%s";
             * example:  SWI: begin KNL_swi (TSK scheduler) (0x13a20)
             */
            var handle = SWI.fxnToHandle(Number(rec.val2));
            return("SWI: begin " + SWI.getNickName(handle));
        
        case 4:
            /* 
             * _log.h: #define _LOG_SWIEND   4   // handle = swi, arg0 = swi->lock
             * _VSM_systemFormats[_LOG_SWIEND]   = "SWI: end   %s (0x%04x) state = %s";
             * example: SWI: end   PRD_swi (0x13a4c) state = done
             *
             * From vsm.c:
             *   elem->arg2 = (Arg)(event->asa.system.asa.thread.arg0 == 0 ? "still ready" : "done");
             */
            var handle = SWI.fxnToHandle(Number(rec.val2));
            var state = (rec.val1 == 0) ? "still ready" : "done";
            return("SWI: end " + SWI.getNickName(handle) + " state = " + state);
        
        case 5:
            /*
             * _log.h: #define _LOG_PRDTICK    5   // tick.high = PRD_D_timh, tick.low = PRD_D_timl
             * _VSM_systemFormats[_LOG_PRDTICK]  = "PRD: tick count = %d (0x%08x)%s";
             * example: PRD: tick count = 5 (0x00000005)
             */
            var tickCount;
            /* 28x and 55x are 16-bit value in rec.val2 */
            if ((ROV.getISA() == '55') || (ROV.getISA() == '28')) {
                tickCount = Number(rec.val2);
            }
            /* 6x is 32-bit value in rec.val1 */
            else {
                tickCount = Number(rec.val1);
            }
            return("PRD: tick count = " + tickCount + " (" + countToHex(tickCount) + ")");
        
        case 6:
            /*
             * _log.h: #define _LOG_CLKINT    6   // tick.high = CLK_R_timh, tick.low = CLK_R_timl
             * _VSM_systemFormats[_LOG_CLKINT]   = "CLK: current time = %d (0x%08x)%s";
             * example: CLK: current time = 6 (0x00000006)
             */
            var tickCount;
            /* 28x and 55x are 16-bit value in rec.val2 */
            if ((ROV.getISA() == '55') || (ROV.getISA() == '28')) {
                tickCount = Number(rec.val2);
            }
            /* 6x is 32-bit value in rec.val1 */
            else {
                tickCount = Number(rec.val1);
            }
            return("CLK: current time = " + tickCount + " (" + countToHex(tickCount) + ")");
            
        case 7:
            /*
             * This event does not appear to be implemented in BIOS 5.
             * _log.h: #define _LOG_HWIBEGIN  7   // handle = hwi id, arg0 = 0
             * _VSM_systemFormats[_LOG_HWIBEGIN] = "HWI: begin";
             */
            return("HWI: begin");
            
        case 8:
            /*
             * _log.h: #define _LOG_USRMSG  8   // user message (format arg0)
             * exmple:
             */
            var args = [Number(rec.val1)];
            var msg = getMessage(rec.val2, args);
            return(msg);
        
        case 9:
            /*
             * _log.h: #define _LOG_USRERR  9   // user error (format arg0)
             * example: SYS_error called: error id = 0x1
             */
            var args = [Number(rec.val1)];
            var msg = getMessage(rec.val2, args);
            return(msg);
        
        case 10: 
            /*
             * _log.h: #define _LOG_TSKBLOCKED  10  // handle = tsk, arg0 = 0
             * _VSM_systemFormats[_LOG_TSKBLOCKED] = "TSK: blocked %s (0x%08x) on %s";
             * example: TSK: blocked task1 (0x000137b0) on <unknown handle> SEM
             */
            var addr = Number(rec.val2)
            return("TSK: blocked " + TSK.getNickName(addr));

        case 11:
            /*
             * _log.h: #define _LOG_TSKDONE  11  // handle = tsk, arg0 = 0
             * _VSM_systemFormats[_LOG_TSKDONE] = "TSK: terminated %s (0x%08x)%s";
             * example: TSK: terminated task0 (0x0001170c)
             */
            var addr = Number(rec.val2);
            return ("TSK: terminated " + TSK.getNickName(addr));
        
        case 12:
            /*
             * _log.h: #define _LOG_TSKRUNNING  12  // handle = tsk, arg0 = 0
             * _VSM_systemFormats[_LOG_TSKRUNNING] = "TSK: running %s (0x%08x)%s";
             * example: TSK: running task1 (0x000137b0)
             */
            return("TSK: running " + TSK.getNickName(Number(rec.val2)));
            
        case 13:
            /*
             * _log.h: #define _LOG_TSKREADY  13  // handle = tsk, arg0 = 0
             * _VSM_systemFormats[_LOG_TSKREADY] = "TSK: ready %s (0x%08x)%s";
             * example: TSK: ready task1 (0x000137b0)
             */
            return ("TSK: ready " + TSK.getNickName(Number(rec.val2)));
        
        case 14:
            /*
             * _log.h: #define _LOG_SEMPOST  14  // handle = sem, arg0 = sem count
             * _VSM_systemFormats[_LOG_SEMPOST] = "SEM: post %s (0x%04x) count = %d";
             * example: SEM: post <unknown handle> (0x13dc8) count = 0
             */
            var addr = Number(rec.val2);
            return ("SEM: post " + SEM.getNickName(addr));
        
        case 15:
            /*
             * _log.h: #define _LOG_TSKYIELD  15  // handle = tsk, arg0 = 0
             * _VSM_systemFormats[_LOG_TSKYIELD] = "TSK: yield %s (0x%08x)%s";
             * example: TSK: yield task0 (0x0001170c)
             */
            var addr = Number(rec.val2);
            return ("TSK: yield " + TSK.getNickName(addr));
        
        case 16:
            /*
             * This event does not appear to be handled by VBD.
             * _log.h: #define _LOG_PWRMRSRCCHNG  16  // arg0 = id, arg1 = 0(off) or 1(on)
             * example:
             */
            var off = (rec.val2 == 0) ? "off" : "on";
            return ("PWRM: Source Change id: " + rec.val1 + " " + off);

        default:
            return ("Unknown event id " + rec.val3);
    }

    return(msg);
}

/* Convert the count to hex and pad with 8 places. */
function countToHex(count)
{
    var str = Number(count).toString(16);
    while (str.length < 8) {
        str = "0" + str;
    }
    
    return ("0x" + str);
} 

/*
 *  ======== unpackArgs ========
 *  Unpacks the printf arguments which are packed into arg1 and arg2.
 *
 *  LOG_printf does not actually adhere to the structure of the LOG_Record, it
 *  does not simply copy one argument into arg1 and another into arg2. When
 *  LOG_printf is called, the arguments are copied to the stack (they are var
 *  args), and then copied directly into the LOG_record. In the 8-bytes of
 *  space in arg1 and arg2.
 *
 *  This does not apply to arg3 which holds the format string address.
 *
 *  On targets with 16-bit characters, some of these arguments may be 16-bits,
 *  so the LOG_record needs to be unpacked to retrieve the correct arguments.
 *
 *  To determine the actual size of the arguments, we first parse the format
 *  string.
 *
 *  To unpack the arguments, we begin by calculating all of the possible
 *  argument values. There are four possible spots for a 16-bit argument
 *  and three possible spots for a 32-bit argument. We calculate all of these
 *  potential argument values, then create the list of correct arguments
 *  using the size information retrieved from parsing the format string.
 * 
 *  Some packing examples:
 *    arg1   --------------       arg1   --------------
 *           | 16-bit arg |              | 16-bit arg |
 *           --------------              --------------
 *           | 16-bit arg |              | 32-bit arg |
 *    arg2   --------------       arg2   |            |
 *           | 32-bit arg |              --------------
 *           |            |              | 16-bit arg |
 *           --------------              --------------
 */                      
function unpackArgs(fmt, args)
{
    /* Parse the format string to get the correct argument sizes. */
    var types = getArgTypes(fmt);
    
    /* Pre-compute all possible 16-bit arg values. */
    var args16 = new Array();
    args16[0] = (args[0] & 0xFFFF0000) >> 16;
    args16[1] = args[0] & 0x0000FFFF;
    args16[2] = (args[1] & 0xFFFF0000) >> 16;
    args16[3] = args[1] & 0x0000FFFF;
    
    /* Pre-compute all possible 32-bit arg values. */
    var args32 = new Array();
    args32[0] = args[0];
    args32[1] = (args16[1] << 16) | args16[2];
    args32[2] = args[1];
    
    /* 
     * Create the new args array using the sizes from the format string and the
     * pre-computed argument values in args16 and args32.
     * 'index' is a running index into the args16 and args32 array. 'index' is
     * essentially an offset into the four 16-bit spaces in arg1 and arg2.
     */
    var newArgs = new Array();
    var index = 0;
    for (var i = 0; i < types.length; i++) {
        var t = types[i];
        
        /* If the argument size is 16-bits, take from the 16-bit args. */
        if (t.size == 16) {
            var val = args16[index];
            
            /* 
             * The xdc.rta.Formatter expects all of the arguments to be the size 
             * of the type IArg (32-bits on all BIOS 5 targets), so we must cast
             * the 16-bit values before using them.
             */
      
            /* 
             * If the type of the argument is unsigned, ensure that the 16-bit
             * value has not been sign-extended. 'val' should be positive before
             * passing to the Formatter.
             * e.g., -1 should become 65535.
             * 
             * If the value is negative, it must have been sign extended. Add
             * 2^16 to the value to remove the sign extension.
             */
            if (!t.signed && (val < 0)) {
                val = val + 0x10000;
            }
            /*
             * If the type of the argument is signed, ensure that the 16-bit
             * value has been sign extended.
             * 
             * To do this, we shift the 16-bit value left, then right. On the
             * right shift, the value will be sign-extended based on the MSB.
             *
             * e.g. 65423 should become -113.
             */
            else if (t.signed) {
                val = (val << 16) >> 16;
            }
            
            newArgs[newArgs.length] = val;
        }
        /* 
         * Otherwise, if the size of the arg is 32-bits take from the 
         * 32-bit args.
         */
        else {
            newArgs[newArgs.length] = args32[index];
        }
        
        /* Move the index forward based on the number of bits consumed. */
        index += t.size / 16;
    }
    
    return (newArgs);
}

/*
 *  ======== getArgTypes ========
 *  Parses the printf format string to determine the sizes of the arguments.
 *
 *  The sizes are hardcoded because this API is only called for 28x and 55x
 *  targets.
 *
 *  See 'unpackArgs'.
 */
function getArgTypes(fmt)
{
    var sizes = new Array();

    var p = java.util.regex.Pattern.compile("%((\\d+)?([cdouxpsr%])|\\$([ALMR]))");
        
    var m = p.matcher(fmt);

    var start = 0;
    
    /* Get the sizes of the types in bits. */
    var intSize = Program.build.target.stdTypes['t_Int'].size *
                  Program.build.target.bitsPerChar;
    var ptrSize = Program.build.target.stdTypes['t_Ptr'].size *
                  Program.build.target.bitsPerChar;   
    
    while (m.find(start)) {
        if (m.group(3) != null) {
            /* Convert to JavaScript string */
            var ch = String(m.group(3)); 
            switch (ch) {
                case 'c':
                case 'd':
                case 'o':
                case 'x':
                    var t = {};
                    t.size = 16;
                    t.signed = true;
                    sizes[sizes.length] = t;
                    break;
                case 'u':
                    var t = {};
                    t.size = intSize;
                    t.signed = false;
                    sizes[sizes.length] = t;
                    break;
                case 'p':
                case 's':
                case 'r':
                    var t = {};
                    t.size = ptrSize;
                    t.signed = false;
                    sizes[sizes.length] = t;
                    break;
                default:
                    break;
            }
        }
        start = m.end();
    }

    return (sizes);
}
