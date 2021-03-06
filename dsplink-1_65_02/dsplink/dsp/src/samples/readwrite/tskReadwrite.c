/** ============================================================================
 *  @file   tskReadwrite.c
 *
 *  @path   $(DSPLINK)/dsp/src/samples/readwrite/
 *
 *  @desc   This is simple TSK based application that uses SIO interface to
 *          implement readwrite for GPP. It receives data from the a input
 *          channel and send the same data back from output channel. Input and
 *          output channel numbers are configurable through header file of this
 *          application. It also uses a message queue to receive a
 *          scaling factor for the output data.
 *
 *  @ver    1.65.02.09
 *  ============================================================================
 *  Copyright (C) 2002-2012, Texas Instruments Incorporated -
 *  http://www.ti.com/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  ============================================================================
 */


/*  ----------------------------------- DSP/BIOS Headers            */
#include <std.h>
#include <log.h>
#include <swi.h>
#include <sys.h>
#include <sio.h>
#include <tsk.h>
#include <msgq.h>
#include <pool.h>

/*  ----------------------------------- DSP/BIOS LINK Headers       */
#include <failure.h>
#include <dsplink.h>
#include <platform.h>
#include <hal_cache.h>

#if defined (DSP_BOOTMODE_NOBOOT)
#include <zcpy_mqt.h>
#include <sma_pool.h>
#include <dsplinkmsgq.h>
#endif

/*  ----------------------------------- Sample Headers              */
#include <tskReadwrite.h>
#include <readwrite.h>
#include <readwrite_config.h>


/** ============================================================================
 *  @const  FILEID
 *
 *  @desc   FILEID is used by SET_FAILURE_REASON macro.
 *  ============================================================================
 */
#define FILEID  FID_APP_C

/** ============================================================================
 *  @name   trace
 *
 *  @desc   trace LOG_Obj used to do LOG_printf
 *  ============================================================================
 */
extern LOG_Obj trace ;

/** ============================================================================
 *  @name   numTransfers
 *
 *  @desc   Iterations of data transfer to be done by the application.
 *  ============================================================================
 */
extern Uint32 numTransfers ;

#if defined (DSP_BOOTMODE_NOBOOT)
/** ============================================================================
 *  @name   smaPoolObj
 *
 *  @desc   Global object for pool parameters for the dynamic POOL_open call
 *  ============================================================================
 */
SMAPOOL_Params            smaPoolObj ;
/** ============================================================================
 *  @name   MESSAGE_MqtParams
 *
 *  @desc   Extern declaration for msgq parameters for the array of pools
 *  ============================================================================
 */
extern ZCPYMQT_Params  mqtParams ;
#endif

/** ============================================================================
 *  @func   TSKRDWR_create
 *
 *  @desc   Create phase function for the TSKRDWR application. Initializes the
 *          TSKRDWR_TransferInfo structure with the information that will be
 *          used by the other phases of the application.
 *
 *  @modif  None.
 *  ============================================================================
 */
Int TSKRDWR_create(TSKRDWR_TransferInfo ** infoPtr)
{
    Int                     status    = SYS_OK ;
    MSGQ_Attrs              msgqAttrs = MSGQ_ATTRS ;
    TSKRDWR_TransferInfo *  info      = NULL ;
    MSGQ_LocateAttrs        syncLocateAttrs ;

#if defined (DSP_BOOTMODE_NOBOOT)
    MSGQ_TransportObj         transport ;
    POOL_Obj                  poolObj ;

    smaPoolObj.poolId        = 0;
    smaPoolObj.exactMatchReq = TRUE ;
    poolObj.initFxn = SMAPOOL_init ;
    poolObj.fxns    = (POOL_Fxns *) &SMAPOOL_FXNS ;
    poolObj.params  = &(smaPoolObj) ;
    poolObj.object  = NULL ;

    status = POOL_open (0, &poolObj) ;

    if (status == SYS_OK) {
        mqtParams.poolId  = 0 ;
        transport.initFxn = ZCPYMQT_init ;         /* Init Function                 */
        transport.fxns    = (MSGQ_TransportFxns *) &ZCPYMQT_FXNS ;     /* Transport interface functions */
        transport.params  = &mqtParams ;   /* Transport params              */
        transport.object  = NULL ;                 /* Filled in by transport        */
        transport.procId  = ID_GPP  ;              /* Processor Id                  */

        status = MSGQ_transportOpen (ID_GPP, &transport) ;
     }
#endif

    /* Allocate TSKRDWR_TransferInfo structure that will be initialized
     * and passed to other phases of the application */
    *infoPtr = MEM_calloc (DSPLINK_SEGID,
                           sizeof (TSKRDWR_TransferInfo),
                           DSPLINK_BUF_ALIGN) ;
    if (*infoPtr == NULL) {
        status = SYS_EALLOC ;
        SET_FAILURE_REASON (status) ;
    }
    else {
        info = *infoPtr ;
    }

    /* The GPP side will be waiting for DSP to open a MSGQ. Open the local
     * MSGQ first.
     */
    if (status == SYS_OK) {
        /* Set the semaphore to a known state. */
        SEM_new (&(info->notifyDspSemObj), 0) ;

        /* Fill in the attributes for this message queue. */
        msgqAttrs.notifyHandle = &(info->notifyDspSemObj) ;
        msgqAttrs.pend         = (MSGQ_Pend) SEM_pendBinary ;
        msgqAttrs.post         = (MSGQ_Post) SEM_postBinary ;

        /* Creating message queue */
        status = MSGQ_open (DSP_MSGQNAME, &info->dspMsgqQueue, &msgqAttrs) ;
        if (status != SYS_OK) {
            SET_FAILURE_REASON (status) ;
        }
    }

    /*  Now locate the GPP message queue  */
    if (status == SYS_OK) {
        /* Synchronous locate. */
        status = SYS_ENOTFOUND ;
        while ((status == SYS_ENOTFOUND) || (status == SYS_ENODEV)) {
            syncLocateAttrs.timeout = SYS_FOREVER ;
            status = MSGQ_locate (GPP_MSGQNAME,
                                  &info->gppMsgqQueue,
                                  &syncLocateAttrs) ;
            if ((status == SYS_ENOTFOUND) || (status == SYS_ENODEV)) {
                TSK_sleep (1000) ;
            }
            else if (status != SYS_OK) {
                LOG_printf (&trace, "MSGQ_locate (msgqOut) failed. "
                            "Status = 0x%x\n", status) ;
            }
        }
    }

    if (status == SYS_OK) {
        /* Filling up the transfer info structure */
        info->numTransfers  = numTransfers ;
    }

    return status ;
}


/** ============================================================================
 *  @func   TSKRDWR_execute
 *
 *  @desc   Execute phase function for the TSKRDWR application. Application
 *          receives the data from the input channel and sends the same data
 *          back on output channel. Channel numbers can be configured through
 *          header file.
 *
 *  @modif  None.
 *  ============================================================================
 */
Int TSKRDWR_execute(TSKRDWR_TransferInfo * info)
{
    Int             status    = SYS_OK;
    Char *          readBuf ;
    Char *          writeBuf ;
    Uint32          scalingFactor ;
    Uint32          size ;
    Uint32          i, j;
    SampleMessage * msg;

    /* Execute the loop for configured number of transfers
     * A value of 0 in numTransfers implies infinite iterations
     */
    for (i = 0 ;
         (   ((info->numTransfers == 0) || (i < info->numTransfers))
          && (status == SYS_OK)) ;
         i++) {
        /* Wait for the messaging containing information about data buffer */
        status = MSGQ_get (info->dspMsgqQueue, (MSGQ_Msg *) &msg, SYS_FOREVER) ;
        if (status == SYS_OK) {
            readBuf       = (Char *) msg->gppWriteAddr ;
            writeBuf      = (Char *) msg->dspWriteAddr ;
            size          = msg->size ;
            scalingFactor = msg->scalingFactor ;

            HAL_cacheInv ((Ptr) readBuf, size) ;

            for (j = 0 ; j < size ; j++) {
                writeBuf [j] = (Char) (readBuf [j] * scalingFactor) ;
            }

            HAL_cacheWbInv ((Ptr)(msg->dspWriteAddr), size) ;

            /* Now send a message to the GPP */
            status = MSGQ_put (info->gppMsgqQueue, (MSGQ_Msg) msg) ;
            if (status != SYS_OK) {
                SET_FAILURE_REASON(status);
            }
        }
    }

    return status ;
}


/** ============================================================================
 *  @func   TSKRDWR_delete
 *
 *  @desc   Delete phase function for the TSKRDWR application. It deallocates
 *          all the resources of allocated during create phase of the
 *          application.
 *
 *  @modif  None.
 *  ============================================================================
 */
Int TSKRDWR_delete (TSKRDWR_TransferInfo * info)
{
    Int         status     = SYS_OK ;
    Bool        freeStatus = FALSE ;

    /* Delete the message queue */
    if (info->dspMsgqQueue != NULL) {
        status = MSGQ_close (info->dspMsgqQueue) ;
        if (status != SYS_OK) {
            SET_FAILURE_REASON (status) ;
        }
    }

    /* Free the info structure */
    freeStatus = MEM_free(DSPLINK_SEGID, info, sizeof (TSKRDWR_TransferInfo));
    if (freeStatus != TRUE) {
        status = SYS_EFREE;
        SET_FAILURE_REASON(status);
    }

    return status;
}
