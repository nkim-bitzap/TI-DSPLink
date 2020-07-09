/****************************************************************************/
/*  ATEXIT.C v7.3.23                                                        */
/*                                                                          */
/* Copyright (c) 1995-2015 Texas Instruments Incorporated                   */
/* http://www.ti.com/                                                       */
/*                                                                          */
/*  Redistribution and  use in source  and binary forms, with  or without   */
/*  modification,  are permitted provided  that the  following conditions   */
/*  are met:                                                                */
/*                                                                          */
/*     Redistributions  of source  code must  retain the  above copyright   */
/*     notice, this list of conditions and the following disclaimer.        */
/*                                                                          */
/*     Redistributions in binary form  must reproduce the above copyright   */
/*     notice, this  list of conditions  and the following  disclaimer in   */
/*     the  documentation  and/or   other  materials  provided  with  the   */
/*     distribution.                                                        */
/*                                                                          */
/*     Neither the  name of Texas Instruments Incorporated  nor the names   */
/*     of its  contributors may  be used to  endorse or  promote products   */
/*     derived  from   this  software  without   specific  prior  written   */
/*     permission.                                                          */
/*                                                                          */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS   */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT   */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT   */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT   */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    */
/*                                                                          */
/****************************************************************************/
#include <stdlib.h>
#include <_lock.h>

#if !defined(__TI_EABI_SUPPORT__) && !defined(__TI_EABI__)
/****************************************************************************/
/* __ATEXIT_FUNC_ID__ IS USED AS AN IDENTIFIER TO DISTINGUISH IF A DTOR_LIST*/
/* RECORDS A ATEXIT FUNCTION.                                               */
/****************************************************************************/
_DATA_ACCESS int __atexit_func_id__ = 0x1234;

#include "_dtor_list.h"
extern void __add_dtor(DTOR_LIST *dtor_entry);

/****************************************************************************/
/* STATICALLY ALLOCATE MEMORY FOR ATEXIT FUNCTION REGISTRATION (CQ20012)    */
/****************************************************************************/
#define MAX_ATEXIT_FUN 32
static _DATA_ACCESS int atexit_func_count = 0;
static _DATA_ACCESS DTOR_LIST atexit_func[MAX_ATEXIT_FUN];

/****************************************************************************/
/* ATEXIT - ATTEMPT TO REGISTER A FUNCTION FOR CALLING AT PROGRAM END       */
/*          THE GENERIC C++ ABI (IA64) REQUIRES USING THE CXA_ATEXIT        */
/*          MECHANISM TO IMPL ATEXIT. FUNCTION DEFINED IN VEC_NEWDEL.CPP    */
/****************************************************************************/
int atexit(void (*fun)())
{
   int err_code = 1;

   /*-----------------------------------------------------------------------*/
   /* MUST LOCK WHEN _ADD_DTOR WILL ACCESS A GLOABL POINTER.                */
   /*-----------------------------------------------------------------------*/
   _lock();
   
   /*-----------------------------------------------------------------------*/
   /* We allow a MAX of 32 functions to be registered for processing at exit*/
   /* This is the minimum required by the C Standard. BIOS has a specific   */
   /* specific request that we NOT use malloc here. If anyone requires more */
   /* than 32 atexit functions they need to update MAX_ATEXIT_FUN define    */
   /* above and rebuild the library (CQ20012, CQ20600).                     */
   /*-----------------------------------------------------------------------*/
   if (atexit_func_count < MAX_ATEXIT_FUN)
   {
      /*--------------------------------------------------------------------*/
      /* Choose the next available entry for registering atexit functions.  */
      /*--------------------------------------------------------------------*/
      int allocated_entry = atexit_func_count++;

      /*--------------------------------------------------------------------*/
      /* Populate the allocated entry with the necessary details.           */
      /*--------------------------------------------------------------------*/
      atexit_func[allocated_entry].next     = NULL;
      atexit_func[allocated_entry].object   = &__atexit_func_id__;
      atexit_func[allocated_entry].fun.dfun = fun;

      /*--------------------------------------------------------------------*/
      /* Register the atexit function for processing at exit.               */
      /*--------------------------------------------------------------------*/
      __add_dtor(&(atexit_func[allocated_entry]));

      err_code = 0;
   }
   
   _unlock();
   return err_code;
}
#endif
