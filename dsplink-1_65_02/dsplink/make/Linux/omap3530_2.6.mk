#   ============================================================================
#   @file   omap3530_2.6.mk
#
#   @path   $(DSPLINK)/make/Linux/
#
#   @desc   This makefile defines OS specific macros used by MAKE system for
#           the OMAP 3530 Linux distribution.
#
#   @ver    1.65.02.09
#   ============================================================================
#   Copyright (C) 2002-2012, Texas Instruments Incorporated -
#   http://www.ti.com/
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions
#   are met:
#   
#   *  Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#   
#   *  Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#   
#   *  Neither the name of Texas Instruments Incorporated nor the names of
#      its contributors may be used to endorse or promote products derived
#      from this software without specific prior written permission.
#   
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#   OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#   EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#   ============================================================================


ifndef OMAP3530_LINUX4_19_127_MK
define OMAP3530_LINUX4_19_127_MK
endef

#   ============================================================================
#   Let the make system know that a specific distribution for the GPP OS
#   is being used.
#   ============================================================================
USE_DISTRIBUTION := 1

#   ============================================================================
#   Set the values of necessary variables to be used for the OS.
#   ============================================================================

#   ----------------------------------------------------------------------------
#   Base directory for the GPP OS, i.e. when cross-compiling for the Beagle
#   this should point to the target's kernel sources
#   ----------------------------------------------------------------------------
BASE_BUILDOS := ${HOME}/Projects/embedded/kernel/armv7-multi/4.19

#   ----------------------------------------------------------------------------
#   Base for toolchain
#   ----------------------------------------------------------------------------
BASE_TOOLCHAIN := ${HOME}/Projects/embedded/gcc/7.5/arm-linux-gnueabihf

#   ----------------------------------------------------------------------------
#   Base for code generation tools - compiler, linker, archiver etc.
#   ----------------------------------------------------------------------------
BASE_CGTOOLS := $(BASE_TOOLCHAIN)/bin

#   ----------------------------------------------------------------------------
#   Base directory for include files provided by GPP OS
#   ----------------------------------------------------------------------------
BASE_OSINC      := $(BASE_BUILDOS)/include

OSINC_GENERIC   := $(BASE_OSINC)
OSINC_PLATFORM  := $(BASE_TOOLCHAIN)/lib/gcc/arm-linux-gnueabihf/include

#NKim, not available
#OSINC_TARGET    := $(BASE_TOOLCHAIN)/arm-none-linux-gnueabi/libc/usr/include

ifneq ("$(VARIANT)", "")
OSINC_VARIANT   := $(BASE_OSINC)
endif

#   ----------------------------------------------------------------------------
#   Base directory for libraries provided by GPP OS
#   ----------------------------------------------------------------------------

# NKim, when cross-compiling, avoid GLIBC mismatches by providing proper
# versions (e.g. an SD-card containing target's distro). See comments
# on linker options below.
BASE_OSLIB      := /media/admin/rootfs
OSLIB_PLATFORM  := $(BASE_OSLIB)

ifneq ("$(VARIANT)", "")
OSLIB_VARIANT   := $(BASE_OSLIB)
endif

#   ============================================================================
#   COMPILER
#   ============================================================================

#   ----------------------------------------------------------------------------
#   Name of the compiler
#   ----------------------------------------------------------------------------
COMPILER        := $(BASE_CGTOOLS)/arm-linux-gnueabihf-gcc
LD              := $(BASE_CGTOOLS)/arm-linux-gnueabihf-ld

CROSS_COMPILE   := arm-none-linux-gnueabi-
export CROSS_COMPILE

#   ----------------------------------------------------------------------------
#   Command line switches used by the compiler
#
#   CC_SW_DEF       Command line defines
#   CC_SW_INC       Search path for header files
#   CC_SW_OBJ       Create object file
#   CC_SW_DEB       Include debug information
#   ----------------------------------------------------------------------------
CC_SW_DEF       := -D
CC_SW_INC       := -I
CC_SW_OBJ       := -o
CC_SW_DEB       := -g

#   ----------------------------------------------------------------------------
#   Standard flags for the compiler, NKim, disabled the error about the DATE
#   and TIME influencing builds.
#   ----------------------------------------------------------------------------
STD_USER_FLAGS  := -Wall -c

#   ----------------------------------------------------------------------------
#   Standard flags for the compiler when building an executable
#   ----------------------------------------------------------------------------
EXE_CC_FLAGS    :=

#   ----------------------------------------------------------------------------
#   Flags for the compiler when building a driver
#   ----------------------------------------------------------------------------
DRV_CC_FLAGS    := -nostdinc

#   ----------------------------------------------------------------------------
#   Flags for the compiler when building a library
#   ----------------------------------------------------------------------------
LIB_CC_FLAGS    :=

#   ----------------------------------------------------------------------------
#   Standard definitions for the compiler
#   ----------------------------------------------------------------------------
STD_CC_DEFNS    := -D_REENTRANT

#   ============================================================================
#   ARCHIVER2 - This denotes the archiver.
#   ============================================================================
ARCHIVER        := $(BASE_CGTOOLS)/arm-linux-gnueabihf-ar

#   ----------------------------------------------------------------------------
#   Standard flags for the archiver
#   ----------------------------------------------------------------------------
STD_AR_FLAGS    := -rs


#   ============================================================================
#   LINKER - The compiler is used for linking purpose as well.
#   ============================================================================
LINKER      := $(BASE_CGTOOLS)/arm-linux-gnueabihf-gcc

#   ----------------------------------------------------------------------------
#   Command line switches used by the linker
#
#   LD_SW_LIB       Search path for libraries
#   LD_SW_OUT       Output filename
#   LD_SW_RELOC     Generate relocateable output
#   ----------------------------------------------------------------------------

LD_SW_LIB       := -L
LD_SW_OUT       := -o
LD_SW_RELOC     := -r

#   ----------------------------------------------------------------------------
#   Standard flags for the linker
#
#   NKim, if there is a glibc version already installed (e.g. arm cross-
#   compiler on your host/build machine), you might have a hard time forcing
#   the compiler NOT to use it (if you want to link against a different glibc
#   version, e.g. as available on the target).
#
#   -L/-Wl/-rpath/ flags/paths did not work for me in this case, thus, the
#   only solution remaining is to use --sysroot (if your compiler allows it,
#   see build configuration)
#   ----------------------------------------------------------------------------
STD_LD_FLAGS    := --sysroot=$(OSLIB_PLATFORM)

#   ----------------------------------------------------------------------------
#   Flags for the linker when building an executable
#   ----------------------------------------------------------------------------
EXE_LD_FLAGS    := -lc -lpthread

#   ----------------------------------------------------------------------------
#   Flags for the linker when building a driver
#   ----------------------------------------------------------------------------
DRV_LD_FLAGS    :=

#   ============================================================================
#   Post processing utilities for Linux 2.6
#   ============================================================================
ifneq ($(CONFIG_MODVERSIONS),)
CMD_MODPOST_FLAGS := -m -i
else
CMD_MODPOST_FLAGS := -i
endif

# NKim, NOTE, that some im
CMD_MODPOST := $(BASE_BUILDOS)/source/scripts/mod/modpost \
               $(CMD_MODPOST_FLAGS) $(BASE_BUILDOS)/build/Module.symvers \
               $(BASE_BUILDOS)/build/vmlinux

endif   # ifndef OMAP3530_LINUX4_19_127_MK
