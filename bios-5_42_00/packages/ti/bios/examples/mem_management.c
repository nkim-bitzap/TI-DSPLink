/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Examples 5,4,1 02-08-2010 (biosEx-j14)
 */
/*
 *  ======== mem_management.c ========
 *  This program allocates and frees memory from
 *  different memory segments.
 */
 
#include <std.h>

#include <log.h>
#include <mem.h>

#include "mem_managementcfg.h"


#define NALLOCS 2       /* # of allocations from each segment */
#define BUFSIZE 128     /* size of allocations */

extern Int SEG0;

static Void printmem(Int segid);

/*
 *  ======== main ========
 */
Void main()
{
    LOG_printf(&trace, "mem_management example started.\n");
}

/*
 *  ======== initTask ========
 */
Void initTask()
{
    Int i;
    Ptr ram[NALLOCS];

    LOG_printf(&trace, "before allocating ...");

    /* print initial memory status */
    printmem(SEG0);

    LOG_printf(&trace, "allocating memory blocks in seg%d ...", SEG0);

    /* allocate some memory from each segment */
    for (i = 0; i < NALLOCS; i++) {
        ram[i] = MEM_alloc(SEG0, BUFSIZE, 0);

        LOG_printf(&trace, "memory block %d allocated at address = %p", i, ram[i]);
    }

    LOG_printf(&trace, "after allocating ...");

    /* print memory status */
    printmem(SEG0);

    /* free memory */
    for (i = 0; i < NALLOCS; i++) {
        MEM_free(SEG0, ram[i], BUFSIZE);
    }

    LOG_printf(&trace, "after freeing ...");

    /* print memory status */
    printmem(SEG0);

    LOG_printf(&trace, "Test Complete");
}

/*
 *  ======== printmem ========
 */
static Void printmem(Int segid)
{
    MEM_Stat    statbuf;

    MEM_stat(segid, &statbuf);

    LOG_printf(&trace, "seg%d: segment size 0x%x", segid, (Int)statbuf.size);
    LOG_printf(&trace, "\tnumber of MADUs used in seg%d: 0x%x", segid, (Int)statbuf.used);
    LOG_printf(&trace, "\tsize of the largest free contiguous block of memory in seg%d:\tA 0x%x", segid, (Int)statbuf.length);
    
}
