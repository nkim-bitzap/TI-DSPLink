/*****************************************************************************/
/*  _BUFREAD.C v7.3.23                                                       */
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
/* Functions:                                                                */
/*    _BUFF_READ  -  Fill a stream's buffer from its file                    */
/*****************************************************************************/
#include <stdio.h>
#include <_lock.h>
#include "file.h"

extern _DATA_ACCESS int  _ft_end;
extern int  _doflush(FILE *_fp);
extern void _buff_read(FILE *_fp);


/*****************************************************************************/
/* _BUFF_READ  -   Fill a stream's buffer from its file                      */
/*                                                                           */
/*    This function fills stream _FP's buffer with the contents of the file  */
/*    it is associated with.  It returns nothing, but sets flags in the      */
/*    stream if any I/O errors occur.                                        */
/*                                                                           */
/*****************************************************************************/
void _buff_read(FILE *_fp)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*------------------------------------------------------------------------*/
   int   errchk,
         j,
         buffer_size    = _fp->bufend - _fp->buf;

   /*------------------------------------------------------------------------*/
   /* If this is a line buffered stream, flush all line buffered streams.    */
   /*------------------------------------------------------------------------*/
   if(_BUFFMODE(_fp) == _IOLBF)
   {
       /*--------------------------------------------------------------------*/
       /* This is a critical section because it depends on the global	     */
       /* variable _ft_end.						     */
       /*--------------------------------------------------------------------*/
       _lock();
       for(j=0; j < _ft_end; j++)
	   if(_BUFFMODE(&_ftable[j]) == _IOLBF)
	       _doflush(&_ftable[j]);
       _unlock();
   }

   /*------------------------------------------------------------------------*/
   /* Read in the next characters from the file.                             */
   /*------------------------------------------------------------------------*/
   errchk = read(_fp->fd, (char *)_fp->buf, buffer_size);

   /*------------------------------------------------------------------------*/
   /* Adjust the buffer pointers.                                            */
   /*------------------------------------------------------------------------*/
   _fp->buff_stop = _fp->buf + errchk;
   _fp->pos = _fp->buf;

   /*------------------------------------------------------------------------*/
   /* Set any error flags if necessary.                                      */
   /*------------------------------------------------------------------------*/
   switch(errchk)
   {
      case -1 : _SET(_fp, _STATERR);
                break;
 
      case 0  : _SET(_fp, _STATEOF);
                break;
   }

   return;
 
}
 
