/** ============================================================================
 *  @file   drv_pmgr.c
 *
 *  @path   $(DSPLINK)/gpp/src/pmgr/Linux/2.6.18/
 *
 *  @desc   Implementation of linux module driver interface.
 *
 *  @ver    1.65.02.09
 *  ============================================================================
 *  Copyright (C) 2002-2012, Texas Instruments Incorporated - http://www.ti.com/
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation version 2.
 *  
 *  This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 *  whether express or implied; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *  ============================================================================
 */


/*  Defined to include MACROS EXPORT_SYMBOL. This must be done before including
 *  module.h
 */
#if !defined (EXPORT_SYMTAB)
#define EXPORT_SYMTAB
#endif

/*  ----------------------------------- OS Specific Headers         */
#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26)
#include <linux/device.h>
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,33)
#include <generated/autoconf.h>
#else
#include <linux/autoconf.h>
#endif
#include <linux/spinlock.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/mm.h>

/* NKim, changed for the kernel in mind, i.e. 4.19 */
/* #include <asm/uaccess.h> */
#include <linux/uaccess.h>

#include <linux/pid.h>
#include <asm/io.h>

/*  ----------------------------------- DSP/BIOS Link               */
#include <dsplink.h>
#include <_dsplink.h>
#include <procdefs.h>
#include <version.h>
#include <terminate.h>

#if defined (RINGIO_COMPONENT)
#include <ringiodefs.h>
#endif /* if defined (RINGIO_COMPONENT) */
#if defined (MPLIST_COMPONENT)
#include <mplistdefs.h>
#endif /* if defined (MPLIST_COMPONENT) */
#if defined (MSGQ_COMPONENT)
#include <msgqdefs.h>
#endif /* if defined (MSGQ_COMPONENT) */
#if defined (CHNL_COMPONENT)
#include <chnldefs.h>
#endif /* if defined (CHNL_COMPONENT) */

/*  ----------------------------------- Profiling                   */
#if defined (DDSP_PROFILE)
#include <profile.h>
#endif /* if defined (DDSP_PROFILE) */

/*  ----------------------------------- Trace & Debug               */
#include <_trace.h>
#include <trc.h>
#include <print.h>

/*  ----------------------------------- Generic Functions           */

#include <list.h>
#include <idm.h>

/*  ----------------------------------- OSAL Headers                */
#include <osal.h>
#include <mem.h>
#include <mem_os.h>
#include <prcs.h>
#if defined (NOTIFY_COMPONENT)
#include <notify_knl.h>
#endif /* #if defined (NOTIFY_COMPONENT) */

/*  ----------------------------------- User API                    */
#if defined (MPCS_COMPONENT)
#include <mpcs.h>
#endif /* if defined (MPCS_COMPONENT) */

/*  ----------------------------------- Processor Manager           */
#include <drvdefs.h>
#include <pmgr_proc.h>
#if defined (CHNL_COMPONENT)
#include <pmgr_chnl.h>
#endif /* if defined (CHNL_COMPONENT) */
#if defined (MSGQ_COMPONENT)
#include <pmgr_msgq.h>
#endif /* if defined (MSGQ_COMPONENT) */

/*  ----------------------------------- Link Driver                 */
#if defined (CHNL_COMPONENT)
#include <ldrv_data.h>
#include <ldrv_chnl.h>
#endif /* if defined (CHNL_COMPONENT) */
#if defined (RINGIO_COMPONENT)
#include <ldrv_ringio.h>
#endif /* if defined (RINGIO_COMPONENT) */
#if defined (MPLIST_COMPONENT)
#include <ldrv_mplist.h>
#endif /* if defined (MPLIST_COMPONENT) */
#if defined (POOL_COMPONENT)
#include <ldrv_pool.h>
#endif /* if defined (POOL_COMPONENT) */
#if defined (MPCS_COMPONENT)
#include <ldrv_mpcs.h>
#endif /* if defined (MPCS_COMPONENT) */
#include <ldrv.h>
#include <ldrv_proc.h>
#if defined (MSGQ_COMPONENT)
#include <ldrv_mqt.h>
#include <ldrv_msgq.h>
#endif /* if defined (MSGQ_COMPONENT) */
#if !(defined (ONLY_PROC_COMPONENT))
#include <ips.h>
#endif

/*  ----------------------------------- LOG  Headers                 */
#if defined (LOG_COMPONENT)
#include <linklog.h>
#endif /* if defined (LOG_COMPONENT) */


EXPORT_SYMBOL(LDRV_PROC_getState);
EXPORT_SYMBOL(LDRV_PROC_setState);
EXPORT_SYMBOL(PMGR_PROC_getSymbolAddress);
EXPORT_SYMBOL(DSPLINK_sendTerminateEvent);
#if !(defined (ONLY_PROC_COMPONENT))
EXPORT_SYMBOL(IPS_register);
EXPORT_SYMBOL(IPS_notify);
EXPORT_SYMBOL(IPS_unregister);
#endif


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
 *  @macro  SET_FAILURE_REASON
 *
 *  @desc   Sets failure reason.
 *  ============================================================================
 */
#if defined (DDSP_DEBUG)
#define SET_FAILURE_REASON TRC_SetReason (status, FID_C_OSAL_DRV_PMGR, __LINE__)
#else
#define SET_FAILURE_REASON
#endif /* if defined (DDSP_DEBUG) */


/** ----------------------------------------------------------------------------
 *  @name   major
 *
 *  @desc   Major number of driver.
 *  ----------------------------------------------------------------------------
 */
STATIC Int32 major = 230 ;

/** ----------------------------------------------------------------------------
 *  @name   DRV_dspId
 *
 *  @desc   Local snoop value of the dsp id.
 *  ----------------------------------------------------------------------------
 */
STATIC unsigned long DRV_dspId = 0xffff;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26)
/** ----------------------------------------------------------------------------
 *  @name   dsplink_class
 *
 *  @desc   class struct for device create.
 *  ----------------------------------------------------------------------------
 */
STATIC struct class *dsplink_class;
#endif

/** ----------------------------------------------------------------------------
 *  @name   DRV_IsInitialized
 *
 *  @desc   If the module has been initialized or not.
 *  ----------------------------------------------------------------------------
 */
STATIC Bool DRV_IsInitialized = FALSE ;

/** ============================================================================
 *  @name   LDRV_LinkCfgPtr
 *
 *  @desc   Global pointer containing DSPLINK configuration information for the
 *          driver.
 *  ============================================================================
 */
extern LINKCFG_Object * LDRV_LinkCfgPtr ;


#if defined (MSGQ_COMPONENT)
/** ----------------------------------------------------------------------------
 *  @name   DRV_MaxMsgqs
 *
 *  @desc   Maximum number of message queues on the GPP.
 *  ----------------------------------------------------------------------------
 */
STATIC Uint32 DRV_MaxMsgqs = 0 ;
#endif /* if defined (CHNL_COMPONENT) */

#if defined (CHNL_COMPONENT)
/** ----------------------------------------------------------------------------
 *  @name   DRV_MemAllocAttrs
 *
 *  @desc   Allocation arguments for CHNL ID to POOL ID Map table allocation.
 *          These are filled up by alloc function and used by free function.
 *  ----------------------------------------------------------------------------
 */
STATIC MemAllocAttrs   DRV_MemAllocAttrs ;

/** ----------------------------------------------------------------------------
 *  @name   DRV_ChnlIdToPoolId
 *
 *  @desc   Place holder to store pool ids for all channels.
 *  ----------------------------------------------------------------------------
 */
STATIC Uint32 (*DRV_ChnlIdToPoolId) [MAX_CHANNELS] ;
#endif /* if defined (CHNL_COMPONENT) */


/** ----------------------------------------------------------------------------
 *  @name   DRV_CallAPI
 *
 *  @desc   Function to invoke the APIs through ioctl.
 *
 *  @arg    cmd
 *              Command identifier.
 *          args
 *              Arguments to be passed for the command.
 *
 *  @ret    DSP_SOK
 *              Operation successfully completed.
 *          DSP_EFAIL
 *              Operation failed.
 *
 *  @enter  None.
 *
 *  @leave  None.
 *
 *  @see    None.
 *  ----------------------------------------------------------------------------
 */
STATIC
NORMAL_API
DSP_STATUS
DRV_CallAPI (Uint32 cmd, CMD_Args * args) ;


/** ----------------------------------------------------------------------------
 *  @func  DSPLINK_Cleanup
 *
 *  @desc  Kernel side component of the cleanup utility.
 *
 *  @arg    None
 *
 *  @ret    None
 *
 *  @enter  None.
 *
 *  @leave  None.
 *
 *  @see    None.
 *  ----------------------------------------------------------------------------
 */
STATIC
NORMAL_API
Void
DSPLINK_Cleanup (Void) ;


/** ----------------------------------------------------------------------------
 *  @name   DRV_Open
 *
 *  @desc   Linux driver function to open the driver object.
 *
 *  @arg    inode
 *              inode pointer.
 *          filp
 *              File structure pointer.
 *
 *  @ret    0
 *              Success.
 *          non-zero
 *              Failure.
 *
 *  @enter  None.
 *
 *  @leave  None.
 *
 *  @see    None.

 *  ----------------------------------------------------------------------------
 */
STATIC
NORMAL_API
int
DRV_Open    (struct inode * inode, struct file * filp) ;


/** ----------------------------------------------------------------------------
 *  @func   DRV_Flush
 *
 *  @desc   Flush function for Linux LINK driver.
 *
 *  @arg    filp
 *              file pointer.
 *          id
 *               id (ignored)
 *  @ret    0
 *              Operation successfully completed.
 *          non-zero
 *              failure occured.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ----------------------------------------------------------------------------
 */
STATIC
NORMAL_API
int
DRV_Flush (struct file * filp, fl_owner_t id);

/** ----------------------------------------------------------------------------
 *  @func   DRV_Release
 *
 *  @desc   Release function for Linux LINK driver.
 *
 *  @arg    inode
 *              inode pointer.
 *          filp
 *              File structure pointer.
 *
 *  @ret    0
 *              Operation successfully completed.
 *          non-zero
 *              failure occured.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ----------------------------------------------------------------------------
 */
STATIC
NORMAL_API
int
DRV_Release (struct inode * inode, struct file * filp) ;


/** ----------------------------------------------------------------------------
 *  @func   DRV_Ioctl
 *
 *  @desc   ioctl function for of Linux LINK driver.
 *
 *  @arg    inode
 *              inode pointer.
 *  @arg    filp
 *              file pointer.
 *  @arg    cmd
 *              IOCTL command id.
 *  @arg    args
 *              arguments for the command.
 *
 *  @ret    0
 *              Operation successfully completed.
 *          non-zero
 *              failure occured.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ----------------------------------------------------------------------------
 */
STATIC
long
DRV_Ioctl (struct file * filp, unsigned int cmd, unsigned long args) ;


/** ----------------------------------------------------------------------------
 *  @func   DRV_Mmap
 *
 *  @desc   mmap function for LINK Linux driver.
 *
 *  @arg    filp
 *              file pointer.
 *  @arg    vma
 *              User virtual memory area structure pointer.
 *
 *  @ret    0
 *              Operation successfully completed.
 *          non-zero
 *              failure occured.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ----------------------------------------------------------------------------
 */
STATIC
int
DRV_Mmap (struct file *filp, struct vm_area_struct *vma) ;


/** ============================================================================
 *  @name   DRV_Read
 *
 *  @desc   Linux specific function to close the driver.
 *  ============================================================================
 */
STATIC
NORMAL_API
int
DRV_Read (struct file * filp, char * dst, size_t size, loff_t *offset) ;


/** ----------------------------------------------------------------------------
 *  @func   DRV_InitializeModule
 *
 *  @desc   Module initialization function for Linux driver.
 *
 *  @arg    None.
 *
 *  @ret    0
 *              Successful execution.
 *          non-zero
 *              Failure.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ----------------------------------------------------------------------------
 */
STATIC int __init DRV_InitializeModule (void) ;


/** ----------------------------------------------------------------------------
 *  @func   DRV_FinalizeModule
 *
 *  @desc   Module finalization  function for Linux driver.
 *
 *  @arg    None.
 *
 *  @ret    None.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    None
 *  ----------------------------------------------------------------------------
 */
STATIC void  __exit DRV_FinalizeModule (void) ;


/** ----------------------------------------------------------------------------
 *  @name   DriverOps
 *
 *  @desc   Function to invoke the APIs through ioctl.
 *  ----------------------------------------------------------------------------
 */
STATIC struct file_operations driverOps = {
    open:    DRV_Open,
    flush:   DRV_Flush,
    release: DRV_Release,
    unlocked_ioctl: DRV_Ioctl,
    mmap:    DRV_Mmap,
    read:    DRV_Read,
   .owner = THIS_MODULE
} ;

/** ----------------------------------------------------------------------------
 *  @name   DRV_Mmap
 *
 *  @desc   Mmap function implementation.
 *  ----------------------------------------------------------------------------
 */
STATIC
NORMAL_API
int
DRV_Mmap (struct file * filp, struct vm_area_struct * vma)
{
    vma->vm_page_prot = pgprot_noncached (vma->vm_page_prot) ;

    if (remap_pfn_range (vma,
                         vma->vm_start,
                         vma->vm_pgoff,
                         vma->vm_end - vma->vm_start,
                         vma->vm_page_prot)) {
        return -EAGAIN ;
    }
    return 0 ;
}


/*******************************************************************************
  @func  DRV_InitializeModule
  @desc  Module initialization function for Linux driver
*******************************************************************************/

STATIC int __init DRV_InitializeModule(void)
{
  int result = 0;
  DSP_STATUS status = DSP_SOK;

#if defined (CHNL_COMPONENT)
  Uint32 tabSize;
#endif

  TRC_0ENTER("DRV_InitializeModule");

  status = OSAL_Initialize();

#if defined (NOTIFY_COMPONENT)
  /* Initialize the User Event module */
  UEVENT_Initialize();
#endif

  PRINT_Printf("DSPLINK Module (%s) created\n", DSPLINK_VERSION);

  if (DSP_FAILED(status)) {
    TRC_2PRINT(TRC_LEVEL7,
               "*** error in '%s': 'OSAL_Initialize' failed, "
               "status 0x%x\n", __FUNCTION__, result);

    SET_FAILURE_REASON;
    result = -1;
  }
  else {

    /* To enable trace for a component and/or subcomponent, uncomment the
        corresponding statements below. (This is not a comprehensive list
        of available trace masks. See file signature.h) */
    TRC_ENABLE (ID_PMGR_ALL);
    TRC_ENABLE (ID_GEN_ALL);
    TRC_ENABLE (ID_OSAL_ALL);
    TRC_ENABLE (ID_LDRV_ALL);
    TRC_ENABLE (ID_LDRV_DATA_ALL);
    TRC_ENABLE (ID_LDRV_DRV_ALL);
    TRC_ENABLE (ID_LDRV_IPS_ALL);
    TRC_ENABLE (ID_LDRV_MQT_ALL);
    TRC_ENABLE (ID_LDRV_POOL_ALL);
    TRC_ENABLE (ID_ARCH_ALL);
    TRC_ENABLE (ID_ARCH_HAL_ALL);
    TRC_ENABLE (ID_ARCH_DSP_ALL);

    TRC_ENABLE (ID_PMGR_PROC);
    TRC_ENABLE (ID_PMGR_CHNL);
    TRC_ENABLE (ID_PMGR_MSGQ);

    TRC_ENABLE (ID_GEN_UTILS);
    TRC_ENABLE (ID_GEN_LIST);
    TRC_ENABLE (ID_GEN_COFF);
    TRC_ENABLE (ID_GEN_COFF_55x);
    TRC_ENABLE (ID_GEN_COFF_64x);
    TRC_ENABLE (ID_GEN_BINLOADER);
    TRC_ENABLE (ID_GEN_IDM);
    TRC_ENABLE (ID_GEN_NOLOADER);
    TRC_ENABLE (ID_GEN_COFF_MEM);
    TRC_ENABLE (ID_GEN_COFF_FILE);
    TRC_ENABLE (ID_GEN_COFF_SHM);

    TRC_ENABLE (ID_OSAL);
    TRC_ENABLE (ID_OSAL_DPC);
    TRC_ENABLE (ID_OSAL_ISR);
    TRC_ENABLE (ID_OSAL_KFILE);
    TRC_ENABLE (ID_OSAL_MEM);
    TRC_ENABLE (ID_OSAL_PRCS);
    TRC_ENABLE (ID_OSAL_SYNC);
    TRC_ENABLE (ID_OSAL_DRV);
    TRC_ENABLE (ID_OSAL_NOTIFY_KNL);
    TRC_ENABLE (ID_OSAL_USER);
    TRC_ENABLE (ID_OSAL_KFILE_PSEUDO);

    TRC_ENABLE (ID_LDRV);
    TRC_ENABLE (ID_LDRV_PROC);
    TRC_ENABLE (ID_LDRV_CHNL);
    TRC_ENABLE (ID_LDRV_MSGQ);
    TRC_ENABLE (ID_LDRV_CHIRPS);
    TRC_ENABLE (ID_LDRV_MPCS);
    TRC_ENABLE (ID_LDRV_MPLIST);
    TRC_ENABLE (ID_LDRV_RINGIO);
    TRC_ENABLE (ID_LDRV_SMM);
    TRC_ENABLE (ID_LDRV_OS);
    TRC_ENABLE (ID_LDRV_DATA);
    TRC_ENABLE (ID_LDRV_DATA_PCPY);
    TRC_ENABLE (ID_LDRV_DATA_ZCPY);
    TRC_ENABLE (ID_LDRV_DRV);
    TRC_ENABLE (ID_LDRV_DRV_SHM);
    TRC_ENABLE (ID_LDRV_IPS);
    TRC_ENABLE (ID_LDRV_IPS_IPS);
    TRC_ENABLE (ID_LDRV_MQT);
    TRC_ENABLE (ID_LDRV_MQT_PCPY);
    TRC_ENABLE (ID_LDRV_MQT_ZCPY);
    TRC_ENABLE (ID_LDRV_POOL);
    TRC_ENABLE (ID_LDRV_POOL_BUF);
    TRC_ENABLE (ID_LDRV_POOL_DMA);
    TRC_ENABLE (ID_LDRV_POOL_SMA);

    TRC_ENABLE (ID_ARCH_DSP);
    TRC_ENABLE (ID_ARCH_DSP_INTF);
    TRC_ENABLE (ID_ARCH_CFG);
    TRC_ENABLE (ID_ARCH_HAL);
    TRC_ENABLE (ID_ARCH_HAL_MAP);
    TRC_ENABLE (ID_ARCH_HAL_DSPCLK);
    TRC_ENABLE (ID_ARCH_HAL_INTGEN);
    TRC_ENABLE (ID_ARCH_HAL_DMA);
    TRC_ENABLE (ID_ARCH_HAL_RDWR);
    TRC_ENABLE (ID_ARCH_HAL_BOOT);
    TRC_ENABLE (ID_ARCH_HAL_PWR);
    TRC_ENABLE (ID_ARCH_HAL_MMU);
    TRC_ENABLE (ID_ARCH_SHMEM_PHY);
    TRC_ENABLE (ID_ARCH_PCI_PHY);
    TRC_ENABLE (ID_ARCH_VLYNQ_PHY);

    /* To set desired severity level for trace, uncomment the statement
       below and change the argument to the function below. 'TRC_ENTER'
       emits everything, while 'TRC_LEVEL4' emits only stuff explicitly
       marked as such */
    TRC_SET_SEVERITY (TRC_ENTER);

    result = register_chrdev(major, "dsplink", &driverOps);

    if (result < 0) {
      TRC_2PRINT(TRC_LEVEL7,
                 "*** error in '%s': Linux API 'register_chrdev' "
                 "failed, status 0x%x\n", __FUNCTION__, result);

      status = DSP_EFAIL;
      SET_FAILURE_REASON;
    }

#if defined (CHNL_COMPONENT)
    else {
      tabSize = sizeof (Uint32) * MAX_DSPS * MAX_CHANNELS;
      status = MEM_Calloc((Void **) &DRV_ChnlIdToPoolId,
                          tabSize,
                          &DRV_MemAllocAttrs);

      if (DSP_FAILED (status)) {
        result = -1;
        SET_FAILURE_REASON;
      }
    }
#endif /* if defined (CHNL_COMPONENT) */

    /* NKim, for kernel versions >= 2.6.26 */
    dsplink_class = class_create(THIS_MODULE, "dsplink");
    device_create(dsplink_class, NULL, MKDEV(major, 0), NULL, "dsplink");

    if (DSP_SUCCEEDED(status)) {
      DRV_IsInitialized = TRUE;
    }
  }

  TRC_1LEAVE("DRV_InitializeModule", result);
  return result;
}

/*******************************************************************************
  @name  DRV_FinalizeModule
  @desc  Linux driver function to finalize the driver module
*******************************************************************************/

STATIC NORMAL_API void __exit DRV_FinalizeModule (void)
{
  DSP_STATUS status = DSP_SOK;

#if defined (CHNL_COMPONENT)
  MemFreeAttrs freeAttrs;
#endif

  TRC_0ENTER("DRV_FinalizeModule");

#if defined (CHNL_COMPONENT)
  freeAttrs.physicalAddress = DRV_MemAllocAttrs.physicalAddress;
  freeAttrs.size = sizeof (Uint32) * MAX_DSPS * MAX_CHANNELS;

  status = MEM_Free((Pvoid *) &DRV_ChnlIdToPoolId, &freeAttrs);

  if (DSP_FAILED (status)) {
    SET_FAILURE_REASON;
  }
#endif

  /* NKim, for kernel versions >= 2.6.26 */
  device_destroy(dsplink_class, MKDEV(major, 0));
  class_destroy(dsplink_class);

  unregister_chrdev(major, "dsplink");

  DRV_IsInitialized = FALSE;

#if defined (NOTIFY_COMPONENT)
  UEVENT_Finalize ();
#endif

  /* Unconditional call OSAL_Finalize */
  status = OSAL_Finalize(TRUE);

  if (DSP_FAILED(status)) {
    TRC_2PRINT(TRC_LEVEL7,
               "*** error in '%s': 'OSAL_Finalize' failed, "
               "status 0x%x\n", __FUNCTION__, result);

    SET_FAILURE_REASON;
  }

  TRC_1LEAVE("DRV_FinalizeModule", result);
}

/*******************************************************************************
  @name  DRV_Open
  @desc  Linux specific function to open the driver
*******************************************************************************/

int DRV_Open(struct inode * inode, struct file * filp)
{
  return 0;
}

/*******************************************************************************
  @name  DRV_Flush
  @desc  Linux specific function to flush the driver
*******************************************************************************/

STATIC NORMAL_API int DRV_Flush(struct file *fp, fl_owner_t owner)
{
  return 0;
}

/*******************************************************************************
  @name  DRV_Read
  @desc  Linux specific function to read data from the driver
*******************************************************************************/

STATIC NORMAL_API int DRV_Read(struct file *filp,
                               char *dst,
                               size_t size,
                               loff_t *offset)
{
  Uint32 nRead = 0;

#if defined (NOTIFY_COMPONENT)
  nRead = UEVENT_GetBuf((Pvoid) dst);
#endif

  return nRead;
}

/** ============================================================================
 *  @name   DRV_Release
 *
 *  @desc   Linux specific function to close the driver.
 *  ============================================================================
 */
STATIC NORMAL_API int DRV_Release(struct inode *inode, struct file *filp)
{
  DSP_STATUS  status = DSP_SOK;
  pid_t       pid;
  Int         i;

  /* get the pid associated with the file pointer */
  pid = pid_nr(filp->f_owner.pid);

  /* check if application terminated and we have a valid snoop value */
  if ((pid != 0) && (DRV_dspId != 0xffff)) {

#if DSPLINK_TERMINATE_EVT != (-1)
    /* send terminate event to dsp */
    status = PMGR_PROC_sendTerminateEvent(DRV_dspId);

    if (DSP_FAILED(status)) 
      TRC_2PRINT(TRC_LEVEL4,
             "*** error in '%s': 'PMGR_PROC_sendTerminateEvent' failed, "
             "status 0x%x\n", __FUNCTION__, status);

      SET_FAILURE_REASON;
    }
#else
        /*  Replicate the same actions as the user-mode exit handler,
         *  which are summarized here.
         *
         *  MSGQ_transportClose(procId);
         *  PROC_stop(procId);
         *
         *  ioctl(DRV_handle->driverHandle, CMD_PROC_CLEANUP, &args);
         *
         *  for (i = 0 ; i < MAX_POOLENTRIES ; i++) {
         *      POOL_close (i) ;
         *  }
         *
         *  PROC_detach(procId);
         *  PROC_destroy();
         */
#if defined(MSGQ_COMPONENT)
//      if (attached && opened) {
            /* MSGQ_transportClose(procId) */
            PMGR_MSGQ_transportClose(DRV_dspId);
//      }
#endif
    /* PROC_stop(procId) */
    PMGR_PROC_stop(DRV_dspId);

    /* ioctl(DRV_handle->driverHandle, CMD_PROC_CLEANUP, &args) */
    DSPLINK_Cleanup();

#if defined(POOL_COMPONENT)
    for (i = 0 ; i < MAX_POOLENTRIES; i++) {
      /* POOL_close(i) */
      /* LDRV_POOL_close(i); TODO, this is currently not working. */
    }
#endif

        /* PROC_detach(procId) BEGIN */
//      if (attached) {
#if defined(RINGIO_COMPONENT)
            /* _RingIO_exit(procId); */
            /* TODO, requires user state which has been lost */
#endif

#if defined(MPLIST_COMPONENT)
            /* _MPLIST_exit(procId); */
            /* TODO, requires user state which has been lost */
#endif

#if defined(MPLIST_COMPONENT) || defined(RINGIO_COMPONENT)
//          if (isLastDetach) {
                /* _RingIO_moduleExit(procId); TODO */
                /* _MPLIST_moduleExit(procId); TODO */
//          }
#endif

#if defined(MPCS_COMPONENT)
            /* _MPCS_exit(procId); */
            /* TODO, requires user state which has been lost */
#endif

#if defined(NOTIFY_COMPONENT)
            /* _NOTIFY_exit(procId); */
            NOTIFY_KnlFinalize(DRV_dspId);
#endif

            /* DRV_INVOKE(DRV_handle, CMD_PROC_DETACH, &args); */
            PMGR_PROC_detach(DRV_dspId, NULL);
//      }
        /* PROC_detach(procId) END */

        /* PROC_destroy() BEGIN */
//      if (lastDestroy) {
            /* _SYNC_USR_exit(); */
            /* TODO, requires user state which has been lost */

            /* _IDM_USR_exit(); */
            IDM_exit();

            /* _MEM_USR_exit(); */
            /* nothing to do */
//      }

        /* DRV_INVOKE(DRV_handle, CMD_PROC_DESTROY, &args); */
        PMGR_PROC_destroy();
        /* PROC_destroy() END */

#endif

    /* this is a one shot trigger, clear snoop value */
    DRV_dspId = 0xffff;
  }

  return status;
}

/********************************************************************************
  @name  DRV_Ioctl
  @desc  Function to invoke the APIs through ioctl
********************************************************************************/

STATIC NORMAL_API long DRV_Ioctl(struct file * filp,
                                 unsigned int cmd,
                                 unsigned long args)
{
  DSP_STATUS status = DSP_SOK;
  void *srcArgs = (void*) args;
  int osStatus = 0;
  int retVal = 0;

  /* this is the local copy we use for copying user data into. NOTE, since
     allocated on the stack, make sure to write out any changes back to
     the user before leaving */
  CMD_Args apiArgs;

  TRC_3ENTER("DRV_Ioctl", filp, cmd, args);

  /* first of all, copy the main structure from user space. As known, this
     only results in a 'shallow copy'. Pointers are copied (however, their
     destinations are not, thus copy them additionally where required) */
  retVal = copy_from_user(&apiArgs, srcArgs, sizeof(CMD_Args));
  DBC_Assert((0 == retVal) && "Failed to copy data from user");

  status = DRV_CallAPI(cmd, &apiArgs);

  if (DSP_FAILED(status)) {
    TRC_2PRINT(TRC_LEVEL7,
               "*** error in '%s': 'DRV_CallAPI' failed, status "
               "0x%x\n", __FUNCTION__, retVal);

    if (status == -ERESTARTSYS) {
      osStatus = -ERESTARTSYS;
    }
    else {
      osStatus = -1;
    }
  }

  /* always do this regardless of previous success status. This is a one
     shot trigger, clear the 'snoop' value */
  if (cmd == CMD_PROC_SENDTERMEVT) {
    DRV_dspId = 0xffff;
  }

  /* now, to finalize the API call, write back the main 'args' struct, if
     there are any changes (as indicated by 'osStatus'). The result of the
     DSP operation is found in 'args->apiStatus' */
  if (osStatus == 0) {
    retVal = copy_to_user(srcArgs, &apiArgs, sizeof(CMD_Args));
    DBC_Assert((0 == retVal) && "Failed to copy data to user");
  }

  TRC_1LEAVE ("DRV_Ioctl", status);
  return osStatus;
}

/*******************************************************************************
  @name  module_init/module_exit
  @desc  Macro calls that indicate initialization and finalization functions
         to the kernel
*******************************************************************************/

MODULE_LICENSE ("GPL v2");
module_init (DRV_InitializeModule);
module_exit (DRV_FinalizeModule);

/********************************************************************************
  @name  DRV_CallAPI
  @desc  Function to invoke the APIs through ioctl
********************************************************************************/

STATIC NORMAL_API DSP_STATUS DRV_CallAPI(Uint32 cmd, CMD_Args *args)
{
  DSP_STATUS status = DSP_SOK;     /* status of driver's ioctl    */
  DSP_STATUS retStatus = DSP_SOK;  /* status of the PMGR function */
  int i, retVal = 0;

  TRC_2ENTER ("DRV_CallAPI", cmd, args) ;

  args->apiStatus = DSP_SOK;

  switch (cmd) {

#if defined (MSGQ_COMPONENT)
    case CMD_MSGQ_PUT:
    {

#if defined (LOG_GD_MSGQ_PUT)
      /* Log the event */
      DSPLINKLOG_LogEvent(GD_MSGQ_PUT,
                          args->apiArgs.msgqPutArgs.msg->msgId,
                          (Uint32) args->apiArgs.msgqPutArgs.msgqQueue,
                          (Uint32) args->apiArgs.msgqPutArgs.msg,
                          (Uint32) (args->apiArgs.msgqPutArgs.msg)->size,
                          0,
                          0);
#endif

      retStatus = PMGR_MSGQ_put (args->apiArgs.msgqPutArgs.msgqQueue,
                                 args->apiArgs.msgqPutArgs.msg);

      args->apiStatus = retStatus;
      break;
    }

    /* propagate the third argument of type 'MSGQ_Msg' back to the user.
       Since the value contained in the 'msgqGetArgs' is not a pointer,
       we dont need to involve 'copy_to_user' */
    case CMD_MSGQ_GET:
    {
      MSGQ_Msg msg;

      retStatus = PMGR_MSGQ_get(args->apiArgs.msgqGetArgs.msgqQueue,
                                args->apiArgs.msgqGetArgs.timeout,
                                &msg);

      if (DSP_SUCCEEDED(retStatus)) {
        args->apiArgs.msgqGetArgs.poolId = msg->poolId;
        args->apiArgs.msgqGetArgs.msgAddr = (Uint32) msg;
      }

      args->apiStatus = retStatus;
      break;
    }

#endif /* if defined (MSGQ_COMPONENT) */

#if defined (CHNL_COMPONENT)
    case CMD_CHNL_ISSUE:
    {
      ProcessorId procId = args->apiArgs.chnlIssueArgs.procId;
      ChannelId chnlId = args->apiArgs.chnlIssueArgs.chnlId;
      ChannelIOInfo ioInfo;

      DBC_Assert((NULL != args->apiArgs.chnlIssueArgs.ioReq) &&
                 "Expected valid IO parameters for 'CMD_CHNL_ISSUE'");

      /* copy the entire 'ChannelIOInfo' struct first */
      retVal = copy_from_user(
                         (void*) &ioInfo,
                         (void*) args->apiArgs.chnlIssueArgs.ioReq,
                         sizeof(ChannelIOInfo));

      DBC_Assert((0 == retVal) && "Failed to copy data from user");

#if defined (LOG_GD_CHNL_I_START)
      /* Log the event */
      DSPLINKLOG_LogEvent(
                  GD_CHNL_I_START,
                  0,
                  (((procId << 16) & 0xFFFF0000) | (chnlId & 0xFFFF)),
                  (Uint32) ioInfo.buffer,
                  ioInfo.size,
                  0,
                  0);
#endif

      retStatus = PMGR_CHNL_issue(procId, chnlId, &ioInfo, NULL);

#if defined (LOG_GD_CHNL_I_COMPLETE)
      /* Log the event */
      DSPLINKLOG_LogEvent(
                  GD_CHNL_I_COMPLETE,
                  0,
                  (((procId << 16) & 0xFFFF0000) | (chnlId & 0xFFFF)),
                  (Uint32) ioInfo.buffer,
                  ioInfo.size,
                  0,
                  0);
#endif

      args->apiStatus = retStatus;
      break;
    }

    case CMD_CHNL_RECLAIM:
    {
      ProcessorId procId = args->apiArgs.chnlReclaimArgs.procId;
      ChannelId chnlId = args->apiArgs.chnlReclaimArgs.chnlId;
      Uint32 timeout = args->apiArgs.chnlReclaimArgs.timeout;
      ChannelIOInfo ioInfo;

      /* This probably does not make much sense, since the user-supplied
         info is not supposed to contain any meaningful values yet (only
         initializer values (if initialized)). However, we still provide
         an explicit copy for more consistency */
      retVal = copy_from_user(
                       (void*) &ioInfo,
                       (void*) args->apiArgs.chnlReclaimArgs.ioReq,
                       sizeof(ChannelIOInfo));

      DBC_Assert((0 == retVal) && "Failed to copy data from user");

//  = args->apiArgs.chnlReclaimArgs.ioReq;

#if defined (LOG_GD_CHNL_R_START)
      /* Log the event */
      DSPLINKLOG_LogEvent(
                  GD_CHNL_R_START,
                  0,
                  (((procId << 16) & 0xFFFF0000) | (chnlId & 0xFFFF)),
                  (Uint32) NULL,
                  ioInfo.size,
                  0,
                  0);
#endif

      retStatus =
        PMGR_CHNL_reclaim(procId, chnlId, timeout, &ioInfo, NULL);

#if defined (LOG_GD_CHNL_R_COMPLETE)
      /* Log the event */
      DSPLINKLOG_LogEvent(
                  GD_CHNL_R_COMPLETE,
                  0,
                  (((procId << 16) & 0xFFFF0000) | (chnlId & 0xFFFF)),
                  (Uint32) ioInfo.buffer,
                  ioInfo.size,
                  0,
                  0);
#endif

      /* commit created values back to the user. NOTE, that we don't have
         to worry about separately writing the buffer since its address
         will be explicitly translated later in 'DRV_Invoke' */
      retVal = copy_to_user(
                       (void*) args->apiArgs.chnlReclaimArgs.ioReq,
                       (void*) &ioInfo,
                       sizeof(ChannelIOInfo));

      DBC_Assert((0 == retVal) && "Failed to copy data to user");

      args->apiStatus = retStatus;
      break;
    }
#endif /* if defined (CHNL_COMPONENT) */

#if defined (MSGQ_COMPONENT)
    case CMD_MSGQ_ALLOC:
    {
      MsgqMsg msg;
      retStatus = PMGR_MSGQ_alloc(args->apiArgs.msgqAllocArgs.poolId,
                                  args->apiArgs.msgqAllocArgs.size,
                                  &msg);

      args->apiArgs.msgqAllocArgs.msgAddr = (Uint32) msg;
      args->apiStatus = retStatus;
      break;
    }

    case CMD_MSGQ_FREE:
    {
      retStatus = PMGR_MSGQ_free(args->apiArgs.msgqFreeArgs.msg);
      args->apiStatus = retStatus;
      break;
    }

#endif /* if defined (MSGQ_COMPONENT) */

    case CMD_PROC_SETUP:
    {

#if defined (MSGQ_COMPONENT)
      LINKCFG_Gpp * gppObj ;
#endif

      retStatus = PMGR_PROC_setup(args->apiArgs.procSetupArgs.linkCfg);

#if defined (MSGQ_COMPONENT)
      if (DSP_SUCCEEDED(retStatus)) {
        gppObj = LDRV_LinkCfgPtr->gppObject;
        DRV_MaxMsgqs = gppObj->maxMsgqs;
      }
#endif

      args->apiStatus = retStatus;
      break;
    }

    case CMD_PROC_DESTROY:
    {
      retStatus = PMGR_PROC_destroy();
      args->apiStatus = retStatus;

#if defined (DDSP_DEBUG)
      MEM_Debug();
#endif

      break;
    }

    case CMD_PROC_ISLASTDESTROY:
    {
      args->apiArgs.procIsLastDestroyArgs.lastDestroy =
        (PMGR_PROC_getSetupRefCount () == 1) ? TRUE : FALSE;

      args->apiStatus = DSP_SOK;
      break;
    }

    case CMD_PROC_ISLASTDETACH:
    {
      args->apiArgs.procIsLastDetachArgs.lastDetach =
        (PMGR_PROC_getAttachRefCount(
           args->apiArgs.procIsLastDetachArgs.procId) == 1) ?
                                    TRUE : FALSE;
      args->apiStatus = DSP_SOK;
      break;
    }

#if defined (MPCS_COMPONENT)
    case CMD_MPCS_MAPREGION:
    {
      retStatus = LDRV_MPCS_getMemInfo(
        &args->apiArgs.mpcsMapArgs.mpcsRegionArgs);

      args->apiStatus = retStatus;
      break;
    }
#endif

#if defined (RINGIO_COMPONENT)
    case CMD_RINGIO_MAPREGION:
    {
      retStatus = LDRV_RINGIO_getMemInfo(
        &args->apiArgs.ringIoArgs.ringioRegionArgs);

      args->apiStatus = retStatus;
      break;
    }
#endif

#if defined (MPLIST_COMPONENT)
    case CMD_MPLIST_MAPREGION:
    {
      retStatus = LDRV_MPLIST_getMemInfo (
        &args->apiArgs.mplistArgs.mplistRegionArgs) ;

      args->apiStatus = retStatus;
      break;
    }
#endif

    case CMD_PROC_START:
      retStatus = PMGR_PROC_start(args->apiArgs.procStartArgs.procId);

      /* snoop the dsp id, used for sending terminate event */
      DRV_dspId = args->apiArgs.procStartArgs.procId;

      args->apiStatus = retStatus;
      break;

    case CMD_PROC_STOP:
      retStatus = PMGR_PROC_stop(args->apiArgs.procStopArgs.procId);

      args->apiStatus = retStatus;
      break;

    case CMD_PROC_GETSYMBOLADDRESS:
      retStatus = PMGR_PROC_getSymbolAddress (
                        args->apiArgs.procGetSymbolAddressArgs.procId,
                        args->apiArgs.procGetSymbolAddressArgs.symbolName,
                        args->apiArgs.procGetSymbolAddressArgs.dspAddr);

      args->apiStatus = retStatus;
      break;

    /* this is quite complicated. We need to provide a string argument for
       the image path as well as 'argv' which is of type 'Char8**'. All
       arguments are 'in' */
    case CMD_PROC_LOAD:
    {
      Char8 path[DSP_MAX_STRLEN] = { 0 };
      Char8 **argv;
      Char8 *arg;
      Uint32 argc;

      if (args->apiArgs.procLoadArgs.imagePath != NULL) {
        retVal = copy_from_user(
                         (void*) path,
                         (void*) args->apiArgs.procLoadArgs.imagePath,
                         DSP_MAX_STRLEN);

        DBC_Assert((0 == retVal) && "Failed to copy data from user");
      }

      if (status != -EFAULT) {
        /* this is annoying, first copy the shallow array of strings into
           provided temporary buffer */
        argc = args->apiArgs.procLoadArgs.argc;
        DBC_Assert(argc > 0);

        argv = vmalloc(argc * sizeof(Char8*));

        retVal = copy_from_user(
          argv, args->apiArgs.procLoadArgs.argv, argc * sizeof(Char8*));

        if (retVal != 0) {
          printk(KERN_ALERT "*** error in '%s': bad 'copy_from_user' "
                            "(CMD_PROC_LOAD), status 0x%x\n",
                            __FUNCTION__, retVal);

          status = -EFAULT;
        }
        else {
          /* now copy each argument into a separate string buffer. Be sure
             to read/index/dereference the copied array */
          for (i = 0; i < argc; ++i)
          {
            DBC_Assert(argv[i] != NULL);

            arg = vmalloc(DSP_MAX_STRLEN);
            retVal = copy_from_user(arg, argv[i], DSP_MAX_STRLEN);

            if (retVal != 0) {
              printk(KERN_ALERT "*** error in '%s': bad 'copy_from_user' "
                                "(CMD_PROC_LOAD), status 0x%x\n",
                                __FUNCTION__, retVal);

              status = -EFAULT;
              break;

            } else argv[i] = arg;
          }
        }
      }

      /* NOTE, this means, if there are any errors copying data from user-
         space, the return is -EFAULT, but the 'apiStatus' is DSP_SOK */
      if (status != -EFAULT)
      {
        retStatus = PMGR_PROC_load(
          args->apiArgs.procLoadArgs.procId, path, argc, argv);

        /* can safely destroy all dynamically created data now, since all
           arguments are 'in' */
        for (i = 0; i < argc; ++i) vfree(argv[i]);

        vfree(argv);
      }

      args->apiStatus = retStatus;
      break;
    }

    case CMD_PROC_LOADSECTION:
      retStatus = PMGR_PROC_loadSection(
        args->apiArgs.procLoadSectionArgs.procId,
        args->apiArgs.procLoadSectionArgs.imagePath,
        args->apiArgs.procLoadSectionArgs.sectID);

      args->apiStatus = retStatus;
      break;

    case CMD_PROC_READ:
      retStatus = PMGR_PROC_read(args->apiArgs.procReadArgs.procId,
                                 args->apiArgs.procReadArgs.dspAddr,
                                 args->apiArgs.procReadArgs.numBytes,
                                 args->apiArgs.procReadArgs.buffer);

      args->apiStatus = retStatus;
      break;

    case CMD_PROC_WRITE:
      retStatus = PMGR_PROC_write(args->apiArgs.procWriteArgs.procId,
                                  args->apiArgs.procWriteArgs.dspAddr,
                                  args->apiArgs.procWriteArgs.numBytes,
                                  args->apiArgs.procWriteArgs.buffer);

      args->apiStatus = retStatus;
      break;

    case CMD_PROC_ATTACH:
    {

#if defined (CHNL_COMPONENT)
      ProcessorId procId;
      ChannelId chnlId;
#endif
      retStatus = PMGR_PROC_attach(args->apiArgs.procAttachArgs.procId,
                                   args->apiArgs.procAttachArgs.attr,
                                   NULL);
#if defined (CHNL_COMPONENT)
      if ((DSP_SUCCEEDED (retStatus)) && (retStatus != DSP_SALREADYATTACHED))
      {
        procId = args->apiArgs.procAttachArgs.procId;

        for (chnlId = 0;
             ((chnlId < MAX_CHANNELS) && DSP_SUCCEEDED (retStatus));
             chnlId++)
        {
          retStatus = LDRV_DATA_getPoolId(procId,
                                          chnlId,
                                          &DRV_ChnlIdToPoolId [procId][chnlId]);

          if (retStatus == DSP_ENOTFOUND) {
            /* DSP_ENOTFOUND indicates that the channel ID is
               not in the range of any configured data driver */
            retStatus = DSP_SOK;
          }
        }
      }
#endif

      args->apiStatus = retStatus;
      break;
    }

    case CMD_PROC_DETACH:
      retStatus = PMGR_PROC_detach(args->apiArgs.procDetachArgs.procId,
                                   NULL);
      args->apiStatus = retStatus;
      break;

    case CMD_PROC_CONTROL:
      retStatus = PMGR_PROC_control (
                    args->apiArgs.procControlArgs.procId,
                    args->apiArgs.procControlArgs.cmd,
                    args->apiArgs.procControlArgs.arg);

      args->apiStatus = retStatus;
      break;

    case CMD_PROC_GETSTATE:
      retStatus = PMGR_PROC_getState(
                    args->apiArgs.procGetStateArgs.procId,
                    args->apiArgs.procGetStateArgs.procState);

      args->apiStatus = retStatus;
      break;

    case CMD_PROC_SENDTERMEVT:
      retStatus = PMGR_PROC_sendTerminateEvent(
              args->apiArgs.procGetSymbolAddressArgs.procId);

      args->apiStatus = retStatus;
      break;

#if defined (DDSP_PROFILE)
    case CMD_PROC_INSTRUMENT:
      retStatus = PMGR_PROC_instrument(
                    args->apiArgs.procInstrumentArgs.procId,
                    args->apiArgs.procInstrumentArgs.procStats);

      args->apiStatus = retStatus;
      break;
#endif

#if defined (DDSP_DEBUG)
    case CMD_PROC_DEBUG:
      PMGR_PROC_debug(args->apiArgs.procDebugArgs.procId);
      break ;
#endif

    case CMD_PROC_CLEANUP:
      DSPLINK_Cleanup();
      break;

#if defined (CHNL_COMPONENT)
    case CMD_CHNL_CREATE:
    {
      ChannelAttrs attrs;

      retVal = copy_from_user(
                        (void*) &attrs,
                        (void*) args->apiArgs.chnlCreateArgs.attrs,
                        sizeof(ChannelAttrs));

      DBC_Assert((0 == retVal) && "Failed to copy data from user");

      retStatus = PMGR_CHNL_create(
                    args->apiArgs.chnlCreateArgs.procId,
                    args->apiArgs.chnlCreateArgs.chnlId,
                    &attrs,
                    NULL);

      args->apiStatus = retStatus;
      break;
    }

    case CMD_CHNL_DELETE:
      retStatus = PMGR_CHNL_delete(args->apiArgs.chnlDeleteArgs.procId,
                                   args->apiArgs.chnlDeleteArgs.chnlId,
                                   NULL);

      args->apiStatus = retStatus;
      break;

    case CMD_CHNL_ALLOCATEBUFFER:
    {
      ProcessorId procId;
      ChannelId chnlId;
      Uint32 size;
      Uint32 numBufs;
      Char8 **bufArray;

      procId = args->apiArgs.chnlAllocateBufferArgs.procId;
      chnlId = args->apiArgs.chnlAllocateBufferArgs.chnlId;
      size = args->apiArgs.chnlAllocateBufferArgs.size;
      numBufs = args->apiArgs.chnlAllocateBufferArgs.numBufs;

      /* in order to be able to transfer created buffers back to the user,
         we need to preserve user addresses. And since there can be more
         than just 1 buffer, we need to do it dynamically */
      status = MEM_Alloc((void **) &bufArray,
                         sizeof(Char8*) * numBufs,
                         MEM_DEFAULT);

      DBC_Assert(DSP_SUCCEEDED(status) && "Failed allocating memory");

      retStatus = PMGR_CHNL_allocateBuffer(procId,
                                           chnlId,
                                           bufArray,
                                           size,
                                           numBufs,
                                           NULL);

      /* now write all created buffers back to the user, write the entire
         array at once */
      retVal = copy_to_user(
                 (void*) args->apiArgs.chnlAllocateBufferArgs.bufArray,
                 (void*) bufArray,
                 sizeof(Char8*) * numBufs);

      DBC_Assert((0 == retVal) && "Failed to copy data to user");

      /* do the housekeeping now. We can safely drop all of the allocated
         structures here */
      status = MEM_Free((Pvoid*) &bufArray, NULL);

      DBC_Assert(DSP_SUCCEEDED(status) && "Failed releasing memory");

      args->apiStatus = retStatus;
      break;
    }

    case CMD_CHNL_FREEBUFFER:
    {
      ProcessorId procId;
      ChannelId chnlId;
      Uint32 numBufs;
      Char8 **bufArray;

      procId = args->apiArgs.chnlFreeBufferArgs.procId;
      chnlId = args->apiArgs.chnlFreeBufferArgs.chnlId;
      numBufs = args->apiArgs.chnlFreeBufferArgs.numBufs;

      /* here too, work on a temporary array of buffer addresses. Allocate
         dynamically and copy each buffer address (which is translated to
         the kernel space by now) */
      status = MEM_Alloc((void **) &bufArray,
                         sizeof(Char8*) * numBufs,
                         MEM_DEFAULT);

      DBC_Assert(DSP_SUCCEEDED(status) && "Failed allocating memory");

      retVal = copy_from_user(
                 (void*) bufArray,
                 (void*) args->apiArgs.chnlFreeBufferArgs.bufArray,
                 sizeof(Char8*) * numBufs);

      DBC_Assert((0 == retVal) && "Failed to copy data from user");

      retStatus = PMGR_CHNL_freeBuffer(procId,
                                       chnlId,
                                       bufArray,
                                       numBufs,
                                       NULL);

      /* do the housekeeping now. We can safely drop all of the allocated
         structures here */
      status = MEM_Free((Pvoid*) &bufArray, NULL);

      DBC_Assert(DSP_SUCCEEDED(status) && "Failed releasing memory");

      args->apiStatus = retStatus;
      break;
    }

    case CMD_CHNL_IDLE:
      retStatus = PMGR_CHNL_idle(args->apiArgs.chnlIdleArgs.procId,
                                 args->apiArgs.chnlIdleArgs.chnlId,
                                 NULL);

      args->apiStatus = retStatus;
      break;

    case CMD_CHNL_FLUSH:
      retStatus = PMGR_CHNL_flush(args->apiArgs.chnlFlushArgs.procId,
                                  args->apiArgs.chnlFlushArgs.chnlId,
                                  NULL);

      args->apiStatus = retStatus;
      break ;

    case CMD_CHNL_CONTROL:
      retStatus = PMGR_CHNL_control (
                        args->apiArgs.chnlControlArgs.procId,
                        args->apiArgs.chnlControlArgs.chnlId,
                        args->apiArgs.chnlControlArgs.cmd,
                        args->apiArgs.chnlControlArgs.arg);

      args->apiStatus = retStatus;
      break;

#if defined (DDSP_PROFILE)
    case CMD_CHNL_INSTRUMENT:
      retStatus = PMGR_CHNL_instrument(
                       args->apiArgs.chnlInstrumentArgs.procId,
                       args->apiArgs.chnlInstrumentArgs.chnlId,
                       args->apiArgs.chnlInstrumentArgs.chnlStats);

      args->apiStatus = retStatus;
      break;
#endif

#if defined (DDSP_DEBUG)
    case CMD_CHNL_DEBUG:
      PMGR_CHNL_debug(args->apiArgs.chnlDebugArgs.procId,
                      args->apiArgs.chnlDebugArgs.chnlId);

      break;
#endif

    case CMD_DRV_GETCHNLMAPTABLE_ADDRESS:
      args->apiArgs.drvPhyAddrArgs.phyAddr =
        (Void *) DRV_MemAllocAttrs.physicalAddress;

      break;

#endif /* if defined (CHNL_COMPONENT) */

#if defined (MSGQ_COMPONENT)
    /* the second argument to 'PMGR_MSGQ_transportOpen' is 'in' and is also
       a pointer to a struct (of which we only need a pool-ID) which we need
       to copy */
    case CMD_MSGQ_TRANSPORTOPEN:
    {
      ZCPYMQT_Attrs attrs;

      DBC_Assert((NULL != args->apiArgs.msgqTransportOpenArgs.attrs) &&
                 "Expected valid attributes for 'CMD_MSGQ_TRANSPORTOPEN'");

      retVal = copy_from_user(
                        (void*) &attrs,
                        (void*) args->apiArgs.msgqTransportOpenArgs.attrs,
                        sizeof(ZCPYMQT_Attrs));

      DBC_Assert((0 == retVal) && "Failed to copy data from user");

      retStatus = PMGR_MSGQ_transportOpen(
                                args->apiArgs.msgqTransportOpenArgs.procId,
                                &attrs);

      args->apiStatus = retStatus;
      break;
    }

    case CMD_MSGQ_TRANSPORTCLOSE:
      retStatus = PMGR_MSGQ_transportClose(
                              args->apiArgs.msgqTransportCloseArgs.procId);

      args->apiStatus = retStatus;
      break ;

    /* the second argument to 'PMGR_MSGQ_open' is 'out', while the third is
       'in'. Proceed in the same manner as we did for other commands */
    case CMD_MSGQ_OPEN:
    {
      /* Only NULL attributes are supported for Linux for MSGQ_open () */
      if (args->apiArgs.msgqOpenArgs.attrs != NULL) {
        retStatus = DSP_ENOTSUPPORTED;
      }
      else {
        Char8 name[DSP_MAX_STRLEN] = { 0 };
        MSGQ_Queue queue;
        MSGQ_Attrs attrs;
        MSGQ_Attrs *pAttrs = NULL;

        if (args->apiArgs.msgqOpenArgs.attrs != NULL)
        {
          /* use a local copy 'attrs' for the third argument */
          retVal = copy_from_user(
                            (void*) &attrs,
                            (void*) args->apiArgs.msgqOpenArgs.attrs,
                            sizeof(MSGQ_Attrs));

          DBC_Assert((0 == retVal) && "Failed to copy data from user");
          pAttrs = &attrs;
        }

        retVal = copy_from_user(
          name, args->apiArgs.msgqOpenArgs.queueName, DSP_MAX_STRLEN);

        DBC_Assert((0 == retVal) && "Failed to copy data from user");

        retStatus = PMGR_MSGQ_open(name, &queue, pAttrs, NULL);

        if (DSP_SUCCEEDED(retStatus)) {
          /* write the local copy 'queue' back to the user space */
          retVal = copy_to_user(
                        (void*) args->apiArgs.msgqOpenArgs.msgqQueue,
                        (void*) &queue,
                        sizeof(MSGQ_Queue));

          DBC_Assert((0 == retVal) && "Failed to copy data to user");
        }
      }

      args->apiStatus = retStatus;
      break;
    }

    case CMD_MSGQ_CLOSE:
      retStatus = PMGR_MSGQ_close(args->apiArgs.msgqCloseArgs.msgqQueue,
                                  NULL);

      args->apiStatus = retStatus;
      break;

    /* Dealing with 3 pointer arguments. The first one ('queueName') is a
       string, the second ('msgqQueue') is of type 'MSGQ_Queue' and the
       third ('attrs') is of type 'MSGQ_LocateAttrs'. The second argument
       ('msgqQueue') is 'out' */
    case CMD_MSGQ_LOCATE:
    {
      Char8 queueName[DSP_MAX_STRLEN] = { 0 };
      MSGQ_LocateAttrs attrs;
      MSGQ_Queue msgqQueue;

      DBC_Assert((NULL != args->apiArgs.msgqLocateArgs.queueName) &&
                 "Expected a valid queue name for 'CMD_MSGQ_LOCATE'");

      retVal = copy_from_user(
                       (void*) queueName,
                       (void*) args->apiArgs.msgqLocateArgs.queueName,
                       DSP_MAX_STRLEN);

      DBC_Assert((0 == retVal) && "Failed to copy data from user");

      retVal = copy_from_user(
                       (void*) &attrs,
                       (void*) args->apiArgs.msgqLocateArgs.attrs,
                       sizeof(MSGQ_LocateAttrs));

      DBC_Assert((0 == retVal) && "Failed to copy data from user");

      retStatus = PMGR_MSGQ_locate(queueName, &msgqQueue, &attrs);

      retVal = copy_to_user(
                       (void*) args->apiArgs.msgqLocateArgs.msgqQueue,
                       (void*) &msgqQueue,
                       sizeof(MSGQ_Queue));

      DBC_Assert((0 == retVal) && "Failed to copy data to user");

      args->apiStatus = retStatus;
      break;
    }

    case CMD_MSGQ_LOCATEASYNC:
      retStatus = PMGR_MSGQ_locateAsync(
                            args->apiArgs.msgqLocateAsyncArgs.queueName,
                            args->apiArgs.msgqLocateAsyncArgs.replyQueue,
                            args->apiArgs.msgqLocateAsyncArgs.attrs);
      args->apiStatus = retStatus;
      break;

    case CMD_MSGQ_RELEASE:
      retStatus = PMGR_MSGQ_release(
                               args->apiArgs.msgqReleaseArgs.msgqQueue);

      args->apiStatus = retStatus;
      break;

    case CMD_MSGQ_COUNT:
      retStatus = PMGR_MSGQ_count(args->apiArgs.msgqCountArgs.msgqQueue,
                                  args->apiArgs.msgqCountArgs.count);

      args->apiStatus = retStatus;
      break;

    case CMD_MSGQ_SETERRORHANDLER:
      retStatus = PMGR_MSGQ_setErrorHandler(
                           args->apiArgs.msgqSetErrorHandlerArgs.errorQueue,
                           args->apiArgs.msgqSetErrorHandlerArgs.poolId);

      args->apiStatus = retStatus;
      break ;

#if defined (DDSP_PROFILE)
    case CMD_MSGQ_INSTRUMENT:
      retStatus = PMGR_MSGQ_instrument(
                                 args->apiArgs.msgqInstrumentArgs.msgqQueue,
                                 args->apiArgs.msgqInstrumentArgs.retVal);

      args->apiStatus = retStatus;
      break;
#endif

#if defined (DDSP_DEBUG)
    case CMD_MSGQ_DEBUG:
      PMGR_MSGQ_debug(args->apiArgs.msgqDebugArgs.msgqQueue);

      args->apiStatus = retStatus;
      break;
#endif

#endif /* if defined (MSGQ_COMPONENT) */

#if defined (POOL_COMPONENT)
    case CMD_POOL_ALLOC:
    {
      retStatus = LDRV_POOL_alloc(args->apiArgs.poolAllocArgs.poolId,
                                  args->apiArgs.poolAllocArgs.bufPtr,
                                  args->apiArgs.poolAllocArgs.size);

      args->apiStatus = retStatus;
      break;
    }

    case CMD_POOL_FREE:
    {
      retStatus = LDRV_POOL_free(args->apiArgs.poolFreeArgs.poolId,
                                 args->apiArgs.poolFreeArgs.bufPtr,
                                 args->apiArgs.poolFreeArgs.size);

      args->apiStatus = retStatus;
      break;
    }

    /* The params the user passes to 'POOL_open' within a particular app-
       lication are found in 'args.apiArgs.poolOpenArgs.params.params'.
       'LDRV_POOL_open' requires an 'in' pointer to a valid struct of type
       'POOL_OpenParams'. Copy the value explicitly via additional call to
       'copy_from_user' */
    case CMD_POOL_OPEN:
    {
      POOL_OpenParams params;

      DBC_Assert((NULL != args->apiArgs.poolOpenArgs.params) &&
                 "Expected valid pool parameters for 'CMD_POOL_OPEN'");

      retVal = copy_from_user(
                          (void*) &params,
                          (void*) args->apiArgs.poolOpenArgs.params,
                          sizeof(POOL_OpenParams));

      DBC_Assert((0 == retVal) && "Failed to copy data from user");

      retStatus =
        LDRV_POOL_open(args->apiArgs.poolOpenArgs.poolId, &params);

      /* need to preserve POOL address data accumulated in 'params' for
         the later tasks (e.g. mmap). Thus, write the computed address data
         back but make sure not to touch the buffer configuration supplied
         by the user */
      retVal = copy_to_user((void*) args->apiArgs.poolOpenArgs.params,
                            (void*) &params,
                            sizeof(POOL_OpenParams));

      DBC_Assert((0 == retVal) && "Failed to copy data to user");

      args->apiStatus = retStatus;
      break;
    }

    case CMD_POOL_CLOSE:
    {
      retStatus = LDRV_POOL_close (args->apiArgs.poolCloseArgs.poolId);

      args->apiStatus = retStatus;
      break;
    }

    case CMD_POOL_WRITEBACK:
    {
      retStatus = LDRV_POOL_writeback(args->apiArgs.poolWBArgs.poolId,
                                      args->apiArgs.poolWBArgs.bufPtr,
                                      args->apiArgs.poolWBArgs.size);

      args->apiStatus = retStatus;
      break;
    }

    case CMD_POOL_INVALIDATE:
    {
      retStatus = LDRV_POOL_invalidate(args->apiArgs.poolInvArgs.poolId,
                                       args->apiArgs.poolInvArgs.bufPtr,
                                       args->apiArgs.poolInvArgs.size);

      args->apiStatus = retStatus;
      break;
    }
#endif /* if defined (POOL_COMPONENT) */

#if defined (NOTIFY_COMPONENT)
    case CMD_NOTIFY_INITIALIZE:
    {
      retStatus = NOTIFY_KnlInitialize(
                                args->apiArgs.notifyInitializeArgs.dspId);

      args->apiStatus = retStatus;
      break;
    }

    case CMD_NOTIFY_FINALIZE:
    {
      retStatus = NOTIFY_KnlFinalize(
                                args->apiArgs.notifyFinalizeArgs.dspId);

      args->apiStatus = retStatus;
      break;
    }

    case CMD_NOTIFY_REGISTER:
    {
      retStatus = NOTIFY_KnlRegister(
                               args->apiArgs.notifyRegisterArgs.dspId,
                               args->apiArgs.notifyRegisterArgs.ipsId,
                               args->apiArgs.notifyRegisterArgs.eventNo,
                               args->apiArgs.notifyRegisterArgs.fnNotifyCbck,
                               args->apiArgs.notifyRegisterArgs.cbckArg);

      args->apiStatus = retStatus;
      break;
    }

    case CMD_NOTIFY_UNREGISTER:
    {
      retStatus = NOTIFY_KnlUnregister(
                             args->apiArgs.notifyUnregisterArgs.dspId,
                             args->apiArgs.notifyUnregisterArgs.ipsId,
                             args->apiArgs.notifyUnregisterArgs.eventNo,
                             args->apiArgs.notifyUnregisterArgs.fnNotifyCbck,
                             args->apiArgs.notifyUnregisterArgs.cbckArg);

      args->apiStatus = retStatus;
      break;
    }

    case CMD_NOTIFY_NOTIFY:
    {
      retStatus = NOTIFY_KnlNotify(
                            args->apiArgs.notifyNotifyArgs.dspId,
                            args->apiArgs.notifyNotifyArgs.ipsId,
                            args->apiArgs.notifyNotifyArgs.eventNo,
                            args->apiArgs.notifyNotifyArgs.payload);

      args->apiStatus = retStatus;
      break;
    }

#if defined (DDSP_PROFILE)
    case CMD_NOTIFY_INSTRUMENT:
    {
      retStatus = NOTIFY_KnlInstrument(
                              args->apiArgs.ipsInstrumentArgs.dspId,
                              args->apiArgs.ipsInstrumentArgs.ipsId,
                              args->apiArgs.ipsInstrumentArgs.ipsStats);

      args->apiStatus = retStatus;
      break;
    }
#endif

#endif /* #if defined (NOTIFY_COMPONENT) */

    case CMD_IDM_INIT:
    {
      retStatus = IDM_init();

      args->apiStatus = retStatus;
      break;
    }

    case CMD_IDM_EXIT:
    {
      retStatus = IDM_exit();

      args->apiStatus = retStatus;
      break;
    }

    /* here, the main function 'IDM_create' accesses 'attrs' contained in
       'args' as a pointer. Thus, we copy the value and pass the copy for a
       safe reference */
    case CMD_IDM_CREATE:
    {
      IDM_Attrs attrs;

      retVal = copy_from_user((void*) &attrs,
                              (void*) args->apiArgs.idmCreateArgs.attrs,
                              sizeof(IDM_Attrs));

      DBC_Assert((0 == retVal) && "Failed to copy data from user");

      retStatus = IDM_create(args->apiArgs.idmCreateArgs.key, &attrs);

      args->apiStatus = retStatus;
      break;
    }

    case CMD_IDM_DELETE:
    {
      retStatus = IDM_delete(args->apiArgs.idmDeleteArgs.key);

      args->apiStatus = retStatus;
      break;
    }

    /* the actual operation 'IDM_acquireId' produces one 'out' value, which
       is the 'id'. Thus, we need to write it back upon completion */
    case CMD_IDM_ACQUIREID:
    {
      Uint32 id;
      Uint32 *userIdAddr;
      Char8 dstKey[DSP_MAX_STRLEN] = { 0 };

      /* copy the id-key into a local buffer. Accessing it directly (user-
         space) might (and most probably will) result in page faults */
      retVal = copy_from_user(
                         (void*) dstKey,
                         (void*) args->apiArgs.idmAcquireIdArgs.idKey,
                         DSP_MAX_STRLEN);

      DBC_Assert((0 == retVal) && "Failed to copy data from user");

      userIdAddr = args->apiArgs.idmAcquireIdArgs.id;

      retStatus = IDM_acquireId(
        args->apiArgs.idmAcquireIdArgs.key, dstKey, &id);

      if (DSP_SUCCEEDED(retStatus)) {
        /* write the created 'id' value back. I guess this is safe (i.e.
           will not be overwritten anything when writing the entire 'args'
           struct back to the user space) */
        retVal = copy_to_user((void*) userIdAddr,
                              (void*) &id,
                              sizeof(Uint32));

        DBC_Assert((0 == retVal) && "Failed to copy data to user");
      }

      args->apiStatus = retStatus;
      break;
    }

    case CMD_IDM_RELEASEID:
    {
      retStatus = IDM_releaseId(args->apiArgs.idmReleaseIdArgs.key,
                                args->apiArgs.idmReleaseIdArgs.id);

      args->apiStatus = retStatus;
      break;
    }

    default:
      status = DSP_EFAIL;
      break;
  }

  /* If any call returned -ERESTARTSYS, it must be propagated further */
  if (retStatus == -ERESTARTSYS) status = retStatus;

  TRC_1LEAVE("DRV_CallAPI", status);
  return status;
}

/** ----------------------------------------------------------------------------
 *  @func  DSPLINK_Cleanup
 *
 *  @desc  Clean up the kernel driver.
 *  ----------------------------------------------------------------------------
 */

STATIC NORMAL_API Void DSPLINK_Cleanup(Void) {

#if defined (MSGQ_COMPONENT)
  DSP_STATUS status = DSP_SOK;
  MSGQ_Queue msgqQueue;
  Uint32 i;

  /* Close any open Message Queues */
  for (i = 0 ; i < DRV_MaxMsgqs ; i++) {
    msgqQueue = ((Uint32) ID_GPP << 16) | i;

    status = PMGR_MSGQ_close(msgqQueue, NULL);

    if (DSP_SUCCEEDED (status)) {
      TRC_0PRINT(TRC_LEVEL4, "PMGR_MSGQ_close done\n");
    }
  }
#endif /* if defined (MSGQ_COMPONENT) */
}

/*******************************************************************************
  @name  DSPLINK_sendTerminateEvent
  @desc  Trigger a termination event
*******************************************************************************/

void DSPLINK_sendTerminateEvent(void)
{
  DSP_STATUS status = DSP_SOK;

  /* send terminate event if we have a valid snoop value */
  if (DRV_dspId != 0xffff) {

    /* send terminate event to dsp */
    status = PMGR_PROC_sendTerminateEvent(DRV_dspId);

    if (DSP_FAILED(status)) {
      SET_FAILURE_REASON;
    }

    /* this is a one shot trigger, clear snoop value */
    DRV_dspId = 0xffff;
  }
}

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
