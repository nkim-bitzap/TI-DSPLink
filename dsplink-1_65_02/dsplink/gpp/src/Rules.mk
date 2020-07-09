#   ============================================================================
#   @file   Rules.mk
#
#   @path   $(DSPLINK)/gpp/src/
#
#   @desc   This file contains the configurable items for the kbuild based
#           makefile.
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

# Update these macros to reflect your environment.
#
# KERNEL_DIR   = The Linux kernel source directory
# TOOL_PATH    = Path to the toolchain
# MAKE_OPTS    = Architecture-specific Make options

# NKim, Linux support only
ifeq ("$(TI_DSPLINK_GPPOS)", "Linux")
ifeq ("$(TI_DSPLINK_PLATFORM)", "OMAP3530")

KERNEL_DIR := ${HOME}/Projects/embedded/kernel/armv7-multi/4.19
TOOL_PATH := ${HOME}/Projects/embedded/gcc/7.5/arm-linux-gnueabihf/bin

endif #ifeq ("$(TI_DSPLINK_PLATFORM)", "OMAP3530")

saved_cross := $(shell cat $(KERNEL_DIR)/include/generated/kernel.cross 2> /dev/null)
CROSS_COMPILE := $(saved_cross)
export CROSS_COMPILE

PATH  := $(TOOL_PATH):$(PATH)
export PATH

endif # ifeq ("$(TI_DSPLINK_GPPOS)", "Linux")
