/*****************************************************************************/
/*  UNGETC.C v7.3.23                                                         */
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
/*    UNGETC   -  Push a character back onto a stream                        */
/*****************************************************************************/
#include <stdio.h>


/*****************************************************************************/
/* UNGETC   -  Push a character back onto a stream                           */
/*                                                                           */
/*    This function returns the character pushed back upon success, or an    */
/*    EOF upon failure.                                                      */
/*                                                                           */
/*****************************************************************************/
_CODE_ACCESS int ungetc(int _c, register FILE *_fp)
{
   /*------------------------------------------------------------------------*/
   /* If the current stream is not associated with a file, or if the         */
   /* character is EOF, return an error.                                     */
   /*------------------------------------------------------------------------*/
   if(_fp->fd == -1 || _c == EOF) return (EOF);

   /*------------------------------------------------------------------------*/
   /* Set up a buffer if one is needed, and none exists.                     */
   /*------------------------------------------------------------------------*/
   if(_fp->buf == NULL)
   {
      int bufsiz = _STCHK(_fp, _IONBF) ? 0 : BUFSIZ;
      if (setvbuf(_fp, NULL, _BUFFMODE(_fp), bufsiz) == EOF) return (EOF);
   } 

   /*------------------------------------------------------------------------*/
   /* If an UNGETC has already been performed and there is no room left in   */
   /* the buffer, return an EOF.                                             */
   /*------------------------------------------------------------------------*/
   else if(_fp->pos < _fp->buf) return (EOF);

   /*------------------------------------------------------------------------*/
   /* If the file is in update mode, and is currently writing, change it to  */
   /* read mode.                                                             */
   /*------------------------------------------------------------------------*/
   if(_STCHK(_fp, _MODERW))
   {
      _UNSET(_fp, _MODEW);
      _SET(_fp, _MODER);
   }

   /*------------------------------------------------------------------------*/
   /* Put the character in the buffer, set the _UNGETC flag in the stream,   */
   /* and clear the EOF flag in the stream.                                  */
   /*------------------------------------------------------------------------*/
   *(--_fp->pos) = (unsigned char)_c;
   _SET(_fp, _UNGETC);
   _UNSET(_fp, _STATEOF);

   return ((unsigned char)_c);
}

