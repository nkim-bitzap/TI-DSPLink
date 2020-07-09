/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) PSL 5,1,0 09-24-2007 (psl-c03)
 */
/*
 *  ======== lnkx.cmd ========
 *
 */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
 PAGE 0:  /* ---- Unified Program/Data Address Space ---- */
  
  /* On-chip Dual Access RAM, divided into 4 blocks of 16K bytes: */
  /* 0-3FFF, 4000-7FFF, 8000-CFFF, D000-FFFF */
  
  INT_VECS (RIX)  : origin = 0x200, length = 0x000100  /* 256-byte int vector */
  
  DARAM       (RWX ): o= 0x00300 l= 0x0FD00
  
  /* On-chip Single Access RAM, divided into 16 blocks of 16K bytes: */
  /* 10000-13FFF, 14000-17FFF, 18000-1CFFF, 1D000-1FFFF */
  /* 20000-23FFF, 24000-27FFF, 28000-2CFFF, 2D000-2FFFF */
  /* 30000-33FFF, 34000-37FFF, 38000-3CFFF, 3D000-3FFFF */
  /* 40000-43FFF, 44000-47FFF, 48000-4CFFF, 4D000-4FFFF */
  SARAM       (RWX ): o= 0x010004 l = 0x3BF5C  

  /* 1Mb off-chip Synchronous Burst Static RAM */
  SBSRAM      (RWX ): o= 0x050000 l= 0x100000

  VECS (RIX)  : origin = 0xffff00, length = 0x000100  /* 256-byte int reset vector */

 PAGE 2:  /* -------- 64K-word I/O Address Space -------- */

  IOPORT (RWI) : origin = 0x000000, length = 0x020000
}


/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
   .vectors > INT_VECS  PAGE 0                      /* Hardware reset vector */
   
   .text     > SARAM    PAGE 0  /* Code                     */

   /* These sections must be on same physical memory page   */
   /* when small memory model is used                       */
   .data     > DARAM    PAGE 0  /* Initialized vars           */
   .bss      > DARAM    PAGE 0  /* Global & static vars       */
   .const    > DARAM    PAGE 0  /* Constant data              */
   .sysmem   > DARAM    PAGE 0  /* Dynamic memory (malloc)    */
   .stack    > DARAM    PAGE 0  /* Primary system stack       */
   .sysstack > DARAM    PAGE 0  /* Secondary system stack     */
   .cio      > DARAM    PAGE 0  /* C I/O buffers              */

   /* These sections may be on any physical memory page     */
   /* when small memory model is used                       */
   .switch   > DARAM    PAGE 0  /* Switch statement tables    */
   .cinit    > DARAM    PAGE 0  /* Auto-initialization tables */
   .pinit    > DARAM    PAGE 0  /* Initialization fn tables   */

   .ioport   > IOPORT PAGE 2    /* Global & static IO vars    */
}

/* configure stacks and heap sizes */
-stack    0x0500
-sysstack 0x1000
-heap     0x0500
