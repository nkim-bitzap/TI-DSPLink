/** ============================================================================
 *  @file   loop.c
 *
 *  @path   $(DSPLINK)/gpp/src/samples/loop/
 *
 *  @desc   This is a loop application which sends a buffer across the DSP
 *          processor and recieves a buffer back using DSP/BIOS LINK.
 *          The data buffer received is verified aginst the data sent to DSP.
 *          This application transfers only one buffer and no buffer(s) are
 *          queued.
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


/*  ----------------------------------- DSP/BIOS Link                   */
#include <dsplink.h>

/*  ----------------------------------- DSP/BIOS LINK API               */
#include <proc.h>
#include <chnl.h>
#include <pool.h>
#if defined (DA8XXGEM)
#include <loaderdefs.h>
#endif

/*  ----------------------------------- Application Header              */
#include <loop.h>
#include <loop_os.h>


#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/*  ============================================================================
 *  @name   NUM_ARGS
 *
 *  @desc   Number of arguments specified to the DSP application.
 *  ============================================================================
 */
#define NUM_ARGS 2

/*******************************************************************************
  @name  XFER_INIT_CHAR
  @desc  The value used to initialize the output buffer
  @note  Make printable for a visual validation
*******************************************************************************/

#define XFER_INIT_CHAR (Char8) '0'

/** ============================================================================
 *  @name   NUMBUFFERPOOLS
 *
 *  @desc   Number of buffer pools in this application.
 *  ============================================================================
 */
#define NUMBUFFERPOOLS 1

/** ============================================================================
 *  @name   NUMBUFS
 *
 *  @desc   Number of buffers in pool.
 *  ============================================================================
 */
#define NUMBUFS        4

/** ============================================================================
 *  @name   POOL_ID
 *
 *  @desc   Pool id for this application.
 *  ============================================================================
 */
#define POOL_ID        0


/*  ============================================================================
 *  @name   LOOP_BufferSize
 *
 *  @desc   Size of buffer to be used for data transfer.
 *  ============================================================================
 */
STATIC Uint32  LOOP_BufferSize ;

/*  ============================================================================
 *  @name   LOOP_NumIterations
 *
 *  @desc   Number of iterations of data transfer.
 *          A value of 0 in LOOP_NumIterations implies infinite iterations.
 *  ============================================================================
 */
STATIC Uint32  LOOP_NumIterations ;

/** ============================================================================
 *  @name   LOOP_Buffers
 *
 *  @desc   Array of buffers used by the loop application.
 *          Length of array in this application is 1.
 *  ============================================================================
 */
STATIC Char8 *LOOP_Buffers[1];

/** ============================================================================
 *  @name   LOOP_IOReq
 *
 *  @desc   It gives information for adding or reclaiming a request.
 *  ============================================================================
 */

STATIC ChannelIOInfo LOOP_IOReq;

#if defined (DA8XXGEM)
/** ============================================================================
 *  @name   dspAddr
 *
 *  @desc   Address of c_int00 in the DSP executable.
 *  ============================================================================
 */
Uint32 LOOP_dspAddr ;

/** ============================================================================
 *  @name   shmAddr
 *
 *  @desc   Address of symbol DSPLINK_shmBaseAddres in the DSP executable.
 *  ============================================================================
 */
Uint32 LOOP_shmAddr ;

/** ============================================================================
 *  @name   argsAddr
 *
 *  @desc   Address of .args section in the DSP executable.
 *  ============================================================================
 */
Uint32 LOOP_argsAddr ;

/** ============================================================================
 *  @name   LINKCFG_config
 *
 *  @desc   Extern declaration to the default DSP/BIOS LINK configuration
 *          structure.
 *  ============================================================================
 */

extern LINKCFG_Object LINKCFG_config;

#endif

#if defined (VERIFY_DATA)
/** ----------------------------------------------------------------------------
 *  @func   LOOP_VerifyData
 *
 *  @desc   This function verifies the data-integrity of given buffer.
 *
 *  @arg    buf
 *              This is the pointer of the buffer whose contents are to be
 *              validated.
 *
 *  @ret    DSP_SOK
 *              Operation successfully completed.
 *          DSP_EFAIL
 *              Contents of the input buffer and the output buffer are
 *              different.
 *
 *  @enter  None
 *
 *  @leave  None
 *
 *  @see    XFER_CHAR
 *  ----------------------------------------------------------------------------
 */

STATIC NORMAL_API DSP_STATUS LOOP_VerifyData(IN Char8 *buf);

#endif /*  defined (VERIFY_DATA) */

/*******************************************************************************
  @func  LOOP_Create
  @desc  This function allocates and initializes resources used by
         this application
*******************************************************************************/

NORMAL_API DSP_STATUS LOOP_Create(IN Char8 *dspExecutable,
                                  IN Char8 *strBufferSize,
                                  IN Char8 *strNumIterations,
                                  IN Uint8 processorId)
{
  DSP_STATUS status = DSP_SOK;
  Char8 *temp = NULL;
  Uint32 numArgs = 0;

  /* 1 buffer pool containing 4 buffers */
  Uint32 numBufs[NUMBUFFERPOOLS] = { NUMBUFS };

#if defined (DA8XXGEM)
  NOLOADER_ImageInfo imageInfo;
#endif

  ChannelAttrs chnlAttrInput;
  ChannelAttrs chnlAttrOutput;
  Uint16 i;
  Char8 *args[NUM_ARGS];
  Uint32 size[NUMBUFFERPOOLS];

#if defined (ZCPY_LINK)
  SMAPOOL_Attrs poolAttrs;
#endif

  LOOP_0Print("Executing 'LOOP_Create'\n");

  /* Create and initialize the proc object */
  status = PROC_setup(NULL);

  /* Attach the Dsp with which the transfers have to be done */
  if (DSP_SUCCEEDED(status)) {
    status = PROC_attach(processorId, NULL);

    LOOP_1Print("  'PROC_attach' done, status 0x%x\n", status);
  }

  /* Open the pool */
  if (DSP_SUCCEEDED(status)) {
    size[0] = LOOP_BufferSize;

    /* array of sizes of buffer pools */
    poolAttrs.bufSizes = (Uint32 *) &size;

    /* array of buffer pools */
    poolAttrs.numBuffers = (Uint32 *) &numBufs;

    /* size of the array of buffer pools */
    poolAttrs.numBufPools = NUMBUFFERPOOLS;

#if defined (ZCPY_LINK)
    poolAttrs.exactMatchReq = TRUE;
#endif

    status =
      POOL_open(POOL_makePoolId(processorId, POOL_ID), &poolAttrs);

    LOOP_1Print("  'POOL_open' done, status 0x%x\n", status);
  }

  /* Load the executable on the DSP */
  if (DSP_SUCCEEDED (status)) {
    numArgs = NUM_ARGS;
    args[0] = strBufferSize;
    args[1] = strNumIterations;

#if defined (DA8XXGEM)
    if (LINKCFG_config.dspConfigs[processorId]->dspObject->doDspCtrl ==
        DSP_BootMode_NoBoot)
    {
      imageInfo.dspRunAddr = LOOP_dspAddr;
      imageInfo.shmBaseAddr = LOOP_shmAddr;
      imageInfo.argsAddr = LOOP_argsAddr;
      imageInfo.argsSize = 50;

      status =
        PROC_load(processorId, (Char8 *) &imageInfo, numArgs, args);
    }
    else
#endif
    {
      status = PROC_load(processorId, dspExecutable, numArgs, args);
     
      LOOP_1Print("  'PROC_load' done, status 0x%x\n", status);
    }
  }

  /* Create a channel to DSP */
  if (DSP_SUCCEEDED(status)) {
    chnlAttrOutput.mode = ChannelMode_Output;
    chnlAttrOutput.endianism = Endianism_Default;
    chnlAttrOutput.size = ChannelDataSize_16bits;

    status = CHNL_create(processorId, CHNL_ID_OUTPUT, &chnlAttrOutput);

    LOOP_1Print("  'CHNL_create (1)' done, status 0x%x\n", status);
  }

  /* Create a channel from DSP */
  if (DSP_SUCCEEDED(status)) {
    chnlAttrInput.mode = ChannelMode_Input;
    chnlAttrInput.endianism = Endianism_Default;
    chnlAttrInput.size = ChannelDataSize_16bits;

    status = CHNL_create(processorId, CHNL_ID_INPUT, &chnlAttrInput);

    LOOP_1Print("  'CHNL_create (2)' done, status 0x%x\n", status);
  }

  /* Allocate buffer(s) for data transfer to DSP */
  if (DSP_SUCCEEDED(status)) {
    status = CHNL_allocateBuffer(processorId,
                                 CHNL_ID_OUTPUT,
                                 LOOP_Buffers,
                                 LOOP_BufferSize,
                                 1);

    LOOP_1Print("  'CHNL_allocateBuffer' done, status 0x%x\n", status);
  }

  /* Now initialize the buffer with data. Make the buffer printable, i.e.
     interpret at a null terminated C-string for a visual validation */
  if (DSP_SUCCEEDED(status)) {
    temp = LOOP_Buffers[0];

    for (i = 0; i < LOOP_BufferSize - 1; i++) {
      *temp++ = XFER_INIT_CHAR;
    }

    *temp = '\0';
  }

  LOOP_1Print("'LOOP_Create' done, status 0x%x\n\n", status);
  return status;
}

/*******************************************************************************
  @func  LOOP_Execute
  @desc  This function implements the execute phase for this application
*******************************************************************************/

NORMAL_API DSP_STATUS LOOP_Execute(IN Uint32 numIterations,
                                   Uint8 processorId)
{
  DSP_STATUS status = DSP_SOK;
  Uint32 i;

  LOOP_0Print("Executing 'LOOP_Execute'\n");

  /* Start execution on DSP */
  status = PROC_start(processorId);

  LOOP_1Print("  'PROC_start' done, status 0x%x\n", status);

  /* Fill the IO Request structure. It gives Information for adding or
     reclaiming an input request */
  if (DSP_SUCCEEDED(status)) {
    LOOP_IOReq.buffer = LOOP_Buffers[0];
    LOOP_IOReq.size = LOOP_BufferSize;
  }

  for (i = 1;
       ((LOOP_NumIterations == 0) || (i <= LOOP_NumIterations))
       && (DSP_SUCCEEDED(status));
       i++)
  {
    LOOP_1Print("Iteration %d\n", i);

    /* Send data to DSP and issue 'filled' buffer to the channel */
    status = CHNL_issue(processorId, CHNL_ID_OUTPUT, &LOOP_IOReq);

    LOOP_1Print("  'CHNL_issue (1)' done, status 0x%x\n", status);

    /* Reclaim 'empty' buffer from the channel */
    if (DSP_SUCCEEDED(status)) {
      status = CHNL_reclaim(processorId,
                            CHNL_ID_OUTPUT,
                            WAIT_FOREVER,
                            &LOOP_IOReq);

      LOOP_1Print("  'CHNL_reclaim' done, status 0x%x\n", status);
    }

    /* Receive data from DSP, issue 'empty' buffer to the channel */
    if (DSP_SUCCEEDED(status)) {
      status = CHNL_issue(processorId, CHNL_ID_INPUT, &LOOP_IOReq);

      LOOP_1Print("  'CHNL_issue (2)' done, status 0x%x\n", status);
    }

    /* Reclaim 'filled' buffer from the channel */
    if (DSP_SUCCEEDED(status)) {
      status = CHNL_reclaim(processorId,
                            CHNL_ID_INPUT,
                            WAIT_FOREVER,
                            &LOOP_IOReq);

      LOOP_1Print("  'CHNL_reclaim (2)' done, status 0x%x\n", status);
    }

#if defined (VERIFY_DATA)
    /* Verify correctness of data received */
    if (DSP_SUCCEEDED(status)) {
      status = LOOP_VerifyData(LOOP_IOReq.buffer);

      LOOP_1Print("  'LOOP_VerifyData' done, status 0x%x\n", status);

      if (DSP_FAILED(status)) {
        LOOP_0Print("  FAIL: data integrity failed\n");
      }
    }
#endif

  }

  LOOP_1Print("'LOOP_Execute' done, status 0x%x\n\n", status);
  return status;
}

/*******************************************************************************
  @func  LOOP_Delete
  @desc  This function releases resources allocated earlier by call to
         LOOP_Create ().

         During cleanup, the allocated resources are being freed
         unconditionally. Actual applications may require stricter check
         against return values for robustness

         NOTE, some of the functions return status codes different from
         the generic 0x8000 to still indicate success. Check the codes
         defined in 'gpp/src/inc/usr/errbase.h'
*******************************************************************************/

NORMAL_API Void LOOP_Delete(Uint8 processorId)
{
  DSP_STATUS status = DSP_SOK;
  DSP_STATUS tmpStatus = DSP_SOK;

  LOOP_0Print("Executing 'LOOP_Delete'\n");

  /* Free the buffer(s) allocated for channel to DSP */
  tmpStatus = CHNL_freeBuffer(processorId,
                              CHNL_ID_OUTPUT,
                              LOOP_Buffers,
                              1);

  LOOP_1Print("  'CHNL_freeBuffer' done, status 0x%x\n", tmpStatus);

  /* Delete both input and output channels */
  tmpStatus = CHNL_delete(processorId, CHNL_ID_INPUT);

  LOOP_1Print("  'CHNL_delete (1)' done, status 0x%x\n", tmpStatus);

  tmpStatus = CHNL_delete(processorId, CHNL_ID_OUTPUT);

  LOOP_1Print("  'CHNL_delete (2)' done, status 0x%x\n", tmpStatus);

  /* Stop execution on DSP */
  status = PROC_stop(processorId);

  LOOP_1Print("  'PROC_stop' done, status 0x%x\n", status);

  /* Close the pool */
  tmpStatus = POOL_close(POOL_makePoolId(processorId, POOL_ID));

  LOOP_1Print("  'POOL_close' done, status 0x%x\n", tmpStatus);

  /* Detach from the processor */
  tmpStatus = PROC_detach(processorId);

  LOOP_1Print("  'PROC_detach' done, status 0x%x\n", tmpStatus);

  /* Destroy the PROC object */
  tmpStatus = PROC_destroy();

  LOOP_1Print("  'PROC_destroy' done, status 0x%x\n", tmpStatus);
  LOOP_1Print("'LOOP_Delete' done, status 0x%x\n\n", status);
}

/*******************************************************************************
  @func  LOOP_Main
  @desc  Entry point for the application
*******************************************************************************/

NORMAL_API Void LOOP_Main(IN Char8 *dspExecutable,
                          IN Char8 *strBufferSize,
                          IN Char8 *strNumIterations,
                          IN Char8 *strProcessorId)
{
  DSP_STATUS status = DSP_SOK;
  Uint8 processorId = 0;

  LOOP_0Print("=========== Sample DSP Application : LOOP ==========\n");

  if ((dspExecutable != NULL)
  && (strBufferSize != NULL)
  && (strNumIterations != NULL))
  {
    /* Validate the buffer size and number of iterations specified */
    LOOP_BufferSize = DSPLINK_ALIGN(LOOP_Atoi(strBufferSize),
                                    DSPLINK_BUF_ALIGN);

    LOOP_1Print ("LOOP_BufferSize: %d\n", LOOP_BufferSize);

    if (LOOP_BufferSize == 0) {
      status = DSP_ESIZE;
    }

    LOOP_NumIterations = LOOP_Atoi(strNumIterations);
    LOOP_1Print ("LOOP_NumIterations: %d\n\n", LOOP_NumIterations);

    /* Find out the processor id to work with */
    processorId = LOOP_Atoi(strProcessorId);

    if (processorId >= MAX_DSPS) {
      LOOP_1Print ("*** error: invalid processor id specified (%d)\n",
                   processorId);

      status = DSP_EFAIL;
    }

    /* Specify the dsp executable file name and the buffer size for
       the loop creation phase */
    if (DSP_SUCCEEDED (status)) {
      status = LOOP_Create(dspExecutable,
                           strBufferSize,
                           strNumIterations,
                           processorId);

      /* Execute the data transfer loop */
      if (DSP_SUCCEEDED(status)) {
        status = LOOP_Execute(LOOP_NumIterations, processorId);
      }

      /* Perform cleanup operation */
      LOOP_Delete(processorId);
    }
  }
  else {
    status = DSP_EINVALIDARG;
 
    LOOP_0Print("*** error: invalid arguments specified for the LOOP "
                "application\n");
  }

  LOOP_0Print("====================================================\n");
}

#if defined (VERIFY_DATA)

/*******************************************************************************
  @func  LOOP_VerifyData
  @desc  This function interprets the content of the given buffer as a
         C-string and prints it for a visual validation
*******************************************************************************/

STATIC NORMAL_API DSP_STATUS LOOP_VerifyData(IN Char8 *buf)
{
  if (buf[LOOP_BufferSize - 1] != '\0') return DSP_EFAIL;
  else {
    LOOP_1Print("buffer: %s", (Uint32) buf);
    return DSP_SOK;
  }
}

#endif

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
