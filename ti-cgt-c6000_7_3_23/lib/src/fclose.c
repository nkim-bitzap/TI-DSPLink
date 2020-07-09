/*****************************************************************************/
/*  FCLOSE.C v7.3.23                                                         */
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
/*    Functions:                                                             */
/*       FCLOSE   -  Close a stream                                          */
/*****************************************************************************/
#include <stdio.h>
#include "file.h"
#include <string.h>
#include <stdlib.h>

extern int _doflush(FILE *_fp);


/*****************************************************************************/
/* FCLOSE   -  Close a stream                                                */
/*                                                                           */
/*    This function flushes the current stream, deallocates any buffers      */
/*    associated with the stream, and closes it.  This function returns a 0  */
/*    if the close was successful, or an EOF if an error occured.            */
/*                                                                           */
/*****************************************************************************/
_CODE_ACCESS int fclose(FILE *_fp)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*------------------------------------------------------------------------*/
   int fd = _fp->fd;
   int errchk;
   int remove_flag = _STCHK(_fp, _TMPFILE);

   /*------------------------------------------------------------------------*/
   /* If the current stream is not associated with a file, return an error.  */
   /*------------------------------------------------------------------------*/
   if(_fp->fd == -1) return (EOF);

   /*------------------------------------------------------------------------*/
   /* Flush the buffer.                                                      */
   /*------------------------------------------------------------------------*/
   if(_doflush(_fp)) return (EOF);

   /*------------------------------------------------------------------------*/
   /* Free the buffer if there was one, and it was malloc'd by SETVBUF.      */
   /*------------------------------------------------------------------------*/
   if(_STCHK(_fp, _BUFFALOC))
   {
      free((_fp->buf)-1);
      _UNSET(_fp, _BUFFALOC);
   }

   /*------------------------------------------------------------------------*/
   /* Reset the buffer pointers in the stream.                               */
   /*------------------------------------------------------------------------*/
   _fp->buf = NULL;
   _fp->pos = NULL;
   _fp->bufend = NULL;

   /*------------------------------------------------------------------------*/
   /* Close the file, and give the FILE structure an invalid file descriptor */
   /* so it cannot be used until it is assigned to another stream.           */
   /*------------------------------------------------------------------------*/
   errchk = close(_fp->fd);
   _fp->fd = -1;

   /*------------------------------------------------------------------------*/
   /* If the FILE pointer was associated with a temporary file, look up that */
   /* temporary file's filename, and remove it.                              */
   /*------------------------------------------------------------------------*/
   if(remove_flag) remove(_tmpnams[fd]);  

   return (errchk);
}

