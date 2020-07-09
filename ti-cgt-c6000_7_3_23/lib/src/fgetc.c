/*****************************************************************************/
/*  FGETC.C v7.3.23                                                          */
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
/*    GETC     -  Get a character from a stream                              */
/*    GETCHAR  -  Get a character from stdin                                 */
/*    FGETC    -  Get a character from a stream                              */
/*****************************************************************************/
#include <stdio.h>
#include "file.h"

extern void _buff_read(FILE *_fp);
extern int  _rd_ok    (FILE *_fp);

extern _CODE_ACCESS int fgetc(register FILE *_fp);






/*****************************************************************************/
/* GETC  -  Get a character from a stream                                    */
/*                                                                           */
/*    This function is equivalent to FGETC.                                  */
/*                                                                           */
/*****************************************************************************/
_CODE_ACCESS int getc(FILE *_fp) { return (fgetc(_fp)); }






/*****************************************************************************/
/* GETCHAR  -  Get a character from stdin                                    */
/*                                                                           */
/*    This function calls a macro defined in STDIO.H, which calls FGETC with */
/*    stdin as its argument.                                                 */
/*                                                                           */
/*****************************************************************************/
_CODE_ACCESS int getchar(void) { return(_getchar()); }






/*****************************************************************************/
/* FGETC -  Get a character from a stream                                    */
/*****************************************************************************/
_CODE_ACCESS int fgetc(register FILE *_fp)
{
   /*------------------------------------------------------------------------*/
   /* Make sure that it is OK to read from this stream.                      */
   /*------------------------------------------------------------------------*/
   if(! _rd_ok(_fp)) return (EOF);
   
   /*------------------------------------------------------------------------*/
   /* For non-buffered streams, call the lowlevel READ function.             */
   /*------------------------------------------------------------------------*/
   if(_BUFFMODE(_fp) == _IONBF)
   {
      int   errchk;
      char  result;

      if (_STCHK(_fp, _UNGETC)) 
      {
         _UNSET(_fp, _UNGETC);
         return ((int)*(_fp->pos++)); 
      }

      errchk = read(_fp->fd, &result, 1);
      if(errchk <= 0)
      {
         _SET(_fp, (errchk == 0) ? _STATEOF : _STATERR);
         return (EOF);
      }

      return ((int)result);
   }

   /*------------------------------------------------------------------------*/
   /* If the buffer has been entirely read, or is empty, call _BUFF_READ to  */
   /* fill the buffer.                                                       */
   /*------------------------------------------------------------------------*/
   if(_fp->pos == _fp->buff_stop) _buff_read(_fp);
 
   /*------------------------------------------------------------------------*/
   /* If the buffer read was unsuccessful, return an EOF.  Otherwise, clear  */
   /* the _UNGETC flag in the stream, and return the next character.         */
   /*------------------------------------------------------------------------*/
   if(_STCHK(_fp, (_STATERR | _STATEOF))) return (EOF);
   _UNSET(_fp, _UNGETC);

   return ((int)*(_fp->pos++)); 
   
}

