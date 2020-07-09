/*****************************************************************************/
/*  FFLUSH.C v7.3.23                                                         */
/*                                                                           */
/* Copyright (c) 1995-2015 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* FUNCTIONS:                                                                */
/*    fflush   -  Call _doflush for all streams that require flushing        */
/*    _doflush -  Flush one stream                                           */
/*****************************************************************************/
#include <stdio.h>
#include <_lock.h>
#include "file.h"

extern _DATA_ACCESS int _ft_end;

int _doflush(FILE *_fp);






/*****************************************************************************/
/* FFLUSH   -  Call _doflush for all streams that require flushing           */
/*                                                                           */
/*    This function returns a 0 upon success, and an EOF upon failure.       */
/*                                                                           */
/*****************************************************************************/
_CODE_ACCESS int fflush(register FILE *_fp)
{
   int result = 0;
 
   /*------------------------------------------------------------------------*/
   /* If _fp is not a NULL pointer, call _DOFLUSH for that stream.           */
   /* Otherwise, call _DOFLUSH for all file streams in the table that are    */
   /* active.                                                                */
   /*------------------------------------------------------------------------*/
   if (_fp) result = _doflush(_fp);
   else
   {
      int index;

      /*---------------------------------------------------------------------*/
      /* This is a critical section because it depends on the global	     */
      /* variable _ft_end.						     */
      /*---------------------------------------------------------------------*/
      _lock();
      for(index = 0; index < _ft_end; index++)
         if(_ftable[index].fd != -1) result |= _doflush(&_ftable[index]);
      _unlock();
   }
 
   return (result);
}






/*****************************************************************************/
/* _DOFLUSH -  Flush one stream                                              */
/*                                                                           */
/*    This function flushes the stream pointed to by _fp.  If the function   */
/*    is successful, it returns a 0.  If unsuccessful, it returns an EOF     */
/*                                                                           */
/*****************************************************************************/
int _doflush(FILE *_fp)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*                                                                        */
   /*    num_write   -  The number of bytes to be written to the file        */
   /*    errchk      -  An indicator to see if WRITE was successful          */
   /*------------------------------------------------------------------------*/
   unsigned num_write = _fp->pos - _fp->buf;
   int errchk = 0;
 
   /*------------------------------------------------------------------------*/
   /* If the current stream is not associated with a file, return an error.  */
   /*------------------------------------------------------------------------*/
   if(_fp->fd == -1) return (EOF);

   /*------------------------------------------------------------------------*/
   /* If the stream is writable, and it has a buffer, call WRITE, and store  */
   /* its return value in errchk                                             */
   /*------------------------------------------------------------------------*/
   if(_STCHK(_fp, _MODEW) && _fp->buf != NULL && num_write != 0)
      errchk = write(_fp->fd, (char *)_fp->buf, num_write);
 
   /*------------------------------------------------------------------------*/
   /* If WRITE fails, set the error flag in the stream pointer, and return   */
   /* an EOF                                                                 */
   /*------------------------------------------------------------------------*/
   if(errchk < 0)
   {
      _SET(_fp, _STATERR);
      return (EOF);
   }
 
   /*------------------------------------------------------------------------*/
   /* Reset the buffer pointer, make files opened with the "+" flag          */
   /* available for wither reading or writing, and return a 0, indicating    */
   /* a success                                                              */
   /*------------------------------------------------------------------------*/
   _fp->pos = _fp->buff_stop = _fp->buf;
   if (_STCHK(_fp, _MODERW)) _UNSET(_fp, (_MODER | _MODEW));
   return 0;
 
}
 
