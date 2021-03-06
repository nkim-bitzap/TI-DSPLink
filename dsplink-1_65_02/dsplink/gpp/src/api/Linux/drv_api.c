/** ============================================================================
 *  @file   drv_api.c
 *
 *  @path   $(DSPLINK)/gpp/src/api/Linux/
 *
 *  @desc   User side driver wrapper that does proper ioctl calls for each
 *          API.
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


/*  ----------------------------------- OS Specific Headers         */
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/*  ----------------------------------- DSP/BIOS Link               */
#include <dsplink.h>
#include <_dsplink.h>

#if defined (CHNL_COMPONENT)
#include <chnldefs.h>
#endif /* if defined (CHNL_COMPONENT) */
#if defined (POOL_COMPONENT)
#include <_pool.h>
#include <pooldefs.h>
#endif /* if defined (POOL_COMPONENT) */
#if defined (MPLIST_COMPONENT)
#include <mplistdefs.h>
#endif  /* if defined (MPLIST_COMPONENT) */
#if defined (RINGIO_COMPONENT)
#include <ringiodefs.h>
#endif  /* if defined (RINGIO_COMPONENT) */
#if defined (MPCS_COMPONENT)
#include <mpcsdefs.h>
#endif  /* if defined (MPCS_COMPONENT) */

/*  ----------------------------------- Trace & Debug               */
#include <_trace.h>

/*  ----------------------------------- OSAL Headers                */
#include <drv_api.h>
#include <drvdefs.h>

/*  ----------------------------------- API                         */
#include <proc.h>
#if defined (POOL_COMPONENT)
#include <pool.h>
#endif /* if defined (POOL_COMPONENT) */
#if defined (MSGQ_COMPONENT)
#include <msgq.h>
#endif /* if defined (MSGQ_COMPONENT) */
#include <_proc.h>
#include <_sync_usr.h>

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

/** ============================================================================
 *  @macro  COMPONENT_ID
 *
 *  @desc   Identifier for sub-component.
 *  ============================================================================
 */
#define  COMPONENT_ID       ID_OSAL_DRV

/** ============================================================================
 *  @macro  LINK_DRIVER_NAME
 *
 *  @desc   Name of the link driver.
 *  ============================================================================
 */
#define  LINK_DRIVER_NAME   "/dev/dsplink"

/** ============================================================================
 *  @const  INIT_RESOURCE_COUNT
 *
 *  @desc   Indicates the initial resource count for the semaphore.
 *  ============================================================================
 */
#define INIT_RESOURCE_COUNT       1

/** ============================================================================
 *  @const  DRV_KEY_CS
 *
 *  @desc   Value to be used for generating the key for DRV CS.
 *  ============================================================================
 */
#define DRV_KEY_CS                'd'

/** ============================================================================
 *  @const  MAX_DRV_CS
 *
 *  @desc   Maximum number of CS objects that can be created.
 *  ============================================================================
 */
#define MAX_DRV_CS                 1

/** ============================================================================
 *  @const  OS_EFAILURE
 *
 *  @desc   Status code indicating error from the OS calls.
 *  ============================================================================
 */
#define OS_EFAILURE               -1

/** ============================================================================
 *  @const  SEMOP_ALLOC_ONE_RESOURCE
 *
 *  @desc   Indicates that one resource is to be allocated.
 *  ============================================================================
 */
#define SEMOP_ALLOC_ONE_RESOURCE  -1

/** ============================================================================
 *  @const  SEMOP_FREE_ONE_RESOURCE
 *
 *  @desc   Indicates that one resource is to be freed.
 *  ============================================================================
 */
#define SEMOP_FREE_ONE_RESOURCE   1

/** ============================================================================
 *  @macro  SET_FAILURE_REASON
 *
 *  @desc   Sets failure reason.
 *  ============================================================================
 */
#if defined (DDSP_DEBUG)
#define SET_FAILURE_REASON  \
            TRC_3PRINT (TRC_LEVEL7, \
                        "\nFailure: Status:[0x%x] File:[0x%x] Line:[%d]\n", \
                        status, FID_C_OSAL_DRV_API, __LINE__)
#else
#define SET_FAILURE_REASON
#endif /* if defined (DDSP_DEBUG) */


#if defined (CHNL_COMPONENT)
/** ============================================================================
 *  @name   DRV_chnlIdToPoolIdMap
 *
 *  @desc   Pointer to a map table that contain information about the channel ID
 *          to pool ID mappings. This table physically exists on the kernel side
 *  ============================================================================
 */
STATIC Uint32 (* DRV_chnlIdToPoolIdMap) [MAX_CHANNELS] = NULL ;
#endif /* if defined (CHNL_COMPONENT) */

/** ============================================================================
 *  @name   DRV_ProtectObject
 *
 *  @desc   This object is used by DRV_PROTECT API's.
 *
 *  @field  osCsId
 *              OS-specific ID of the semaphore set to be used.
 *  @field  csEntered
 *              Indicates whether the CS has been entered in this process.
 *
 *  @see    None
 *  ============================================================================
 */
typedef struct DRV_ProtectObject_tag {
    int    osCsId ;
    Bool   csEntered ;
} DRV_ProtectObject ;

/** ============================================================================
 *  @name   DSPLINK_skipExitHandler
 *
 *  @desc   Global flag to indicate that exit handler has already been
 *          called from signal handler.
 *  ============================================================================
 */
Bool DSPLINK_skipExitHandler = FALSE;

/** ============================================================================
 *  @name   DSPLINK_isSignal
 *
 *  @desc   Global flag to indicate whether execution is in signal context.
 *          Driver on the user-side.
 *  ============================================================================
 */
Bool DSPLINK_isSignal ;

/** ============================================================================
 *  @name   DRV_protectObj
 *
 *  @desc   Contains information for protecting DRV module.
 *  ============================================================================
 */
STATIC DRV_ProtectObject DRV_protectObj ;

/** ============================================================================
 *  @name   PROC_linkCfgPtr
 *
 *  @desc   Global pointer containing DSPLINK configuration information for the
 *          driver on the user-side.
 *  ============================================================================
 */
extern LINKCFG_Object * PROC_linkCfgPtr ;

/*  ----------------------------------------------------------------------------
 *  @name   PROC_stateObj
 *
 *  @desc   State object for the PROC user-level component containing internal
 *          state information required by it.
 *  ----------------------------------------------------------------------------
 */
extern PROC_Object PROC_stateObj ;

/*  ----------------------------------------------------------------------------
 *  @name   DRV_installCleanupRoutines
 *
 *  @desc   Install signal handler and atexit handler for cleanup.
 *
 *  @ret    None
 *  ----------------------------------------------------------------------------
 */
static
void
DRV_installCleanupRoutines (IN LINKCFG_Object * linkCfgPtr) ;


/*  ----------------------------------------------------------------------------
 *  @name   DSPLINK_atExitHandler
 *
 *  @desc   atexit handler for DSP/BIOS LINK. This ensures that the system
 *          is left in a correct state even if application does not perform
 *          the required shutdown operations.
 *
 *  @ret    None
 *  ----------------------------------------------------------------------------
 */
static
void
DSPLINK_atExitHandler (Void) ;


/*  ----------------------------------------------------------------------------
 *  @name   DSPLINK_sigHandler
 *
 *  @desc   Signal handler for incorrect behavior of user applications that may
 *          result in DSP/BIOS Link being left in an unusable state.
 *          This is a Linux specific implementation and equivalent
 *          implementation may not available on other operating systems.
 *
 *  @args   sigNum
 *              Signal number.
 *
 *  @ret    None
 *  ----------------------------------------------------------------------------
 */
static
void
DSPLINK_sigHandler (int sigNum) ;

/*******************************************************************************
  @name  getCmdString
  @desc  For debugging purposes get a printable name for a command
*******************************************************************************/

Char8 *getCmdString(Uint32 cmd)
{
  switch (cmd) {
    case BASE_CMD: return "BASE_CMD";
    case CMD_PROC_SETUP: return "CMD_PROC_SETUP";
    case CMD_PROC_DESTROY: return "CMD_PROC_DESTROY";
    case CMD_PROC_START: return "CMD_PROC_START";
    case CMD_PROC_STOP: return "CMD_PROC_STOP";
    case CMD_PROC_LOAD: return "CMD_PROC_LOAD";
    case CMD_PROC_LOADSECTION: return "CMD_PROC_LOADSECTION";
    case CMD_PROC_DETACH: return "CMD_PROC_DETACH";
    case CMD_PROC_ATTACH: return "CMD_PROC_ATTACH";
    case CMD_PROC_GETSTATE: return "CMD_PROC_GETSTATE";
    case CMD_PROC_CONTROL: return "CMD_PROC_CONTROL";
    case CMD_PROC_READ: return "CMD_PROC_READ";
    case CMD_PROC_WRITE: return "CMD_PROC_WRITE";
    case CMD_PROC_GETSYMBOLADDRESS: return "CMD_PROC_GETSYMBOLADDRESS";
    case CMD_PROC_SENDTERMEVT: return "CMD_PROC_SENDTERMEVT";
    case CMD_PROC_ISLASTDESTROY: return "CMD_PROC_ISLASTDESTROY";
    case CMD_PROC_ISLASTDETACH: return "CMD_PROC_ISLASTDETACH";
    case CMD_PROC_CLEANUP: return "CMD_PROC_CLEANUP";
    case CMD_PROC_ADDRTRANSLATE: return "CMD_PROC_ADDRTRANSLATE";

#if defined (DDSP_PROFILE)
    case CMD_PROC_INSTRUMENT: return "CMD_PROC_INSTRUMENT";
#endif

#if defined (DDSP_DEBUG)
    case CMD_PROC_DEBUG: return "CMD_PROC_DEBUG";
#endif

#if defined (CHNL_COMPONENT)
    case CMD_CHNL_CREATE: return "CMD_CHNL_CREATE";
    case CMD_CHNL_DELETE: return "CMD_CHNL_DELETE";
    case CMD_CHNL_ISSUE: return "CMD_CHNL_ISSUE";
    case CMD_CHNL_RECLAIM: return "CMD_CHNL_RECLAIM";
    case CMD_CHNL_ALLOCATEBUFFER: return "CMD_CHNL_ALLOCATEBUFFER";
    case CMD_CHNL_FREEBUFFER: return "CMD_CHNL_FREEBUFFER";
    case CMD_CHNL_IDLE: return "CMD_CHNL_IDLE";
    case CMD_CHNL_FLUSH: return "CMD_CHNL_FLUSH";
    case CMD_CHNL_CONTROL: return "CMD_CHNL_CONTROL";
    case CMD_DRV_GETCHNLMAPTABLE_ADDRESS:
      return "CMD_DRV_GETCHNLMAPTABLE_ADDRESS";

#if defined (DDSP_PROFILE)
    case CMD_CHNL_INSTRUMENT: return "CMD_CHNL_INSTRUMENT";
#endif

#if defined (DDSP_DEBUG)
    case CMD_CHNL_DEBUG: return "CMD_CHNL_DEBUG";
#endif

#endif /* CHNL_COMPONENT */

#if defined (MSGQ_COMPONENT)
    case CMD_MSGQ_TRANSPORTOPEN: return "CMD_MSGQ_TRANSPORTOPEN";
    case CMD_MSGQ_TRANSPORTCLOSE: return "CMD_MSGQ_TRANSPORTCLOSE";
    case CMD_MSGQ_OPEN: return "CMD_MSGQ_OPEN";
    case CMD_MSGQ_CLOSE: return "CMD_MSGQ_CLOSE";
    case CMD_MSGQ_LOCATE: return "CMD_MSGQ_LOCATE";
    case CMD_MSGQ_LOCATEASYNC: return "CMD_MSGQ_LOCATEASYNC";
    case CMD_MSGQ_RELEASE: return "CMD_MSGQ_RELEASE";
    case CMD_MSGQ_ALLOC: return "CMD_MSGQ_ALLOC";
    case CMD_MSGQ_FREE: return "CMD_MSGQ_FREE";
    case CMD_MSGQ_PUT: return "CMD_MSGQ_PUT";
    case CMD_MSGQ_GET: return "CMD_MSGQ_GET";
    case CMD_MSGQ_SETERRORHANDLER: return "CMD_MSGQ_SETERRORHANDLER";
    case CMD_MSGQ_COUNT: return "CMD_MSGQ_COUNT";

#if defined (DDSP_PROFILE)
    case CMD_MSGQ_INSTRUMENT: return "CMD_MSGQ_INSTRUMENT";
#endif

#if defined (DDSP_DEBUG)
    case CMD_MSGQ_DEBUG: return "CMD_MSGQ_DEBUG";
#endif

#endif /* MSGQ_COMPONENT */

    case CMD_POOL_OPEN: return "CMD_POOL_OPEN";
    case CMD_POOL_CLOSE: return "CMD_POOL_CLOSE";
    case CMD_POOL_ALLOC: return "CMD_POOL_ALLOC";
    case CMD_POOL_FREE: return "CMD_POOL_FREE";
    case CMD_POOL_TRANSLATEADDR: return "CMD_POOL_TRANSLATEADDR";
    case CMD_POOL_RECONFIGURE: return "CMD_POOL_RECONFIGURE";
    case CMD_POOL_WRITEBACK: return "CMD_POOL_WRITEBACK";
    case CMD_POOL_INVALIDATE: return "CMD_POOL_INVALIDATE";

#if defined (MPCS_COMPONENT)
    case CMD_MPCS_MAPREGION: return "CMD_MPCS_MAPREGION";
    case CMD_MPCS_UNMAPREGION: return "CMD_MPCS_UNMAPREGION";
#endif

    case CMD_NOTIFY_INITIALIZE: return "CMD_NOTIFY_INITIALIZE";
    case CMD_NOTIFY_FINALIZE: return "CMD_NOTIFY_FINALIZE";
    case CMD_NOTIFY_REGISTER: return "CMD_NOTIFY_REGISTER";
    case CMD_NOTIFY_UNREGISTER: return "CMD_NOTIFY_UNREGISTER";
    case CMD_NOTIFY_NOTIFY: return "CMD_NOTIFY_NOTIFY";

#if defined (DDSP_PROFILE)
    case CMD_NOTIFY_INSTRUMENT: return "CMD_NOTIFY_INSTRUMENT";
#endif

    case CMD_RINGIO_MAPREGION: return "CMD_RINGIO_MAPREGION";
    case CMD_RINGIO_UNMAPREGION: return "CMD_RINGIO_UNMAPREGION";

    case CMD_MPLIST_MAPREGION: return "CMD_MPLIST_MAPREGION";
    case CMD_MPLIST_UNMAPREGION: return "CMD_MPLIST_UNMAPREGION";

    case CMD_IDM_INIT: return "CMD_IDM_INIT";
    case CMD_IDM_EXIT: return "CMD_IDM_EXIT";
    case CMD_IDM_CREATE: return "CMD_IDM_CREATE";
    case CMD_IDM_DELETE: return "CMD_IDM_DELETE";
    case CMD_IDM_ACQUIREID: return "CMD_IDM_ACQUIREID";
    case CMD_IDM_RELEASEID: return "CMD_IDM_RELEASEID";

    default: return "CMD_INVALID (UNCONFIGURED)";
  }
}

/** ============================================================================
 *  @name   DRV_Initialize
 *
 *  @desc   Initialization function for the driver.
 *
 *  @modif  None.
 *  ============================================================================
 */

NORMAL_API DSP_STATUS DRV_Initialize(OUT DRV_Object ** drvObj,
                                     IN OUT Pvoid arg)
{
  DSP_STATUS status = DSP_SOK;
  Int32 osStatus;

#if defined (CHNL_COMPONENT)
  Void *physicalAddr = NULL;
  size_t length;
  CMD_Args cmdArgs;
#endif

  TRC_2ENTER ("DRV_Initialize", drvObj, arg);
  DBC_Require (drvObj != NULL);

  if (drvObj == NULL) {
    status = DSP_EPOINTER;
    SET_FAILURE_REASON;
  }
  else if (*drvObj != NULL) {
    status = _SYNC_USR_enterCS (PROC_stateObj.syncCsObj);

    if (DSP_SUCCEEDED (status)) {
      (*drvObj)->refCount++;

      status = _SYNC_USR_leaveCS (PROC_stateObj.syncCsObj);

      if (DSP_FAILED (status)) {
        SET_FAILURE_REASON ;
      }
    }
    else {
      SET_FAILURE_REASON;
    }
  }
    else {
      *drvObj = (DRV_Object *) malloc (sizeof (DRV_Object));

      if (*drvObj != NULL) {
        (*drvObj)->driverHandle = open (LINK_DRIVER_NAME, O_SYNC | O_RDWR);

        if ((*drvObj)->driverHandle < 0) {
          perror ("dsplink driver open: " LINK_DRIVER_NAME);
          status = DSP_EFAIL;
          SET_FAILURE_REASON;
        }
        else {
          osStatus = fcntl ((*drvObj)->driverHandle, F_SETFD, FD_CLOEXEC);

          if (osStatus != 0) {
            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }
        }

        /* Associate this process with the file object. This allows
           the driver to detect when the application has been terminated */
        if (DSP_SUCCEEDED(status)) {
          osStatus = fcntl((*drvObj)->driverHandle, F_SETOWN, getpid());

          if (osStatus != 0) {
            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }
        }

#if defined (CHNL_COMPONENT)
        if (DSP_SUCCEEDED (status)) {
          osStatus = ioctl ((*drvObj)->driverHandle,
                            CMD_DRV_GETCHNLMAPTABLE_ADDRESS,
                            &cmdArgs);

          if (osStatus < 0) {
            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }
          else {
            physicalAddr = cmdArgs.apiArgs.drvPhyAddrArgs.phyAddr;
            length = sizeof (Uint32) * MAX_CHANNELS * MAX_DSPS;

            DRV_chnlIdToPoolIdMap = mmap (NULL,
                                          length,
                                          PROT_READ | PROT_WRITE,
                                          MAP_SHARED,
                                          (*drvObj)->driverHandle,
                                          (off_t) physicalAddr);

            if (DRV_chnlIdToPoolIdMap == (Void *) -1) {
              status = DSP_EFAIL;
              SET_FAILURE_REASON;
            }
          }

          if (DSP_FAILED (status)) {
            close ((*drvObj)->driverHandle) ;
          }
      }
#endif /* if defined (CHNL_COMPONENT) */

      if (DSP_SUCCEEDED (status)) {
        (*drvObj)->signature = SIGN_DRV ;
        (*drvObj)->refCount  = 1 ;
        (*drvObj)->pageSize = getpagesize();
      }
      else {
        (*drvObj)->signature = SIGN_NULL ;
        free (*drvObj) ;
        *drvObj = NULL;
      }
    }
    else {
      status = DSP_EMEMORY;
      SET_FAILURE_REASON;
    }
  }

  TRC_1LEAVE("DRV_Initialize", status);
  return status;
}

/*******************************************************************************
  @name  DRV_Finalize
  @desc  Finalize function for the driver
*******************************************************************************/

NORMAL_API DSP_STATUS DRV_Finalize(IN DRV_Object * drvObj,
                                   IN OUT Pvoid arg)
{
  DSP_STATUS status = DSP_SOK;
  int osStatus;

#if defined (CHNL_COMPONENT)
  Uint32 length;
#endif /* if defined (CHNL_COMPONENT) */

  TRC_2ENTER("DRV_Finalize", drvObj, arg);

  DBC_Require(drvObj != NULL);
  DBC_Require(IS_OBJECT_VALID(drvObj, SIGN_DRV));

  if (IS_OBJECT_VALID (drvObj, SIGN_DRV)) {
    /* This is called in protection from proc_detach, and for proc_destroy
       It is the last entity calling DRV_Finalize */
    if (drvObj->refCount > 0 ) {
      drvObj->refCount--;
    }

    if (drvObj->refCount == 0) {

#if defined (CHNL_COMPONENT)
      length =  sizeof (Uint32) * MAX_CHANNELS * MAX_DSPS;
      osStatus = munmap (DRV_chnlIdToPoolIdMap, length);

      if (osStatus == -1) {
        status = DSP_EFAIL;
        SET_FAILURE_REASON;
      }
#endif

      /* clear process id to indicate normal shutdown to driver */
      fcntl(drvObj->driverHandle, F_SETOWN, 0);

      osStatus = close (drvObj->driverHandle) ;

      drvObj->signature = SIGN_NULL ;
      drvObj->pageSize = 0;
      free (drvObj) ;
      drvObj = NULL ;

      if ((osStatus < 0) && DSP_SUCCEEDED(status)) {
        status = DSP_EFAIL;
        SET_FAILURE_REASON;
      }
      else if (DSP_SUCCEEDED (status)) {
        status = DSP_SFINALIZED;
      }
    }
  }
  else {
    status = DSP_EPOINTER;
    SET_FAILURE_REASON;
  }

  TRC_1LEAVE ("DRV_Finalize", status) ;
  return status;
}

/*******************************************************************************
  @name  DRV_Invoke
  @desc  Invokes the lower layer function, which is OS dependent
*******************************************************************************/

NORMAL_API DSP_STATUS DRV_Invoke(IN DRV_Object * drvObj,
                                 IN Uint32 cmdId,
                                 IN OUT Pvoid arg1,
                                 IN OUT Pvoid arg2)
{
  DSP_STATUS status = DSP_SOK;
  CMD_Args *args = arg1;
  int osStatus;

  TRC_4ENTER("DRV_Invoke", drvObj, cmdId, arg1, arg2);

  DBC_Require(((drvObj != NULL) && (IS_OBJECT_VALID (drvObj, SIGN_DRV)))
           || ((drvObj == NULL) && (cmdId == CMD_PROC_ATTACH)));

  if (IS_OBJECT_VALID(drvObj, SIGN_DRV) || (cmdId == CMD_PROC_ATTACH))
  {
    DBC_Assert(args != NULL);

    switch (cmdId) {

#if defined (MSGQ_COMPONENT)
      case CMD_MSGQ_PUT:
      {
        /* Get the pool ID from  the pool number and dsp processor ID.
           'args->apiArgs.msgqPutArgs.msg->poolId' is pool number and not
           pool ID in 1.60 stream */
        status = _POOL_xltBuf(args->apiArgs.msgqPutArgs.msg->poolId,
                              (Pvoid *) &args->apiArgs.msgqPutArgs.msg,
                              USR_TO_KNL);

        if (DSP_SUCCEEDED(status)) {
          osStatus = ioctl(drvObj->driverHandle, cmdId, args);

          if (osStatus < 0) {
            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }
        }

        break;
      }

      case CMD_MSGQ_GET:
      {
        osStatus = ioctl(drvObj->driverHandle, cmdId, args);

        if (osStatus < 0) {
          status = DSP_EFAIL;
          SET_FAILURE_REASON;
        }
        else if (DSP_SUCCEEDED(args->apiStatus)) {
          status = _POOL_xltBuf(
                        args->apiArgs.msgqGetArgs.poolId,
                        (Pvoid *) &args->apiArgs.msgqGetArgs.msgAddr,
                        KNL_TO_USR);

          if (DSP_FAILED(status)) {
            SET_FAILURE_REASON;
          }
        }

        break;
      }

#endif /* if defined (MSGQ_COMPONENT) */

#if defined (CHNL_COMPONENT)
      /*  Channel Issue & Reclaim is handled on top of switch statement
          to optimize the data transfer path */
      case CMD_CHNL_ISSUE:
      {
        ProcessorId procId = args->apiArgs.chnlIssueArgs.procId;
        ChannelId chnlId = args->apiArgs.chnlIssueArgs.chnlId;
        ChannelIOInfo *ioInfo = args->apiArgs.chnlIssueArgs.ioReq;
        Char8 *usrAddr = ioInfo->buffer;
        Char8 *addr = usrAddr;

        /* translate the buffer address to the kernel space. This means,
           we don't have to copy the buffer itself during 'ioctl' */
        status = _POOL_xltBuf(
                          DRV_chnlIdToPoolIdMap[procId][chnlId],
                          (Pvoid *) &addr,
                          USR_TO_KNL);

        if (DSP_SUCCEEDED(status)) {
          ioInfo->buffer = addr;

          osStatus = ioctl(drvObj->driverHandle, cmdId, args);

          if (osStatus < 0) {
            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }

          /* Restore the user address in the user structure */
          ioInfo->buffer = usrAddr;
        }
        else {
          status = DSP_EFAIL;
          SET_FAILURE_REASON;
        }

        break;
      }

      case CMD_CHNL_RECLAIM:
      {
        ProcessorId procId = args->apiArgs.chnlReclaimArgs.procId;
        ChannelId chnlId = args->apiArgs.chnlReclaimArgs.chnlId;
        ChannelIOInfo *ioInfo = args->apiArgs.chnlReclaimArgs.ioReq;

        osStatus = ioctl(drvObj->driverHandle, cmdId, args);

        if (osStatus < 0) {
          status = DSP_EFAIL;
          SET_FAILURE_REASON;
        }
        else if (DSP_SUCCEEDED (args->apiStatus)) {

          /* translate the buffer address back to the user space */
          status = _POOL_xltBuf(
                          DRV_chnlIdToPoolIdMap[procId][chnlId],
                          (Pvoid *) &ioInfo->buffer,
                          KNL_TO_USR);

          if (DSP_FAILED (status)) {
            SET_FAILURE_REASON;
          }
        }

        break;
      }

#endif /* if defined (CHNL_COMPONENT) */

#if defined (MSGQ_COMPONENT)
        case CMD_MSGQ_ALLOC:
            {
                osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;
                if (osStatus < 0) {
                    status = DSP_EFAIL ;
                    SET_FAILURE_REASON ;
                }
                else if (DSP_SUCCEEDED (args->apiStatus)) {
                    status = _POOL_xltBuf (
                               args->apiArgs.msgqAllocArgs.poolId,
                               (Pvoid *) &args->apiArgs.msgqAllocArgs.msgAddr,
                               KNL_TO_USR) ;
                    if (DSP_FAILED (status)) {
                        SET_FAILURE_REASON ;
                    }
                }
            }
            break ;

        case CMD_MSGQ_FREE:
            {
                status = _POOL_xltBuf (args->apiArgs.msgqFreeArgs.msg->poolId,
                                    (Pvoid *) &args->apiArgs.msgqFreeArgs.msg,
                                    USR_TO_KNL) ;
                if (DSP_SUCCEEDED (status)) {
                    osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;
                    if (osStatus < 0) {
                        status = DSP_EFAIL ;
                        SET_FAILURE_REASON ;
                    }
                }
            }
            break ;
#endif /* if defined (MSGQ_COMPONENT) */

#if defined (CHNL_COMPONENT)
        case CMD_CHNL_ALLOCATEBUFFER:
        {
          ProcessorId procId;
          ChannelId chnlId;
          Uint32 numBufs;
          Char8 **bufArray;
          Uint32 i;

          procId = args->apiArgs.chnlAllocateBufferArgs.procId;
          chnlId = args->apiArgs.chnlAllocateBufferArgs.chnlId;
          numBufs = args->apiArgs.chnlAllocateBufferArgs.numBufs;
          bufArray = args->apiArgs.chnlAllocateBufferArgs.bufArray;

          osStatus = ioctl(drvObj->driverHandle, cmdId, args);

          if (osStatus < 0) {
            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }
          else if (DSP_SUCCEEDED (args->apiStatus)) {
            /* translate each of the buffers (created in the kernel space)
               back to the user by translating its address. This way we
               don't have to worry about explicitly copying each buffer
               at the end of 'ioctl' */
            for (i = 0; (i < numBufs); i++) {
              status = _POOL_xltBuf(
                           DRV_chnlIdToPoolIdMap[procId][chnlId],
                           (Pvoid *) &(bufArray[i]),
                           KNL_TO_USR);

              DBC_Assert(DSP_SUCCEEDED(status));
            }
          }

          break;
        }

        case CMD_CHNL_FREEBUFFER:
        {
          ProcessorId procId;
          ChannelId chnlId;
          Uint32 numBufs;
          Char8 **bufArray;
          Uint32 i;

          procId = args->apiArgs.chnlFreeBufferArgs.procId;
          chnlId = args->apiArgs.chnlFreeBufferArgs.chnlId;
          numBufs = args->apiArgs.chnlFreeBufferArgs.numBufs;
          bufArray = args->apiArgs.chnlFreeBufferArgs.bufArray;

          /* similarly here, prior to calling 'ioctl' translate ach buffer
             address from the user to the kernel space */
          for (i = 0; (i < numBufs); i++) {
            status = _POOL_xltBuf(
                               DRV_chnlIdToPoolIdMap [procId][chnlId],
                               (Pvoid *) &(bufArray[i]),
                               USR_TO_KNL);

            DBC_Assert(DSP_SUCCEEDED (status));
          }

          osStatus = ioctl(drvObj->driverHandle, cmdId, args);

          if (osStatus < 0) {
            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }

          break;
        }
#endif /* if defined (CHNL_COMPONENT) */

#if defined (RINGIO_COMPONENT)
        case CMD_RINGIO_MAPREGION:
            {
                osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;

                if (osStatus < 0) {
                    status = DSP_EFAIL ;
                    SET_FAILURE_REASON ;
                }
                else {
                    /* mmap the region in user space */
                    RingIO_MemInfo * mapInfo = (RingIO_MemInfo *)
                                  &(args->apiArgs.ringIoArgs.ringioRegionArgs) ;
                    Uint32 userAddr ;
                    Uint32 addr ;
                    Uint32 size ;

                    size = mapInfo->size ;
                    addr = mapInfo->physAddr ;
                    /** --------------------------------------------------------
                     *  Align the physical address to page boundary
                     *  --------------------------------------------------------
                     */
                    size = size + (addr % drvObj->pageSize) ;
                    addr = addr - (addr % drvObj->pageSize) ;

                    userAddr = (Uint32) mmap (
                                 NULL,
                                 size,
                                 PROT_READ | PROT_WRITE,
                                 MAP_SHARED,
                                 drvObj->driverHandle,
                                 (off_t) addr) ;

                    if (userAddr == (Uint32) MAP_FAILED) {
                        TRC_0PRINT (
                                TRC_LEVEL7,
                                "Couldn't map DSP memory"
                                " in user space\n") ;
                        status = DSP_EFAIL ;
                        SET_FAILURE_REASON ;
                    }
                    else {
                        /** ----------------------------------------------------
                         *  change the user address to reflect the actual user
                         *  address of memory block mapped. This is done since
                         *  during mmap memory block was shifted(+-) so that it
                         *  is aligned to page boundary.
                         *  ----------------------------------------------------
                         */
                        mapInfo->userAddr =  userAddr
                                           + (mapInfo->physAddr % drvObj->pageSize) ;
                    }
                }
            }
            break ;

        case CMD_RINGIO_UNMAPREGION:
            {
                /* munmap the region in user space */
                RingIO_MemInfo * unmapInfo = (RingIO_MemInfo *)
                                &(args->apiArgs.ringIoArgs.ringioRegionArgs) ;
                Uint32 addr = unmapInfo->userAddr ;
                Uint32 size = unmapInfo->size ;

                /** ------------------------------------------------------------
                 *  Get the actual user address and size. Since these are
                 *  modified at the time of mmaping, to have memory block
                 *  page boundary aligned.
                 *  ------------------------------------------------------------
                 */
                size = size + (addr % drvObj->pageSize) ;
                addr = addr - (addr % drvObj->pageSize) ;
                munmap ((Void *)addr, size) ;
                args->apiStatus = DSP_SOK ;
            }
            break ;
#endif /* if defined (RINGIO_COMPONENT) */

#if defined (MPLIST_COMPONENT)
        case CMD_MPLIST_MAPREGION:
            {
                osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;

                if (osStatus < 0) {
                    status = DSP_EFAIL ;
                    SET_FAILURE_REASON ;
                }
                else {
                    /* mmap the region in user space */
                    MPLIST_MemInfo * mapInfo = (MPLIST_MemInfo *)
                                  &(args->apiArgs.mplistArgs.mplistRegionArgs) ;
                    Uint32 userAddr ;
                    Uint32 addr ;
                    Uint32 size ;

                    size = mapInfo->size ;
                    addr = mapInfo->physAddr ;
                    /** --------------------------------------------------------
                     *  Align the physical address to page boundary
                     *  --------------------------------------------------------
                     */
                    size = size + (addr % drvObj->pageSize) ;
                    addr = addr - (addr % drvObj->pageSize) ;

                    userAddr = (Uint32) mmap (
                                 NULL,
                                 size,
                                 PROT_READ | PROT_WRITE,
                                 MAP_SHARED,
                                 drvObj->driverHandle,
                                 (off_t) addr) ;

                    if (userAddr == (Uint32) MAP_FAILED) {
                        TRC_0PRINT (
                                TRC_LEVEL7,
                                "Couldn't map DSP memory"
                                " in user space\n") ;
                        status = DSP_EFAIL ;
                        SET_FAILURE_REASON ;
                    }
                    else {
                        /** ----------------------------------------------------
                         *  change the user address to reflect the actual user
                         *  address of memory block mapped. This is done since
                         *  during mmap memory block was shifted(+-) so that it
                         *  is aligned to page boundary.
                         *  ----------------------------------------------------
                         */
                        mapInfo->userAddr =  userAddr
                                           + (mapInfo->physAddr % drvObj->pageSize) ;
                    }
                }
            }
            break ;

        case CMD_MPLIST_UNMAPREGION:
            {
                /* munmap the region in user space */
                MPLIST_MemInfo * unmapInfo =
                (MPLIST_MemInfo *) &(args->apiArgs.mplistArgs.mplistRegionArgs) ;
                Uint32 addr = unmapInfo->userAddr ;
                Uint32 size = unmapInfo->size ;

                /** --------------------------------------------------------
                 *  Get the actual user address and size. Since these are
                 *  modified at the time of mmaping, to have memory block
                 *  page boundary aligned.
                 *  --------------------------------------------------------
                 */
                size = size + (addr % drvObj->pageSize) ;
                addr = addr - (addr % drvObj->pageSize) ;
                munmap ((Void *)addr, size) ;
                args->apiStatus = DSP_SOK ;
            }
            break ;
#endif /* if defined (MPLIST_COMPONENT) */

      case CMD_PROC_SETUP:
      {
        /* Install cleanup routines */
        DRV_installCleanupRoutines(
          args->apiArgs.procSetupArgs.linkCfg);

        osStatus = ioctl (drvObj->driverHandle, cmdId, args);

        TRC_1PRINT(TRC_LEVEL4, "osStatus: %x\n", osStatus);

        if (osStatus < 0) {
          status = DSP_EFAIL;
          SET_FAILURE_REASON;
        }

#if defined (POOL_COMPONENT)
        else {
          _POOL_init();
        }
#endif /* if defined (POOL_COMPONENT) */

        break;
      }

        case CMD_PROC_DESTROY:
            {
#if defined (POOL_COMPONENT)
                _POOL_exit () ;
#endif /* if defined (POOL_COMPONENT) */

                osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;

                if (osStatus < 0) {
                    status = DSP_EFAIL ;
                    SET_FAILURE_REASON ;
                }
            }
            break ;

      case CMD_PROC_ATTACH:
      {
        if (DRV_handle == NULL) {
          status = DRV_Initialize(&DRV_handle, NULL);

          if (DSP_SUCCEEDED (status)) {
            /* Install cleanup routines. This is needed for the case in
               in multi-application case where app has not called
               PROC_setup and has directly called PROC_attach */
            DRV_installCleanupRoutines (PROC_linkCfgPtr) ;
          }
          else {
            SET_FAILURE_REASON;
          }
        }

        if (DSP_SUCCEEDED(status)) {
          osStatus = ioctl(DRV_handle->driverHandle, cmdId, args);

          if (osStatus < 0) {
            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }
        }

        break;
      }

        case CMD_PROC_DETACH:
            {
                if (drvObj == NULL) {
                    status = DSP_EATTACHED ;
                    SET_FAILURE_REASON ;
                }
                else {
                    osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;
                    if (osStatus < 0) {
                        status = DSP_EFAIL ;
                        SET_FAILURE_REASON ;
                    }
                }
            }
            break ;

        case CMD_PROC_CONTROL:
            {
                Uint32 addr ;
                Uint32 size ;

                osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;
                if (osStatus < 0) {
                    status = DSP_EFAIL ;
                    SET_FAILURE_REASON ;
                }
                else {
                    switch (args->apiArgs.procControlArgs.cmd)
                    {
                        case PROC_CTRL_CMD_MAP_DSPMEM:
                            {
                                ProcMemMapInfo * mapInfo =
                                    (ProcMemMapInfo *)
                                        args->apiArgs.procControlArgs.arg ;
                                Uint32 userAddr ;

                                addr = mapInfo->mappedAddr ;
                                size = mapInfo->mappedSize ;
                                /** --------------------------------------------
                                 *  Align the physical address to page boundary
                                 *  --------------------------------------------
                                 */
                                size = size + (addr % drvObj->pageSize) ;
                                addr = addr - (addr % drvObj->pageSize) ;

                                userAddr = (Uint32) mmap (
                                             NULL,
                                             size,
                                             PROT_READ | PROT_WRITE,
                                             MAP_SHARED,
                                             drvObj->driverHandle,
                                             (off_t) addr) ;

                                if (userAddr == (Uint32) MAP_FAILED) {
                                    TRC_0PRINT (
                                            TRC_LEVEL7,
                                            "Couldn't map DSP memory"
                                            " in user space\n") ;
                                    status = DSP_EFAIL ;
                                    SET_FAILURE_REASON ;
                                }
                                else {
                                    userAddr =   userAddr
                                              +  (  mapInfo->mappedAddr
                                                  % drvObj->pageSize) ;
                                    mapInfo->mappedAddr = userAddr ;
                                }
                            }
                            break ;

                        case PROC_CTRL_CMD_UNMAP_DSPMEM:
                            {
                                ProcMemMapInfo * mapInfo =
                                    (ProcMemMapInfo *)
                                        args->apiArgs.procControlArgs.arg ;
                                addr = mapInfo->mappedAddr ;
                                size = mapInfo->mappedSize ;
                                size = size + (addr % drvObj->pageSize) ;
                                addr = addr - (addr % drvObj->pageSize) ;

                                munmap ((Void *) addr, size) ;
                            }
                            break ;

                        default:
                            /* do nothing */
                            break ;
                    }
                }
            }
            break ;

        case CMD_PROC_SENDTERMEVT:
            {
                if (DRV_handle == NULL) {
                    status = DSP_EFAIL;
                    SET_FAILURE_REASON;
                }

                if (DSP_SUCCEEDED(status)) {
                    osStatus = ioctl(DRV_handle->driverHandle, cmdId, args);
                    if (osStatus < 0) {
                        status = DSP_EFAIL;
                        SET_FAILURE_REASON;
                    }
                }
            }
            break ;

#if defined (POOL_COMPONENT)
        case CMD_POOL_ALLOC:
            {
                osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;
                if (osStatus < 0) {
                    status = DSP_EFAIL ;
                    SET_FAILURE_REASON ;
                }
                else if (DSP_SUCCEEDED (args->apiStatus)) {
                    status = _POOL_xltBuf (args->apiArgs.poolAllocArgs.poolId,
                                           args->apiArgs.poolAllocArgs.bufPtr,
                                           KNL_TO_USR) ;
                    if (DSP_FAILED (status)) {
                        SET_FAILURE_REASON ;
                    }
                }
            }
            break ;

        case CMD_POOL_FREE:
            {
                status = _POOL_xltBuf (args->apiArgs.poolFreeArgs.poolId,
                                       &args->apiArgs.poolFreeArgs.bufPtr,
                                       USR_TO_KNL) ;
                if (DSP_SUCCEEDED (status)) {
                    osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;
                    if (osStatus < 0) {
                        status = DSP_EFAIL ;
                        SET_FAILURE_REASON ;
                    }
                }
            }
            break ;

        case CMD_POOL_TRANSLATEADDR:
            {
                POOL_AddrXltFlag xltFlag ;

                args->apiStatus = DSP_SOK ;

                xltFlag =   args->apiArgs.poolTranslateAddrArgs.srcAddrType
                      | (args->apiArgs.poolTranslateAddrArgs.dstAddrType << 8) ;
                *(args->apiArgs.poolTranslateAddrArgs.dstAddr) =
                                   args->apiArgs.poolTranslateAddrArgs.srcAddr ;
                status = _POOL_xltBuf (
                                     args->apiArgs.poolTranslateAddrArgs.poolId,
                                     args->apiArgs.poolTranslateAddrArgs.dstAddr,
                                     xltFlag) ;

                if (DSP_SUCCEEDED (status)) {
                  if (*(args->apiArgs.poolTranslateAddrArgs.dstAddr) == NULL)
                  {
                     status = DSP_ENOTFOUND;
                     SET_FAILURE_REASON;
                  }
                }
                else {
                    SET_FAILURE_REASON ;
                }
            }
            break ;

      case CMD_POOL_OPEN:
      {
        POOL_OpenParams *retParams;
        Uint32 addr;
        Uint32 size;
        Uint32 userAddr;
        Uint8 poolNo;
        ProcessorId procId;
        POOL_AddrInfo *poolAddrPtr;

        /* trigger 'ioctl' which goes to DRV_Ioctl which subsequently calls
           'LDRV_POOL_open'. NOTE, that despite of 'args' being declared as
           'in' we expect the data to be (partially) updated by subsequent
           calls (e.g. 'SMAPOOL_open', 'LDRV_POOL_open', etc.) */
        osStatus = ioctl(drvObj->driverHandle, cmdId, args);

        if ((osStatus < 0) || (DSP_FAILED(args->apiStatus))) {
          if (osStatus < 0) {
            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }
        }
        else {
          /* Now acquire the POOL address data set-up by 'SMAPOOL_open' and
	     'LDRV_POOL_open' */
          retParams = args->apiArgs.poolOpenArgs.params;

          /* Align the physical address to page boundary */
          size = retParams->size +
                 (retParams->physAddr % drvObj->pageSize);

          addr = retParams->physAddr -
                 (retParams->physAddr % drvObj->pageSize);

          userAddr = (Uint32) mmap(NULL,
                                   size,
                                   PROT_READ | PROT_WRITE,
                                   MAP_SHARED,
                                   drvObj->driverHandle,
                                   addr);

          if (userAddr == (Uint32) MAP_FAILED) {
            TRC_1PRINT(TRC_LEVEL7, "*** error in 's': 'mmap' failed\n",
                                   __FUNCTION__);

            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }
          else {
            /* change the user address to reflect the actual user address of
               memory block mapped. This is done since during 'mmap' the
               memory block was shifted(+-) so that it is aligned to the page
               boundary */
            userAddr = userAddr + (retParams->physAddr % drvObj->pageSize);

            /* Get the proc Number for the processor */
            procId = POOL_getProcId(args->apiArgs.poolOpenArgs.poolId);

            /* Get the pool Number on the processor */
            poolNo = POOL_getPoolNo(args->apiArgs.poolOpenArgs.poolId);

            /* update the pool information */
            poolAddrPtr = &POOL_addrConfig[procId][poolNo];
            poolAddrPtr->addr[AddrType_Usr] = userAddr;
            poolAddrPtr->addr[AddrType_Phy] = retParams->physAddr;
            poolAddrPtr->addr[AddrType_Knl] = retParams->virtAddr;
            poolAddrPtr->addr[AddrType_Dsp] = retParams->dspAddr;
            poolAddrPtr->size = retParams->size;
            poolAddrPtr->isInit = TRUE;
          }
        }

        break;
      }

        case CMD_POOL_CLOSE:
            {
                Uint32   addr ;
                Uint32   size ;
                Uint8            poolNo ;
                ProcessorId      procId ;
                POOL_AddrInfo *  poolAddrPtr ;

                /* Get the proc Number for the processor */
                procId = POOL_getProcId (args->apiArgs.poolOpenArgs.poolId) ;
                /* Get the pool Number on the processor */
                poolNo = POOL_getPoolNo (args->apiArgs.poolOpenArgs.poolId) ;

                poolAddrPtr = &POOL_addrConfig [procId][poolNo] ;

                /* Check if pool was opened */
                if (poolAddrPtr->addr [AddrType_Usr] ==  (Uint32) NULL) {
                    status = DSP_EINVALIDARG ;
                }
                else {
                    addr = poolAddrPtr->addr [AddrType_Usr] ;
                    size = poolAddrPtr->size ;

                    /** --------------------------------------------------------
                     *  Get the actual user address and size. Since these are
                     *  modified at the time of mmaping, to have memory block
                     *  page boundary aligned.
                     *  --------------------------------------------------------
                     */
                    size = size + (addr % drvObj->pageSize) ;
                    addr = addr - (addr % drvObj->pageSize) ;

                    /** --------------------------------------------------------
                     *  Unmap the memory block from user address space.
                     *  --------------------------------------------------------
                     */
                    munmap ((Void *) addr, size) ;

                    /** --------------------------------------------------------
                     *  Call the POOL CLOSE ioctl function.
                     *  --------------------------------------------------------
                     */
                    osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;
                    if (osStatus < 0) {
                        status = DSP_EFAIL ;
                        SET_FAILURE_REASON ;
                    }
                    else {
                        poolAddrPtr->addr [AddrType_Usr] = (Uint32) NULL ;
                        poolAddrPtr->addr [AddrType_Phy] = (Uint32) NULL ;
                        poolAddrPtr->addr [AddrType_Knl] = (Uint32) NULL ;
                        poolAddrPtr->addr [AddrType_Dsp] = (Uint32) NULL ;
                        poolAddrPtr->size                = (Uint32) -1u ;
                        poolAddrPtr->isInit              = FALSE ;
                    }
                }
            }
            break ;

        case CMD_POOL_WRITEBACK:
            {
                _POOL_xltBuf (args->apiArgs.poolFreeArgs.poolId,
                              &args->apiArgs.poolFreeArgs.bufPtr,
                              USR_TO_KNL) ;
                osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;
                if (osStatus < 0) {
                    status = DSP_EFAIL ;
                    SET_FAILURE_REASON ;
                }
            }
            break ;

        case CMD_POOL_INVALIDATE:
            {
                _POOL_xltBuf (args->apiArgs.poolFreeArgs.poolId,
                              &args->apiArgs.poolFreeArgs.bufPtr,
                              USR_TO_KNL) ;
                osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;
                if (osStatus < 0) {
                    status = DSP_EFAIL ;
                    SET_FAILURE_REASON ;
                }
            }
            break ;

#endif /* if defined (POOL_COMPONENT) */

#if defined (MPCS_COMPONENT)
        case CMD_MPCS_MAPREGION:
            {
                osStatus = ioctl (drvObj->driverHandle, cmdId, args) ;

                if (osStatus < 0) {
                    status = DSP_EFAIL ;
                    SET_FAILURE_REASON ;
                }
                else {
                    /* mmap the region in user space */
                    MPCS_MemInfo * mapInfo = (MPCS_MemInfo *)
                                  &(args->apiArgs.mpcsMapArgs.mpcsRegionArgs) ;
                    Uint32 userAddr ;
                    Uint32 addr ;
                    Uint32 size ;

                    size = mapInfo->size ;
                    addr = mapInfo->physAddr ;
                    /** --------------------------------------------------------
                     *  Align the physical address to page boundary
                     *  --------------------------------------------------------
                     */
                    size = size + (addr % drvObj->pageSize) ;
                    addr = addr - (addr % drvObj->pageSize) ;

                    userAddr = (Uint32) mmap (
                                 NULL,
                                 size,
                                 PROT_READ | PROT_WRITE,
                                 MAP_SHARED,
                                 drvObj->driverHandle,
                                 (off_t) addr) ;

                    if (userAddr == (Uint32) MAP_FAILED) {
                        TRC_0PRINT (
                                TRC_LEVEL7,
                                "Couldn't map DSP memory"
                                " in user space\n") ;
                        status = DSP_EFAIL ;
                        SET_FAILURE_REASON ;
                    }
                    else {
                        /** ----------------------------------------------------
                         *  change the user address to reflect the actual user
                         *  address of memory block mapped. This is done since
                         *  during mmap memory block was shifted(+-) so that it
                         *  is aligned to page boundary.
                         *  ----------------------------------------------------
                         */
                        mapInfo->userAddr =  userAddr
                                           + (mapInfo->physAddr % drvObj->pageSize) ;
                    }
                }
            }
            break ;

        case CMD_MPCS_UNMAPREGION:
            {
                /* munmap the region in user space */
                MPCS_MemInfo * unmapInfo = (MPCS_MemInfo *)
                                &(args->apiArgs.mpcsMapArgs.mpcsRegionArgs) ;
                Uint32 addr = unmapInfo->userAddr ;
                Uint32 size = unmapInfo->size ;

                /** ------------------------------------------------------------
                 *  Get the actual user address and size. Since these are
                 *  modified at the time of mmaping, to have memory block
                 *  page boundary aligned.
                 *  ------------------------------------------------------------
                 */
                size = size + (addr % drvObj->pageSize) ;
                addr = addr - (addr % drvObj->pageSize) ;
                munmap ((Void *)addr, size) ;
                args->apiStatus = DSP_SOK ;
            }
            break ;
#endif /* if defined (MPCS_COMPONENT) */

#if defined (NOTIFY_COMPONENT)
        case CMD_NOTIFY_NOTIFY:
        {
          osStatus = ioctl (drvObj->driverHandle, cmdId, args);

          if (osStatus < 0) {
            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }
        }

        break;
#endif /* #if defined (NOTIFY_COMPONENT) */

        default:
        {
          osStatus = ioctl(drvObj->driverHandle, cmdId, args);

          if (osStatus < 0) {
            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }
        }

        break;
      }

    /* Return API's status if ioctl is successful */
    if (DSP_SUCCEEDED (status)) {
      status = args->apiStatus;
    }
  }
  else {
    status = DSP_EATTACHED;
    SET_FAILURE_REASON;
  }

  TRC_3PRINT(TRC_LEVEL4, "processed %s in '%s', status 0x%x\n",
                         getCmdString(cmdId), __FUNCTION__, status);

  TRC_1LEAVE("DRV_Invoke", status);
  return status;
}

/*******************************************************************************
  @name  DRV_ProtectInit
  @desc  This function initailizes driver protection mechanism between
         multiple processes. This API can be called by multiple processes,
         and will create the semaphore if it does not exist
*******************************************************************************/

NORMAL_API DSP_STATUS DRV_ProtectInit(IN DRV_Object * drvObj)
{
  DSP_STATUS status = DSP_SOK;
  key_t key;

  TRC_1ENTER("DRV_ProtectInit", drvObj);

  DBC_Require(drvObj != NULL);
  DBC_Require(IS_OBJECT_VALID(drvObj, SIGN_DRV));

  if (IS_OBJECT_VALID(drvObj, SIGN_DRV)) {
    /* Generate the unique key */
    key = ftok(LINK_DRIVER_NAME, DRV_KEY_CS);

    if (key == OS_EFAILURE) {
      status = DSP_EFAIL;
      SET_FAILURE_REASON;
    }
    else {
      /* Create a semaphore set based on the unique key. A set will be
         created if it does not exist for this key.

         protection osCsId etc. cannot be placed in drvObj since it is
         destroyed after PROC_detach and recreated in PROC_setup */
      DRV_protectObj.osCsId = semget(key,
                                     MAX_DRV_CS,
                                     0666 | IPC_CREAT | IPC_EXCL);
 
      if (DRV_protectObj.osCsId == OS_EFAILURE) {
        if (errno == EEXIST) {
          DRV_protectObj.osCsId = semget (key, 0, 0);
          DRV_protectObj.csEntered = FALSE;
        }
        else {
          status = DSP_EFAIL;
          SET_FAILURE_REASON;
        }
      }
      else {
        /* Initialize the semaphores as initially available */
        if (semctl(DRV_protectObj.osCsId,
                   0,
                   SETVAL,
                   INIT_RESOURCE_COUNT) ==  OS_EFAILURE)
        {
          status = DSP_EFAIL;
          SET_FAILURE_REASON;
        }
      }
    }
  }
  else {
    status = DSP_EPOINTER;
    SET_FAILURE_REASON;
  }

  TRC_1LEAVE("DRV_ProtectInit", status);
  return status;
}

/*******************************************************************************
  @name  DRV_ProtectExit
  @desc  This function finalizes driver protection mechanism between
         multiple processes. This function must be called only by the
         last exiting process
*******************************************************************************/

NORMAL_API DSP_STATUS DRV_ProtectExit(IN DRV_Object * drvObj)
{
  DSP_STATUS status = DSP_SOK;

  TRC_1ENTER("DRV_ProtectExit", drvObj);

  DBC_Require(drvObj != NULL);
  DBC_Require(IS_OBJECT_VALID(drvObj, SIGN_DRV));

  if (IS_OBJECT_VALID(drvObj, SIGN_DRV)) {
    /* Delete the semaphore set */
    if (semctl(DRV_protectObj.osCsId, 0, IPC_RMID, 0) == OS_EFAILURE) {
      status = DSP_EFAIL;
      SET_FAILURE_REASON;
    }
  }
  else {
    status = DSP_EPOINTER;
    SET_FAILURE_REASON;
  }

  TRC_1LEAVE("DRV_ProtectExit", status);
  return status;
}

/*******************************************************************************
  @name  DRV_ProtectEnter
  @desc  This function enters driver protection between multiple processes
*******************************************************************************/

NORMAL_API DSP_STATUS DRV_ProtectEnter(IN DRV_Object * drvObj)
{
  DSP_STATUS status = DSP_SOK;
  struct sembuf sb  = { 0, SEMOP_ALLOC_ONE_RESOURCE, 0 };

  TRC_1ENTER("DRV_ProtectEnter", drvObj);

  DBC_Require(drvObj != NULL);
  DBC_Require(IS_OBJECT_VALID (drvObj, SIGN_DRV));

  if (IS_OBJECT_VALID (drvObj, SIGN_DRV)) {
    if (DSPLINK_isSignal == FALSE) {

      /* Wait on the semaphore */
      sb.sem_num = 0;

      do {
        status = DSP_SOK;

        if (semop(DRV_protectObj.osCsId, &sb, 1) == OS_EFAILURE) {
          if (errno == EINTR) {
            /* If interrupted by a signal, wait again */
            status = DSP_EINTR;
          }
          else {
            status = DSP_EFAIL;
            SET_FAILURE_REASON;
          }
        }
      } while (status == DSP_EINTR);

      DRV_protectObj.csEntered = TRUE;
    }
  }
  else {
    status = DSP_EPOINTER;
    SET_FAILURE_REASON;
  }

  TRC_1LEAVE("DRV_ProtectEnter", status);
  return status;
}

/*******************************************************************************
  @name  DRV_ProtectLeave
  @desc  This function leaves driver protection between multiple processes
*******************************************************************************/

NORMAL_API DSP_STATUS DRV_ProtectLeave(IN DRV_Object * drvObj)
{
  DSP_STATUS status = DSP_SOK;
  struct sembuf sb  = {0, SEMOP_FREE_ONE_RESOURCE, 0};
  Bool enteredCs = TRUE;

  TRC_1ENTER("DRV_ProtectLeave", drvObj);

  DBC_Require(drvObj != NULL);
  DBC_Require(IS_OBJECT_VALID (drvObj, SIGN_DRV));

  if (IS_OBJECT_VALID(drvObj, SIGN_DRV)) {
    if (DSPLINK_isSignal == TRUE) {
      if (DRV_protectObj.csEntered == FALSE) {
        enteredCs = FALSE;
      }
    }

    /* Release the semaphore */
    if (enteredCs == TRUE) {
      /* Release the semaphore */
      sb.sem_num = 0 ;

      if (semop(DRV_protectObj.osCsId, &sb, 1) == OS_EFAILURE) {
        status = DSP_EFAIL;
        SET_FAILURE_REASON;
      }

      DRV_protectObj.csEntered = FALSE;
    }
  }
  else {
    status = DSP_EPOINTER;
    SET_FAILURE_REASON;
  }

  TRC_1LEAVE("DRV_ProtectLeave", status);
  return status;
}

/*******************************************************************************
  @name  DRV_installCleanupRoutines
  @desc  Install signal handler and atexit handler for cleanup
*******************************************************************************/

static void DRV_installCleanupRoutines(IN LINKCFG_Object *linkCfgPtr)
{
  struct sigaction sigInstaller;
  Uint32 i;
  sigset_t block_mask;

  TRC_1ENTER("DRV_installCleanupRoutines", linkCfgPtr);

  if (linkCfgPtr->gppObject->gppOsObject->handleSignals == TRUE) {
    sigemptyset(&block_mask);
    sigfillset(&block_mask);
    sigInstaller.sa_flags = (SA_RESTART);
    sigInstaller.sa_mask = block_mask;
    sigInstaller.sa_handler = &DSPLINK_sigHandler;

    for (i = 0; i < linkCfgPtr->gppObject->gppOsObject->numSignals; i++)
    {
      sigaction(linkCfgPtr->gppObject->gppOsObject->sigNumArray[i],
                &sigInstaller,
                NULL);
    }
  }

  atexit(&DSPLINK_atExitHandler);

  TRC_0LEAVE("DRV_installCleanupRoutines");
}

/*******************************************************************************
  @name  DSPLINK_atExitHandler
  @desc  'atexit' handler for DSP/BIOS LINK. This ensures that the system
         is left in a correct state even if application does not perform
         the required shutdown operations
*******************************************************************************/

STATIC Void DSPLINK_atExitHandler(Void)
{
  int osStatus = 0;
  CMD_Args args;

  /* NOTE, hardcoded for now */
  Uint32 procId = 0;

#if defined (POOL_COMPONENT)
  Uint32 i;
#endif

  TRC_0ENTER ("DSPLINK_atExitHandler") ;

  /* skip handler if already invoked by signal handler */
  if (DSPLINK_skipExitHandler) goto leave;

  TRC_0PRINT (TRC_LEVEL7,
    "=====================================================================\n"
    "IMPORTANT: There may be several error prints in the atExit handler.  \n"
    "           These occur because DSPLink tries to clean up resources.  \n"
    "           If resources are already freed, it will cause errors.     \n"
    "           THESE ERRORS CAN BE SAFELY IGNORED.                       \n"
    "=====================================================================\n");

  /* Set the flag to TRUE to indicating signal */
  DSPLINK_isSignal = TRUE;

#if defined (MSGQ_COMPONENT)
  MSGQ_transportClose(procId);
#endif

#if DSPLINK_TERMINATE_EVT != (-1)
  /* if dsp still running, send terminate event */
  {
    PROC_State procState;
    PROC_getState(procId, &procState);

    if (procState == ProcState_Started) {
      PROC_sendTerminateEvent(procId);
    }
    else {
      PROC_stop(procId);
    }
  }
#else
  PROC_stop(procId);
#endif

  if (DRV_handle != NULL) {
    osStatus = ioctl(DRV_handle->driverHandle, CMD_PROC_CLEANUP, &args);

    if (osStatus < 0) {
      TRC_0PRINT(TRC_LEVEL7,
                "!!! Could not cleanup the kernel driver. "
                "Please restart the system...\n") ;
    }
  }

#if defined (POOL_COMPONENT)
  for (i = 0; i < MAX_POOLENTRIES; i++) {
    POOL_close(i);
  }
#endif

  PROC_detach(procId);
  PROC_destroy();

  /* Reset the DSPLINK_isSignal flag */
  DSPLINK_isSignal = FALSE;

leave:
  TRC_0LEAVE("DSPLINK_atExitHandler");
  return;
}

/*******************************************************************************
  @name  DSPLINK_sigHandler
  @desc  Signal handler for incorrect behavior of user applications that may
         result in DSP/BIOS Link being left in an unusable state.
         This is a Linux specific implementation and equivalent
         implementation may not available on other operating systems
*******************************************************************************/

static void DSPLINK_sigHandler(int sigNum)
{
  TRC_1ENTER("DSPLINK_sigHandler", sigNum);

  /* Set the flag to TRUE to indicating signal */
  DSPLINK_isSignal = TRUE;

  /* It is necessary to call the cleanup function from the signal handler
     context to ensure that the cleanup is not interrupted by another
     signal. Just exit (0) is not enough  as the at exit handler can be
     pre-empted by a signal */
  DSPLINK_atExitHandler();
  DSPLINK_skipExitHandler = TRUE;

  /*  Force hard stop on the process  */
  exit(0);

  TRC_0LEAVE("DSPLINK_sigHandler");
  return;
}

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
