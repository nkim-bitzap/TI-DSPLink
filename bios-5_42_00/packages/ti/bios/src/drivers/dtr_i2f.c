/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *  @(#) DSP/BIOS_Kernel 5,2,5,44 09-06-2012 (cuda-u44)
 */
/*
 *  ======== dtr_i2f.c ========
 *  Spectron-supplied "user" function for DTR.
 *
 *  Note: For the purpose of transforming fixed point data to floating point,
 *  this function assumes that sizeof(Float) == sizeof(Int)!  Of course,
 *  for the C30/C40 this is ok, but ...
 *
 */

#include <std.h>
#include <stddef.h>

#include <dtr.h>

/*
 *  ======== DTR_fix2flt ========
 *
 *  This transformation converts integer data to floating point data.
 *
 *  *addr = (Float)(*addr * scale)
 */
Void DTR_fix2flt(Arg arg, DTR_Elem *addr, size_t size)
{
    register size_t     i;              
    register Int        *iptr;
    register Float      *fptr;
    register DTR_Scale  scale;
    
    scale = *(DTR_Scale *)arg;
    fptr = (Float *)addr;
    iptr = (Int *)addr;

    for (i = (size / sizeof(Float)); i > 0; i--) {
        *fptr++ = ((Float)*iptr++) * scale;
    }
}

