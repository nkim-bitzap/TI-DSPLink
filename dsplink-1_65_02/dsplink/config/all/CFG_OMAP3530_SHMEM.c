/** ============================================================================
 *  @file   CFG_OMAP3530_SHMEM.c
 *
 *  @path   $(DSPLINK)/config/all/
 *
 *  @desc   Defines the configuration information for DSP/BIOS LINK for the
 *          OMAP platform.
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

/* DSP/BIOS LINK Headers */
#include <dsplink.h>
#include <procdefs.h>

#if defined (__cplusplus)
EXTERN "C" {
#endif /* defined (__cplusplus) */

/*******************************************************************************
  @desc NKim, to provide more memory to the DSP, the default memory layout
        has been changed. Now, 128 MB are assigned to the DSP with the
        code/data segment being put after the POOL buffer memory. This
        allows a DSP program to use (almost) 128 MB, if necessary. I
        might change this later, since 128 MB really looks like overkill
        to me.

  @note The memory map configuration provided here does not have any effect
        on the DSP, which is configured separately. In case of 'OMAP3530'
        and 'DspBios 5.xx' we need to edit 'dsp/inc/DspBios/5.XX/OMAP3530'
        according to the changes done here.

                DSPLINK MEMORY SECTION DIAGRAM (ALTERNATIVE)

       |--------------[ 0xXXXXXX00 ]---------------------------------|
       |                                                             |
       |                   DSPLINK SHARED MEMORY0                    |
       |             Shared control structure is loaded here         |
       |                                                             |
       |-------------------------------------------------------------|
       |                                                             |
       |                   DSPLINK SHARED MEMORY1                    |
       |             Shared control structure is loaded here         |
       |                                                             |
       |-------------------------------------------------------------|
       |                                                             |
       |                   POOL Buffer Memory                        |
       |             Pool's buffers are created in this area         |
       |                                                             |
       |-------------------------------------------------------------|
       |                                                             |
       |                   RESET VECTOR (0x80)                       |
       |             Last two nibbles must be zero                   |
       |                                                             |
       |-------------------------------------------------------------|
       |                                                             |
       |                   DSP CODE/DATA                             |
       |            DSP executable is loaded to this section         |
       |            Contiguous with the RESET VECTOR region          |
       |                                                             |
       |=============================================================|

  @desc NKim, given the total memory of 256 MB available on the target
        (BeagleBoard C4), we reserve 128 MB for the exclusive use by the
        DSP. The remaining 128 MB are assigned to the GPP side with the
        kernel being explicitly aware of that boundary.

        According to various sources, the last address possible on the
        target is 0x90000000. Therefore:

        0x90000000 (address space top) - 0x8000000 (128 MB GPP memory)
          = 0x88000000 (DSP address space start)

*******************************************************************************/

/*******************************************************************************
  @name   DRVHANDSHAKEPOLLCOUNT

  @desc   POLL Count for Driver handshake
*******************************************************************************/

#define  DRVHANDSHAKEPOLLCOUNT ((Uint32) 0xFFFFFFF)

/*******************************************************************************
  @name   SHAREDENTRYID/SHAREDMEMORYADDR/SHAREDMEMORYSIZE

  @desc   Indicates start address/size for dsplink shared memory region 1

  @desc NKim, given the partitioning explained above, the start address
        for the shared memory area 1 equals 0x88000000
*******************************************************************************/

#define  SHAREDENTRYID0    0
#define  SHAREDMEMORYADDR0 0x88000000
#define  SHAREDMEMORYSIZE0 0x5000

/*******************************************************************************
  @name SHAREDENTRYID/SHAREDMEMORYADDR/SHAREDMEMORYSIZE

  @desc Indicates start address/size for dsplink shared memory region 2

  @note NKim, given the partitioning explained above, the start address
        for the shared memory area 2 equals 0x88005000
*******************************************************************************/

#define  SHAREDENTRYID1    1
#define  SHAREDMEMORYADDR1 (SHAREDMEMORYADDR0 + SHAREDMEMORYSIZE0)
#define  SHAREDMEMORYSIZE1 0x2B000

/*******************************************************************************
  @name POOLMEMORYADDR/POOLMEMORYSIZE

  @desc Indicates startaddress/size for dsplink POOL memory region

  @note NKim, given the partitioning explained above, the start address
        for the pool memory region equals 0x88030000
*******************************************************************************/

#define  POOLENTRYID    2
#define  POOLMEMORYADDR (SHAREDMEMORYADDR1 + SHAREDMEMORYSIZE1)
#define  POOLMEMORYSIZE 0x000D0000

/*******************************************************************************
  @name RESETCTRLADDR

  @desc Indicates the start address of Reset Ctrl memory region

  @note The last two nibbles must be zero i.e. align to 256 boundary.
        The start address equals 0x88100000 in our scheme
*******************************************************************************/

#define RSTENTRYID    3
#define RESETCTRLADDR (POOLMEMORYADDR + POOLMEMORYSIZE)
#define RESETCTRLSIZE 0x80

/*******************************************************************************
  @name CODEMEMORYADDR/CODEMEMORYSIZE

  @desc Indicates startaddress/size for dsplink code region

  @note NKim, given the partitioning explained above, the start address
        for the code/data region equals 0x88100080. This segment now
        occupies the rest of the remaining DSP memory (roughly 127 MB)
*******************************************************************************/

#define CODEENTRYID    4
#define CODEMEMORYADDR (RESETCTRLADDR + RESETCTRLSIZE)
#define CODEMEMORYSIZE 0x7EFFF80

/*******************************************************************************
  @name  LINKCFG_memTable_00
  @desc  Memory table entries
*******************************************************************************/

STATIC LINKCFG_MemEntry  LINKCFG_memTable_00[] =
{
  {
    SHAREDENTRYID0,     /* ENTRY        : Entry number */
    "DSPLINKMEM",       /* NAME         : Name of the memory region */
    SHAREDMEMORYADDR0,  /* ADDRPHYS     : Physical address */
    SHAREDMEMORYADDR0,  /* ADDRDSPVIRT  : DSP virtual address */
    (Uint32) -1u,       /* ADDRGPPVIRT  : GPP virtual address (if known) */
    SHAREDMEMORYSIZE0,  /* SIZE         : Size of the memory region */
    TRUE,               /* SHARED       : Shared access memory? */
    FALSE,              /* SYNCD        : Synchronized? */
  },

  {
    SHAREDENTRYID1,     /* ENTRY        : Entry number */
    "DSPLINKMEM1",      /* NAME         : Name of the memory region */
    SHAREDMEMORYADDR1,  /* ADDRPHYS     : Physical address */
    SHAREDMEMORYADDR1,  /* ADDRDSPVIRT  : DSP virtual address */
    (Uint32) -1u,       /* ADDRGPPVIRT  : GPP virtual address (if known) */
    SHAREDMEMORYSIZE1,  /* SIZE         : Size of the memory region */
    TRUE,               /* SHARED       : Shared access memory? */
    FALSE,              /* SYNCD        : Synchronized? */
  },

  {
    POOLENTRYID,        /* ENTRY        : Entry number */
    "POOLMEM",          /* NAME         : Name of the memory region */
    POOLMEMORYADDR,     /* ADDRPHYS     : Physical address */
    POOLMEMORYADDR,     /* ADDRDSPVIRT  : DSP virtual address */
    (Uint32) -1u,       /* ADDRGPPVIRT  : GPP virtual address (if known) */
    POOLMEMORYSIZE,     /* SIZE         : Size of the memory region */
    TRUE,               /* SHARED       : Shared access memory? Logically */
    FALSE,              /* SYNCD        : Synchronized? */
  },

  {
    RSTENTRYID,         /* ENTRY        : Entry number */
    "RESETCTRL",        /* NAME         : Name of the memory region */
    RESETCTRLADDR,      /* ADDRPHYS     : Physical address */
    RESETCTRLADDR,      /* ADDRDSPVIRT  : DSP virtual address */
    (Uint32) -1u,       /* ADDRGPPVIRT  : GPP virtual address (if known) */
    RESETCTRLSIZE,      /* SIZE         : Size of the memory region */
    TRUE,               /* SHARED       : Shared access memory? */
    FALSE,              /* SYNCD        : Synchronized? */
  },

  {
    CODEENTRYID,        /* ENTRY        : Entry number */
    "DDR2",             /* NAME         : Name of the memory region */
    CODEMEMORYADDR,     /* ADDRPHYS     : Physical address */
    CODEMEMORYADDR,     /* ADDRDSPVIRT  : DSP virtual address */
    (Uint32) -1u,       /* ADDRGPPVIRT  : GPP virtual address (if known) */
    CODEMEMORYSIZE,     /* SIZE         : Size of the memory region */
    TRUE,               /* SHARED       : Shared access memory? */
    FALSE,              /* SYNCD        : Synchronized? */
  },

  {
    5,                  /* ENTRY        : Entry number */
    "DSPIRAM",          /* NAME         : Name of the memory region */
    0x5c7f8000,         /* ADDRPHYS     : Physical address */
    0x107f8000,         /* ADDRDSPVIRT  : DSP virtual address */
    (Uint32) -1u,       /* ADDRGPPVIRT  : GPP virtual address (if known) */
    0x00018000,         /* SIZE         : Size of the memory region */
    TRUE,               /* SHARED       : Shared access memory? */
    FALSE               /* SYNCD        : Synchronized? */
  },

  {
    6,                  /* ENTRY        : Entry number */
    "DSPL1PRAM",        /* NAME         : Name of the memory region */
    0x5cE00000,         /* ADDRPHYS     : Physical address */
    0x10E00000,         /* ADDRDSPVIRT  : DSP virtual address */
    (Uint32) -1u,       /* ADDRGPPVIRT  : GPP virtual address (if known) */
    0x00008000,         /* SIZE         : Size of the memory region */
    TRUE,               /* SHARED       : Shared access memory? */
    FALSE               /* SYNCD        : Synchronized? */
  },

  {
    7,                  /* ENTRY        : Entry number */
    "DSPL1DRAM",        /* NAME         : Name of the memory region */
    0x5cF04000,         /* ADDRPHYS     : Physical address */
    0x10F04000,         /* ADDRDSPVIRT  : DSP virtual address */
    (Uint32) -1,        /* ADDRGPPVIRT  : GPP virtual address (if known) */
    0x00014000,         /* SIZE         : Size of the memory region */
    TRUE,               /* SHARED       : Shared access memory? */
    FALSE               /* SYNCD        : Synchronized? */
  },

  {
    8,                  /* ENTRY        : Entry number */
    "L4_CORE",          /* NAME         : Name of the memory region */
    0x48000000,         /* ADDRPHYS     : Physical address */
    0x48000000,         /* ADDRDSPVIRT  : DSP virtual address */
    (Uint32) -1,        /* ADDRGPPVIRT  : GPP virtual address (if known) */
    0x01000000,         /* SIZE         : Size of the memory region */
    FALSE,              /* SHARED       : Shared access memory? */
    FALSE               /* SYNCD        : Synchronized? */
  },

  {
    9,                  /* ENTRY        : Entry number */
    "L4_PER",           /* NAME         : Name of the memory region */
    0x49000000,         /* ADDRPHYS     : Physical address */
    0x49000000,         /* ADDRDSPVIRT  : DSP virtual address */
    (Uint32) -1,        /* ADDRGPPVIRT  : GPP virtual address (if known) */
    0x00100000,         /* SIZE         : Size of the memory region */
    FALSE,              /* SHARED       : Shared access memory? */
    FALSE               /* SYNCD        : Synchronized? */
  }
};

/*******************************************************************************
  @name  LINKCFG_memTables
  @desc  Array of memory tables in the system
*******************************************************************************/

STATIC LINKCFG_MemEntry *LINKCFG_memTables[] = { LINKCFG_memTable_00 };

/*******************************************************************************
  @name  LINKCFG_ipsTable_00
  @desc  IPS table ID 0
*******************************************************************************/

STATIC LINKCFG_Ips LINKCFG_ipsTable_00[] =
{
  {
    /* NAME: Name of the Inter-Processor-Signaling component */
    "IPS",

    /* NUMIPSEVENTS: Number of IPS events to be supported */
    (Uint32) 32,

    /* MEMENTRY: Memory entry ID (-1 if not needed) */
    SHAREDENTRYID0,

    /* GPPINTID: Interrupt no. to used by the IPS on GPP-side.
       (-1 if uni-directional to DSP) */
    (Uint32) 26,

    /* DSPINTID: Interrupt no. to used by the IPS on DSP-side.
       (-1 if uni-directional to GPP) */
    (Uint32) 55,

    /* DSPINTVECTORID: Interrupt vector no. to used by the IPS on DSP-side.
       (-1 if uni-directional to GPP) */
    (Uint32) 5,

     /* ARGUMENT1: Poll value for which IPS waits while sending 
        event (-1 if infinite) */
    (Uint32) 50000000,

    /* ARGUMENT2: Second IPS-specific argument */
    0
  }
};

/*******************************************************************************
  @name  LINKCFG_ipsTables
  @desc  Array of IPS tables in the system
*******************************************************************************/

STATIC LINKCFG_Ips *LINKCFG_ipsTables[] = { LINKCFG_ipsTable_00 };

/*******************************************************************************
  @name  LINKCFG_poolTable_00
  @desc  Pool table ID 0
*******************************************************************************/

STATIC LINKCFG_Pool LINKCFG_poolTable_00[] =
{
  {
    "SMAPOOL",               /* NAME: Name of the pool */
    SHAREDENTRYID1,          /* MEMENTRY: Memory entry ID (-1 if not needed) */
    (Uint32) POOLMEMORYSIZE, /* POOLSIZE: Size of the pool (-1 if not needed) */
    (Uint32) -1,             /* IPSID: ID of the IPS used */
    (Uint32) -1,             /* IPSEVENTNO: IPS Event num. associated with POOL */
    POOLENTRYID,             /* POOLMEMENTRY: Pool memory region section ID  */
    0x0,                     /* ARGUMENT1: First Pool-specific argument */
    0x0                      /* ARGUMENT2: Second Pool-specific argument */
  }
};

/*******************************************************************************
  @name  LINKCFG_poolTables
  @desc  Array of Pool tables in the system
*******************************************************************************/

STATIC LINKCFG_Pool *LINKCFG_poolTables[] = { LINKCFG_poolTable_00 };

/*******************************************************************************
  @name  LINKCFG_dataTable_00
  @desc  Data driver table ID 0
*******************************************************************************/

STATIC LINKCFG_DataDrv LINKCFG_dataTable_00[] =
{
  {
    "ZCPYDATA",      /* NAME: Name of the data driver */
    0,               /* BASECHANNELID: Base channel ID for the driver */
    16,              /* NUMCHANNELS: Number of channels supported */
    16384,           /* MAXBUFSIZE: Maximum size of buffer (-1 if no limit) */
    SHAREDENTRYID1,  /* MEMENTRY: Memory entry ID (-1 if not needed) */
    0,               /* POOLID: Pool id for allocating buffers */
    1,               /* QUEUELENGTH: Queue length for the data driver */
    0,               /* IPSID: ID of the IPS used */
    1,               /* IPSEVENTNO: IPS Event num. associated with data Driver */
    0x0,             /* ARGUMENT1: First data driver specific argument */
    0x0              /* ARGUMENT2: Second data driver specific argument */
  }
};

/*******************************************************************************
  @name   LINKCFG_dataTables
  @desc   Array of Data driver tables in the system
*******************************************************************************/

STATIC LINKCFG_DataDrv *LINKCFG_dataTables[] = { LINKCFG_dataTable_00 };

/*******************************************************************************
  @name  LINKCFG_mqtObjects
  @desc  Array of Message Queue Transport objects in the system
*******************************************************************************/

STATIC LINKCFG_Mqt LINKCFG_mqtObjects[] =
{
  {
    "ZCPYMQT",       /* NAME: Name of the Message Queue Transport */
    SHAREDENTRYID1,  /* MEMENTRY: Memory entry ID (-1 if not needed) */
    (Uint32) -1,     /* MAXMSGSIZE: Maximum message size (-1 if no limit) */
    0,               /* IPSID: ID of the IPS used */
    0,               /* IPSEVENTNO: IPS Event number associated with MQT */
    0x0,             /* ARGUMENT1: First MQT-specific argument */
    0x0              /* ARGUMENT2: Second MQT-specific argument */
  }
};

/*******************************************************************************
  @name  LINKCFG_ringIoObjects
  @desc  Array of RINGIO objects in the system
*******************************************************************************/

STATIC LINKCFG_RingIo LINKCFG_ringIoObjects[] =
{
  {
    "RINGIOTABLE",   /* NAME: Name of the RingIO Table */
    SHAREDENTRYID0,  /* MEMENTRY: Memory entry ID (-1 if not needed) */
    64,              /* NUMENTRIES: Number of RingIO entries supported */
    0,               /* IPSID: ID of the IPS used */
    2                /* IPSEVENTNO: IPS Event number associated with RingIO */
  }
};

/*******************************************************************************
  @name  LINKCFG_mplistObjects
  @desc  Array of MPLIST objects in the system
*******************************************************************************/

STATIC LINKCFG_MpList LINKCFG_mplistObjects[] =
{
  {
    "MPLISTTABLE",   /* NAME: Name of the MpList Table */
    SHAREDENTRYID1,  /* MEMENTRY: Memory entry ID (-1 if not needed) */
    64,              /* NUMENTRIES: Number of MpList entries supported */
    (Uint32) -1,     /* IPSID: ID of the IPS used */
    (Uint32) -1      /* IPSEVENTNO: IPS Event number associated with MpList */
  }
};

/*******************************************************************************
  @name  LINKCFG_mpcsObjects
  @desc  Array of MPCS objects in the system
*******************************************************************************/

STATIC LINKCFG_Mpcs LINKCFG_mpcsObjects[] =
{
  {
    "MPCS",          /* NAME: Name of the MPCS Table */
    SHAREDENTRYID1,  /* MEMENTRY: Memory entry ID (-1 if not needed) */
    256,             /* NUMENTRIES: Number of MPCS entries supported */
    (Uint32) -1,     /* IPSID: ID of the IPS used */
    (Uint32) -1      /* IPSEVENTNO: IPS Event number associated with MPCS */
  }
};

/*******************************************************************************
  @name  LINKCFG_logObject
  @desc  Configuration object for the GPP.
*******************************************************************************/

STATIC LINKCFG_Log LINKCFG_logObject =
{
  FALSE,  /* GDMSGQPUT         : GPP->DSP MSG - MSGQ_put call */
  FALSE,  /* GDMSGQSENDINT     : GPP->DSP MSG - GPP sends interrupt */
  FALSE,  /* GDMSGQISR         : GPP->DSP MSG - DSP receives interrupt */
  FALSE,  /* GDMSGQQUE         : GPP->DSP MSG - Message queued at DSP */
  FALSE,  /* DGMSGQPUT         : DSP->GPP MSG - MSGQ_put call */
  FALSE,  /* DGMSGQSENDINT     : DSP->GPP MSG - DSP sends interrupt */
  FALSE,  /* DGMSGQISR         : DSP->GPP MSG - GPP receives interrupt */
  FALSE,  /* DGMSGQQUE         : DSP->GPP MSG - Message queued at GPP */
  FALSE,  /* GDCHNLISSUESTART  : GPP->DSP CHNL - Entering inside ISSUE call */
  FALSE,  /* GDCHNLISSUEQUE    : GPP->DSP CHNL - ISSUE: Buffer is queued on GPP */
  FALSE,  /* GDCHNLISSUECOMPL  : GPP->DSP CHNL - ISSUE call completed */
  FALSE,  /* GDCHNLXFERSTART   : GPP->DSP CHNL - Initiate buffer transfer by GPP */
  FALSE,  /* GDCHNLXFERPROCESS : GPP->DSP CHNL - Buffer transfer takes place */
  FALSE,  /* GDCHNLXFERCOMPL   : GPP->DSP CHNL - Buffer transfer is complete */
  FALSE,  /* GDCHNLRECLSTART   : GPP->DSP CHNL - Entering RECLAIM call */
  FALSE,  /* GDCHNLRECLPEND    : GPP->DSP CHNL - RECLAIM: Wait on a semaphore */
  FALSE,  /* GDCHNLRECLPOST    : GPP->DSP CHNL - RECLAIM: Posting the Semaphore */
  FALSE,  /* GDCHNLRECLCOMPL   : GPP->DSP CHNL - RECLAIM call completed */
  FALSE,  /* DGCHNLISSUEQUE    : DSP->GPP CHNL - ISSUE: Buffer is queued on DPS */
  FALSE,  /* DGCHNLXFERSTART   : DSP->GPP CHNL - Initiate buffer transfer by DSP */
  FALSE,  /* DGCHNLXFERPROCESS : DSP->GPP CHNL - Buffer transfer takes place */
  FALSE,  /* DGCHNLXFERCOMPL   : DSP->GPP CHNL - Buffer transfer is complete */
  FALSE,  /* DGCHNLRECLPEND    : DSP->GPP CHNL - RECLAIM: Wait on a semaphore */
  FALSE,  /* DGCHNLRECLPOST    : DSP->GPP CHNL - RECLAIM: Posting the Semaphore */
  10,     /* MSGIDRANGESTART   : MSG ID range: lower limit */
  20      /* MSGIDRANGEEND     : MSG ID range: upper limit */
};

/*******************************************************************************
  @name  LINKCFG_linkDrvObjects
  @desc  Array of Link driver objects in the system.
*******************************************************************************/

STATIC LINKCFG_LinkDrv LINKCFG_linkDrvObjects[] =
{
  {
    /* NAME : Name of the link driver */
    "SHMDRV",

    /* HSHKPOLLCOUNT : Poll value for which handshake waits (-1 = infinite) */
    DRVHANDSHAKEPOLLCOUNT,

    /* MEMENTRY : Memory entry ID (-1 if not needed) */
    (Uint32) SHAREDENTRYID1,

    /* IPSTABLEID : ID of the IPS table used */
    0,

    /* IPSENTRIES : Number of IPS supported */
    sizeof (LINKCFG_ipsTable_00) / sizeof (LINKCFG_Ips),

    /* POOLTABLEID : ID of the POOL table */
    0,

    /* NUMPOOLS : Number of POOLs supported */
    sizeof (LINKCFG_poolTable_00) / sizeof (LINKCFG_Pool),

    /* DATATABLEID : ID of the data driver table */
    0,

    /* NUMDATADRV : Number of data drivers supported */
    sizeof (LINKCFG_dataTable_00) / sizeof (LINKCFG_DataDrv),

    /* MQTID : ID of the MQT */
    0,

    /* RINGIOTABLEID : RingIO Table Id used for this DSP */
    0,

    /* MPLISTTABLEID : MpList Table Id used for this DSP */
    0,

    /* MPCSTABLEID : MPCS Table ID used for this DSP */
    0
  }
};

/*******************************************************************************
  @name  LINKCFG_dspObjects
  @desc  Array of configuration objects for the DSPs in the system
*******************************************************************************/

#define NUM_MEM_TBL0_ENTRIES \
  sizeof (LINKCFG_memTable_00)/sizeof (LINKCFG_MemEntry)

STATIC LINKCFG_Dsp LINKCFG_dspObject =
{
  "OMAP3530",              /* NAME          : Name of the DSP */
  DspArch_C64x,            /* ARCHITECTURE  : DSP architecture */
  "COFF",                  /* LOADERNAME    : Name of the DSP executable loader */
  FALSE,                   /* AUTOSTART     : Autostart the DSP (Not supported) */
  "DEFAULT.OUT",           /* EXECUTABLE    : Executable for autostart */
  DSP_BootMode_Boot_NoPwr, /* DODSPCTRL     : Link boot dependent DSP control */
  RESETCTRLADDR,           /* RESUMEADDR    : Resume address */
  RESETCTRLADDR,           /* RESETVECTOR   : Reset Vector for the DSP */
  RESETCTRLSIZE,           /* RESETCODESIZE : Size of code at DSP Reset Vector */
  1,                       /* MADUSIZE      : DSP Minimum Addressable Data Unit */
  -1,                      /* CPUFREQ       : DSP Frequency (in KHz) */
  Endianism_Little,        /* ENDIAN        : DSP Endianism */
  FALSE,                   /* WORDSWAP      : Swap words when writing to memory */
  0,                       /* MEMTABLEID    : ID of the memory table used */
  NUM_MEM_TBL0_ENTRIES,    /* MEMENTRIES    : Number of entries in memory table */
  0,                       /* LINKDRVID     : ID of the link driver used */
  -1,                      /* ARG1          : Bus No of PCI card */
  -1,                      /* ARG2          : Slot No of PCI card */
  0,                       /* ARG3          : Shared memory interface */
  0,                       /* ARG4          : Physical interface 1-pci 2-vlynq*/
  (Uint32) -1l             /* ARG5          : EDMA channel number (OMAP unused) */
};

/*******************************************************************************
  @name  OMAP3530_SHMEM_Config
  @desc  DSP/BIOS LINK configuration structure
*******************************************************************************/

LINKCFG_DspConfig OMAP3530_SHMEM_Config =
{
  /* DSPOBJECTS : Array of DSP objects */
  (LINKCFG_Dsp *) &LINKCFG_dspObject,

  /* NUMLINKDRVS : Number of Link Drivers */
  sizeof (LINKCFG_linkDrvObjects)/sizeof (LINKCFG_LinkDrv),

  /* LINKDRVOBJECTS : Array of Link Driver objects */
  (LINKCFG_LinkDrv *) LINKCFG_linkDrvObjects,

  /* NUMMEMTABLES : Number of memory tables */
  sizeof (LINKCFG_memTables)/sizeof (LINKCFG_MemEntry *),

  /* MEMTABLES : Array of Memory tables */
  (LINKCFG_MemEntry **) LINKCFG_memTables,
  
  /* NUMIPSTABLES : Number of IPS tables */
  sizeof (LINKCFG_ipsTables)/sizeof (LINKCFG_Ips *),

  /* IPSTABLES : Array of IPS tables */
  (LINKCFG_Ips **) LINKCFG_ipsTables,

  /* NUMPOOLTABLES : Number of POOL tables */
  sizeof (LINKCFG_poolTables)/sizeof (LINKCFG_Pool *),

  /* POOLTABLES : Array of Pool tables */
  (LINKCFG_Pool **) LINKCFG_poolTables,

  /* NUMDATATABLES : Number of data tables */
  sizeof (LINKCFG_dataTables)/sizeof (LINKCFG_DataDrv *),

  /* DATATABLES : Array of data tables */
  (LINKCFG_DataDrv **) LINKCFG_dataTables,

  /* NUMMQTS : Number of MQTs */
  sizeof (LINKCFG_mqtObjects)/sizeof (LINKCFG_Mqt),

  /* MQTOBJECTS : Array of MQT objects */
  (LINKCFG_Mqt *) LINKCFG_mqtObjects,

  /* NUMRINGIOTABLES : Number of RINGIO tables */
  sizeof (LINKCFG_ringIoObjects)/sizeof (LINKCFG_RingIo),

  /* RINGIOOBJECTS : Array of RINGIO objects */
  (LINKCFG_RingIo *) LINKCFG_ringIoObjects,

  /* NUMMPLISTTABLES : Number of MPLIST tables */
  sizeof (LINKCFG_mplistObjects)/sizeof (LINKCFG_MpList),

  /* MPLISTOBJECTS : Array of MPLIST objects */
  (LINKCFG_MpList *) LINKCFG_mplistObjects,

  /* NUMMPCSTABLES : Number of MPCS tables */
  sizeof (LINKCFG_mpcsObjects)/sizeof (LINKCFG_Mpcs),

  /* MPCSOBJECTS : Array of MPCS objects */
  (LINKCFG_Mpcs *) LINKCFG_mpcsObjects,

  /* LOGOBJECT : Pointer to LOG object */
  (LINKCFG_Log *) &LINKCFG_logObject
};

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

