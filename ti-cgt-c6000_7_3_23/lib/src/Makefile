##############################################################################
#
#
# Makefile for C6000 run-time support library version 7.3.23
#
#
##############################################################################
#
# This Makefile is automatically-generated: you usually should not edit it. 
#
##############################################################################


##############################################################################
#
# This Makefile is specific to compiler RTS library version 7.3.23.  
# The format is subject to change without notice.  This Makefile is intended
# for use with mklib, which understands which 'make' variables to set to build
# each distinct version of the RTS library.
#
# This Makefile uses GNU make language extensions.
#
##############################################################################

##############################################################################
#
# GROUPS
#
# The source files are set up in a modular fashion using "groups."  Groups
# represent major feature clusters, and usually specify source files which
# implement that feature.  When building a library which needs a particular
# feature, the group which represents that feature is "activated" by setting a
# 'make' variable.  This variable can be set directly by the user, or may be
# inferred from the setting of other variables.  Groups (and the files they
# contain) not needed for a certain library are not activated.  Some groups
# are always activated.  Groups which are not always activated are enclosed in
# an "ifeq" testing the corresponding 'make' variable (the name of the
# variable is the name of the group).
#
# Groups can specify any kind of source file (e.g. C, C++, assembly), but do
# not list header files, or source files included from other source files.
# This Makefile is focused on how to build the object files, not listing all
# of the necessary files.  Some groups do not list any source files; these
# groups may still carry information such as extra options to use when that
# group is active, or may activate other groups.  Some groups exist only to be
# tested as part of the activation condition of other groups.
#
# Groups can specify extra compiler options to use when that group is active.
# These can be options intended for all targets (UNIVERSAL_FLAGS), such as the
# CPU version, or can be intended only for a certain type of files (CPP_FLAGS)
# (e.g. the option "--exceptions")
#
##############################################################################

##############################################################################
#
# OPTIONS
#
# You can append or override some options through 'make' variables specified
# on the command line.  Not all options can be changed this way, and some
# options are dangerous to use in a Makefile (e.g. "--skip_assembler").
# Options added by groups below should not be altered; if the option is
# undesired, you're probably building the wrong library.  For example, if you
# don't want "--exceptions", you shouldn't be using EXCEPTIONS=1.
#
# You can append options to the standard list by using EXTRA_FLAGS.  This is
# useful for enabling debugging support or activating silicon errata
# workarounds:
#
# gmake LIB=some.lib EXTRA_FLAGS="-g"
#
# You can completely replace the standard list by using STANDARD_FLAGS, but
# this should almost never be necessary.  WARNING: This Makefile will not
# optimize the files if you replace the standard list and your replacement
# options do not include the right optimization flags.
#
# gmake LIB=some.lib STANDARD_FLAGS="-o3 -oe"
#
##############################################################################

##############################################################################
# Available libraries
#
# You can build each 7.3.23 library using the appropriate command:
#
# gmake library LIB=rts6200.lib C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts6200_eh.lib FULL_PORTABLE_EH=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6200_elf.lib C6XABI=1 C6000=1 NOT_VENC_ASM=1 EABI=1
# gmake library LIB=rts6200_elf40.lib C6XABI=1 ELF40=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6200_elf40_eh.lib C6XABI=1 EABI_TDEH=1 ELF40=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6200_elf_eh.lib C6XABI=1 EABI_TDEH=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6200e.lib BIG_ENDIAN=1 C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts6200e_eh.lib FULL_PORTABLE_EH=1 BIG_ENDIAN=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6200e_elf.lib C6XABI=1 BIG_ENDIAN=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6200e_elf40.lib C6XABI=1 BIG_ENDIAN=1 ELF40=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6200e_elf40_eh.lib BIG_ENDIAN=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 ELF40=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6200e_elf_eh.lib C6XABI=1 BIG_ENDIAN=1 EABI_TDEH=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6200v.lib VENC=1 NOASM_RTS=1 C_MEMCPY=1
# gmake library LIB=rts6200v_eh.lib FULL_PORTABLE_EH=1 VENC=1 NOASM_RTS=1 C_MEMCPY=1 EXCEPTIONS=1
# gmake library LIB=rts6400.lib C6400=1 C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts6400_eh.lib FULL_PORTABLE_EH=1 C6400=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6400_elf.lib C6XABI=1 C6400=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6400_elf40.lib C6XABI=1 C6400=1 ELF40=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6400_elf40_eh.lib C6400=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 ELF40=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6400_elf_eh.lib C6XABI=1 C6400=1 EABI_TDEH=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6400e.lib C6400=1 BIG_ENDIAN=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6400e_eh.lib FULL_PORTABLE_EH=1 C6400=1 BIG_ENDIAN=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6400e_elf.lib C6XABI=1 C6400=1 BIG_ENDIAN=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6400e_elf40.lib C6XABI=1 C6400=1 BIG_ENDIAN=1 ELF40=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6400e_elf40_eh.lib C6400=1 BIG_ENDIAN=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 ELF40=1 C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts6400e_elf_eh.lib C6400=1 BIG_ENDIAN=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts64plus.lib C64P=1 C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts64plus_eh.lib FULL_PORTABLE_EH=1 C64P=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts64plus_elf.lib C6XABI=1 C64P=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts64plus_elf40.lib C6XABI=1 C64P=1 ELF40=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts64plus_elf40_eh.lib EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 C64P=1 ELF40=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts64plus_elf_eh.lib C6XABI=1 EABI_TDEH=1 C64P=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts64plus_elf_no_parallel_loads.lib C6XABI=1 C64P=1 NOT_VENC_ASM=1 C6000=1 NO_PARALLEL_LOADS=1 EABI=1
# gmake library LIB=rts64plus_elf_no_parallel_loads_eh.lib EXCEPTIONS=1 EABI=1 NO_PARALLEL_LOADS=1 C6XABI=1 EABI_TDEH=1 C64P=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts64pluse.lib BIG_ENDIAN=1 C64P=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts64pluse_eh.lib FULL_PORTABLE_EH=1 BIG_ENDIAN=1 C64P=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts64pluse_elf.lib C6XABI=1 BIG_ENDIAN=1 C64P=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts64pluse_elf40.lib C6XABI=1 BIG_ENDIAN=1 C64P=1 ELF40=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts64pluse_elf40_eh.lib BIG_ENDIAN=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 C64P=1 ELF40=1 C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts64pluse_elf_eh.lib BIG_ENDIAN=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 C64P=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts64pluse_elf_no_parallel_loads.lib C6XABI=1 BIG_ENDIAN=1 C64P=1 NOT_VENC_ASM=1 C6000=1 NO_PARALLEL_LOADS=1 EABI=1
# gmake library LIB=rts64pluse_elf_no_parallel_loads_eh.lib BIG_ENDIAN=1 EXCEPTIONS=1 EABI=1 NO_PARALLEL_LOADS=1 C6XABI=1 EABI_TDEH=1 C64P=1 C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts64plusv.lib VENC=1 NOASM_RTS=1 C64P=1 C_MEMCPY=1
# gmake library LIB=rts64plusv_eh.lib FULL_PORTABLE_EH=1 VENC=1 NOASM_RTS=1 C64P=1 C_MEMCPY=1 EXCEPTIONS=1
# gmake library LIB=rts6600_coff.lib COFFABI=1 C6600=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6600_coff_eh.lib FULL_PORTABLE_EH=1 COFFABI=1 C6600=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6600_elf.lib C6XABI=1 C6600=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6600_elf40.lib C6XABI=1 ELF40=1 C6600=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6600_elf40_eh.lib C6600=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 ELF40=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6600_elf_eh.lib C6XABI=1 EABI_TDEH=1 C6600=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6600e_coff.lib COFFABI=1 BIG_ENDIAN=1 C6600=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6600e_coff_eh.lib FULL_PORTABLE_EH=1 COFFABI=1 BIG_ENDIAN=1 C6600=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6600e_elf.lib C6XABI=1 BIG_ENDIAN=1 C6600=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6600e_elf40.lib C6XABI=1 BIG_ENDIAN=1 ELF40=1 C6600=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6600e_elf40_eh.lib BIG_ENDIAN=1 C6600=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 ELF40=1 C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts6600e_elf_eh.lib BIG_ENDIAN=1 C6600=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6700.lib C6700=1 C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts6700_eh.lib C6700=1 FULL_PORTABLE_EH=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6700_elf.lib C6700=1 C6XABI=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6700_elf40.lib C6700=1 C6XABI=1 ELF40=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6700_elf40_eh.lib C6700=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 ELF40=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6700_elf_eh.lib C6700=1 C6XABI=1 EABI_TDEH=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6700e.lib C6700=1 BIG_ENDIAN=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6700e_eh.lib C6700=1 FULL_PORTABLE_EH=1 BIG_ENDIAN=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6700e_elf.lib C6700=1 C6XABI=1 BIG_ENDIAN=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6700e_elf40.lib C6700=1 C6XABI=1 BIG_ENDIAN=1 ELF40=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts6700e_elf40_eh.lib C6700=1 BIG_ENDIAN=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 ELF40=1 C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts6700e_elf_eh.lib C6700=1 BIG_ENDIAN=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6740.lib C6000=1 NOT_VENC_ASM=1 C6740=1
# gmake library LIB=rts6740_eh.lib FULL_PORTABLE_EH=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1 C6740=1
# gmake library LIB=rts6740_elf.lib C6XABI=1 C6000=1 NOT_VENC_ASM=1 EABI=1 C6740=1
# gmake library LIB=rts6740_elf40.lib C6XABI=1 ELF40=1 NOT_VENC_ASM=1 C6000=1 EABI=1 C6740=1
# gmake library LIB=rts6740_elf40_eh.lib EXCEPTIONS=1 EABI=1 C6740=1 C6XABI=1 EABI_TDEH=1 ELF40=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts6740_elf_eh.lib C6XABI=1 EABI_TDEH=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1 EABI=1 C6740=1
# gmake library LIB=rts6740e.lib BIG_ENDIAN=1 C6000=1 NOT_VENC_ASM=1 C6740=1
# gmake library LIB=rts6740e_eh.lib FULL_PORTABLE_EH=1 BIG_ENDIAN=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1 C6740=1
# gmake library LIB=rts6740e_elf.lib C6XABI=1 BIG_ENDIAN=1 NOT_VENC_ASM=1 C6000=1 EABI=1 C6740=1
# gmake library LIB=rts6740e_elf40.lib C6XABI=1 BIG_ENDIAN=1 ELF40=1 NOT_VENC_ASM=1 C6000=1 EABI=1 C6740=1
# gmake library LIB=rts6740e_elf40_eh.lib BIG_ENDIAN=1 EXCEPTIONS=1 EABI=1 C6740=1 C6XABI=1 EABI_TDEH=1 ELF40=1 C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts6740e_elf_eh.lib BIG_ENDIAN=1 EXCEPTIONS=1 EABI=1 C6740=1 C6XABI=1 EABI_TDEH=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts67plus.lib C67P=1 C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts67plus_eh.lib FULL_PORTABLE_EH=1 C67P=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts67plus_elf.lib C6XABI=1 C67P=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts67plus_elf40.lib C6XABI=1 C67P=1 ELF40=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts67plus_elf40_eh.lib C67P=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 ELF40=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts67plus_elf_eh.lib C6XABI=1 C67P=1 EABI_TDEH=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts67pluse.lib C67P=1 BIG_ENDIAN=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts67pluse_eh.lib FULL_PORTABLE_EH=1 C67P=1 BIG_ENDIAN=1 EXCEPTIONS=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rts67pluse_elf.lib C6XABI=1 C67P=1 BIG_ENDIAN=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts67pluse_elf40.lib C6XABI=1 C67P=1 BIG_ENDIAN=1 ELF40=1 NOT_VENC_ASM=1 C6000=1 EABI=1
# gmake library LIB=rts67pluse_elf40_eh.lib C67P=1 BIG_ENDIAN=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 ELF40=1 C6000=1 NOT_VENC_ASM=1
# gmake library LIB=rts67pluse_elf_eh.lib C67P=1 BIG_ENDIAN=1 EXCEPTIONS=1 EABI=1 C6XABI=1 EABI_TDEH=1 NOT_VENC_ASM=1 C6000=1
# gmake library LIB=rtscgemv.lib VENC=1 NOASM_RTS=1 C_MEMCPY=1 CGEM=1
# gmake library LIB=rtscgemv_eh.lib FULL_PORTABLE_EH=1 VENC=1 NOASM_RTS=1 C_MEMCPY=1 EXCEPTIONS=1 CGEM=1
# gmake library LIB=rtstesla_be_coff.lib TESLA=1 COFFABI=1 BIG_ENDIAN=1 C_MEMCPY=1 NOT_VENC_ASM=1
# gmake library LIB=rtstesla_be_coff_eh.lib FULL_PORTABLE_EH=1 TESLA=1 COFFABI=1 BIG_ENDIAN=1 C_MEMCPY=1 EXCEPTIONS=1 NOT_VENC_ASM=1
# gmake library LIB=rtstesla_be_elf.lib C6XABI=1 TESLA=1 BIG_ENDIAN=1 C_MEMCPY=1 NOT_VENC_ASM=1 EABI=1
# gmake library LIB=rtstesla_be_elf40.lib C6XABI=1 TESLA=1 BIG_ENDIAN=1 C_MEMCPY=1 ELF40=1 NOT_VENC_ASM=1 EABI=1
# gmake library LIB=rtstesla_be_elf40_eh.lib BIG_ENDIAN=1 C_MEMCPY=1 EXCEPTIONS=1 EABI=1 C6XABI=1 TESLA=1 EABI_TDEH=1 ELF40=1 NOT_VENC_ASM=1
# gmake library LIB=rtstesla_be_elf_eh.lib BIG_ENDIAN=1 C_MEMCPY=1 EXCEPTIONS=1 EABI=1 C6XABI=1 TESLA=1 EABI_TDEH=1 NOT_VENC_ASM=1
# gmake library LIB=rtstesla_le_coff.lib TESLA=1 COFFABI=1 C_MEMCPY=1 NOT_VENC_ASM=1
# gmake library LIB=rtstesla_le_coff_eh.lib FULL_PORTABLE_EH=1 TESLA=1 COFFABI=1 C_MEMCPY=1 EXCEPTIONS=1 NOT_VENC_ASM=1
# gmake library LIB=rtstesla_le_elf.lib C6XABI=1 TESLA=1 C_MEMCPY=1 NOT_VENC_ASM=1 EABI=1
# gmake library LIB=rtstesla_le_elf40.lib C6XABI=1 TESLA=1 C_MEMCPY=1 ELF40=1 NOT_VENC_ASM=1 EABI=1
# gmake library LIB=rtstesla_le_elf40_eh.lib C_MEMCPY=1 EXCEPTIONS=1 EABI=1 C6XABI=1 TESLA=1 EABI_TDEH=1 ELF40=1 NOT_VENC_ASM=1
# gmake library LIB=rtstesla_le_elf_eh.lib C6XABI=1 TESLA=1 EABI_TDEH=1 C_MEMCPY=1 EXCEPTIONS=1 NOT_VENC_ASM=1 EABI=1
##############################################################################

#-----------------------------------------------------------------------------
# Basic definitions
#-----------------------------------------------------------------------------
STANDARD_FLAGS =  -o -oe -k -ps -pdsw225 -q
ifeq (y,$(shell [ -e $(CGT_BIN)/cl6x ] && echo y))
  CC = $(CGT_BIN)/cl6x
else
  CC = cl6x
endif
ifeq (y,$(shell [ -e $(CGT_BIN)/ar6x ] && echo y))
  AR = $(CGT_BIN)/ar6x
else
  AR = ar6x
endif
CD = cd

OBJ = OBJ

#-----------------------------------------------------------------------------
# Group ELF40
#-----------------------------------------------------------------------------
ifeq ($(ELF40),1)
C6XABI=1
UNIVERSAL_FLAGS += --long_precision_bits=40
endif


#-----------------------------------------------------------------------------
# Group TARGET
#-----------------------------------------------------------------------------
UNIVERSAL_FLAGS += -mo --mem_model:data=far --no_visible_enums

TARGET_C_SOURCE = \
	autoinit.c \
	boot.c \
	dtos.c \
	gsmfuncs.c \
	gsmvars.c \
	imath40.c \
	imath64.c \
	llshift.c \
	lltoa.c \
	memcpy62.c \
	mpyll.c \
	outprof.c \
	pprof_cio.c \
	pprof_user.c \
	trgmsg.c \
	memset.c \
	copy_zero_init.c \
	copy_decompress_none.c \
	copy_decompress_rle.c \
	copy_decompress_lzss.c \
	imaxabs.c \
	imaxdiv.c \
	strtoimax.c \
	strtoumax.c

C_SOURCE += $(TARGET_C_SOURCE)


TARGET_LINASM_SOURCE = \
	negll.sa

LINASM_SOURCE += $(TARGET_LINASM_SOURCE)


#-----------------------------------------------------------------------------
# Group GENERIC
#-----------------------------------------------------------------------------
UNIVERSAL_FLAGS += -c --ti_lib --building_runtime -D_BOOL
CPP_FLAGS += -fg --rtti

#-----------------------------------------------------------------------------
# Group VENC
#-----------------------------------------------------------------------------
ifeq ($(VENC),1)
UNIVERSAL_FLAGS += --vencode
endif


#-----------------------------------------------------------------------------
# Group TESLA
#-----------------------------------------------------------------------------
ifeq ($(TESLA),1)
C_MEMCPY=1
UNIVERSAL_FLAGS += -mv=tesla

TESLA_ASM_SOURCE = \
	divi_t.asm \
	divu_t.asm \
	remi_t.asm \
	remu_t.asm \
	strasgi_t.asm

ASM_SOURCE += $(TESLA_ASM_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group C6XABI
#-----------------------------------------------------------------------------
ifeq ($(C6XABI),1)
EABI=1
UNIVERSAL_FLAGS += --abi=eabi

C6XABI_C_SOURCE = \
	weak_return.c \
	divrem.c

C_SOURCE += $(C6XABI_C_SOURCE)


C6XABI_ASM_SOURCE = \
	tdeh_uwentry_c6000.asm

ASM_SOURCE += $(C6XABI_ASM_SOURCE)


C6XABI_CPP_SOURCE = \
	tdeh_pr_c6000.cpp

CPP_SOURCE += $(C6XABI_CPP_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group EXCEPTIONS
#-----------------------------------------------------------------------------
ifeq ($(EXCEPTIONS),1)
CPP_FLAGS += --exceptions
endif


#-----------------------------------------------------------------------------
# Group COMPLEX_HEADERS
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group CGEM
#-----------------------------------------------------------------------------
ifeq ($(CGEM),1)
UNIVERSAL_FLAGS += -mv=cgem --enable:cgem_64b
endif


#-----------------------------------------------------------------------------
# Group DINKUM_MATH_SUBSET_SHARED_WITH_COMPLEX
#-----------------------------------------------------------------------------

DINKUM_MATH_SUBSET_SHARED_WITH_COMPLEX_C_SOURCE = \
	xsin.c \
	xfsin.c \
	xlsin.c \
	xsinh.c \
	xfsinh.c \
	xlsinh.c \
	xcosh.c \
	xfcosh.c \
	xlcosh.c \
	xexp.c \
	xfexp.c \
	xlexp.c \
	xdtest.c \
	xfdtest.c \
	xldtest.c \
	xdscale.c \
	xfdscale.c \
	xldscale.c \
	xdnorm.c \
	xfdnorm.c \
	xldnorm.c \
	xvalues.c \
	xfvalues.c \
	xlvalues.c \
	xferaise.c

C_SOURCE += $(DINKUM_MATH_SUBSET_SHARED_WITH_COMPLEX_C_SOURCE)


#-----------------------------------------------------------------------------
# Group C6000
#-----------------------------------------------------------------------------
ifneq ($(TESLA),1)
ifneq ($(VENC),1)
C6000=1
endif
endif

ifeq ($(C6000),1)

C6000_ASM_SOURCE = \
	divi.asm \
	divu.asm \
	memcpy64.asm \
	remi.asm \
	remu.asm \
	strasg.asm

ASM_SOURCE += $(C6000_ASM_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group NOT_VENC_ASM
#-----------------------------------------------------------------------------
ifneq ($(VENC),1)
NOT_VENC_ASM=1
endif

ifeq ($(NOT_VENC_ASM),1)

NOT_VENC_ASM_ASM_SOURCE = \
	push.asm \
	call_stub.asm \
	setjmp.asm

ASM_SOURCE += $(NOT_VENC_ASM_ASM_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group GENERIC_EDG
#-----------------------------------------------------------------------------

GENERIC_EDG_CPP_SOURCE = \
	array_del.cpp \
	array_new.cpp \
	array_nodel.cpp \
	array_nonew.cpp \
	array_pdel.cpp \
	array_pnew.cpp \
	delete.cpp \
	delnothrow.cpp \
	dtor_list.cpp \
	error.cpp \
	guard.cpp \
	memzero.cpp \
	new_.cpp \
	newhandler.cpp \
	newnothrow.cpp \
	placedel.cpp \
	placenew.cpp \
	pure_virt.cpp \
	rtti.cpp \
	set_new.cpp \
	typeinfo_.cpp \
	vars.cpp \
	vec_cctor.cpp \
	vec_newdel.cpp

CPP_SOURCE += $(GENERIC_EDG_CPP_SOURCE)


#-----------------------------------------------------------------------------
# Group GENERIC_TI
#-----------------------------------------------------------------------------

GENERIC_TI_C_SOURCE = \
	cpy_tbl.c \
	ecvt.c \
	exit.c \
	fcvt.c \
	memory.c \
	_bufread.c \
	_io_perm.c \
	_lock.c \
	_printfi.c \
	_printfi_min.c \
	_printfi_nf.c \
	_scanfi.c \
	_tvaltostr.c \
	abs.c \
	args_main.c \
	asctime.c \
	assert.c \
	atexit.c \
	atof.c \
	atoi.c \
	atol.c \
	atoll.c \
	bsearch.c \
	clearerr.c \
	clock.c \
	ctime_.c \
	ctype.c \
	defs.c \
	difftime.c \
	errno.c \
	fclose.c \
	feof.c \
	ferror.c \
	fflush.c \
	fgetc.c \
	fgetpos.c \
	fgets.c \
	fopen.c \
	fprintf.c \
	fputc.c \
	fputs.c \
	fread.c \
	fscanf.c \
	fseek.c \
	fsetpos.c \
	ftell.c \
	fwrite.c \
	gmtime.c \
	isalnum.c \
	isalpha.c \
	isascii.c \
	iscntrl.c \
	isdigit.c \
	isgraph.c \
	islower.c \
	isprint.c \
	ispunct.c \
	isspace.c \
	isupper.c \
	isxdigit.c \
	localtim.c \
	lowlev.c \
	ltoa.c \
	memccpy.c \
	memchr.c \
	memcmp.c \
	memmov.c \
	mktime.c \
	multibyte.c \
	perror.c \
	printf.c \
	qsort.c \
	rand.c \
	remove.c \
	rewind.c \
	setbuf.c \
	setlocale.c \
	setvbuf.c \
	sinit.c \
	snprintf.c \
	sprintf.c \
	sscanf.c \
	strcat.c \
	strchr.c \
	strcmp.c \
	strcoll.c \
	strcpy.c \
	strcspn.c \
	strerror.c \
	strftime.c \
	strlen.c \
	strncat.c \
	strncmp.c \
	strncpy.c \
	strpbrk.c \
	strrchr.c \
	strspn.c \
	strstr.c \
	strtod.c \
	strtok.c \
	strtol.c \
	strtold.c \
	strtoll.c \
	strtoul.c \
	strtoull.c \
	strxfrm.c \
	time.c \
	tmpfile.c \
	tmpnam.c \
	tmzone.c \
	toascii.c \
	tolower.c \
	toupper.c \
	trgdrv.c \
	ungetc.c \
	vfprintf.c \
	vprintf.c \
	vsnprintf.c \
	vsprintf.c \
	wctype.c

C_SOURCE += $(GENERIC_TI_C_SOURCE)


#-----------------------------------------------------------------------------
# Group C64P
#-----------------------------------------------------------------------------
ifeq ($(C64P),1)
UNIVERSAL_FLAGS += -mv64+
endif


#-----------------------------------------------------------------------------
# Group EABI_TDEH
#-----------------------------------------------------------------------------
ifeq ($(C6XABI),1)
ifeq ($(EXCEPTIONS),1)
EABI_TDEH=1
endif
endif

ifeq ($(EABI_TDEH),1)
UNIVERSAL_FLAGS += -D__TI_TABLE_DRIVEN_EXCEPTIONS
CPP_FLAGS += --extern_c_can_throw

EABI_TDEH_CPP_SOURCE = \
	tdeh_unwinder.cpp \
	tdeh_cpp_abi.cpp \
	tdeh_pr_common.cpp \
	tdeh_init.cpp

CPP_SOURCE += $(EABI_TDEH_CPP_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group C6740
#-----------------------------------------------------------------------------
ifeq ($(C6740),1)
UNIVERSAL_FLAGS += -mv6740
endif


#-----------------------------------------------------------------------------
# Group EABI
#-----------------------------------------------------------------------------
ifeq ($(EABI),1)

EABI_CPP_C_SOURCE = \
	decode.c

CPP_C_SOURCE += $(EABI_CPP_C_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group NO_PARALLEL_LOADS
#-----------------------------------------------------------------------------
ifeq ($(NO_PARALLEL_LOADS),1)
UNIVERSAL_FLAGS += --no_parallel_loads
endif


#-----------------------------------------------------------------------------
# Group GENERIC_DINKUM
#-----------------------------------------------------------------------------

GENERIC_DINKUM_C_SOURCE = \
	signal.c \
	raise.c \
	fwide.c \
	stox.c

C_SOURCE += $(GENERIC_DINKUM_C_SOURCE)


GENERIC_DINKUM_CPP_SOURCE = \
	fiopen.cpp \
	iomanip.cpp \
	ios.cpp \
	iostream.cpp \
	limits.cpp \
	locale.cpp \
	locale0.cpp \
	nothrow.cpp \
	raisehan.cpp \
	string.cpp \
	strstrea.cpp \
	throw.cpp \
	wiostrea.cpp \
	wlocale.cpp \
	xfpostox.cpp \
	xlocale.cpp \
	xlocinfo.cpp

CPP_SOURCE += $(GENERIC_DINKUM_CPP_SOURCE)


GENERIC_DINKUM_CX0_SOURCE = \
	xatexit.cx0

CX0_SOURCE += $(GENERIC_DINKUM_CX0_SOURCE)


GENERIC_DINKUM_CX_SOURCE = \
	wchar.cx

CX_SOURCE += $(GENERIC_DINKUM_CX_SOURCE)


#-----------------------------------------------------------------------------
# Group C6600
#-----------------------------------------------------------------------------
ifeq ($(C6600),1)
UNIVERSAL_FLAGS += -mv6600
endif


#-----------------------------------------------------------------------------
# Group C_MEMCPY
#-----------------------------------------------------------------------------
ifeq ($(C_MEMCPY),1)
UNIVERSAL_FLAGS += -D_TI_USE_C_MEMCPY=1
endif


#-----------------------------------------------------------------------------
# Group BIG_ENDIAN
#-----------------------------------------------------------------------------
ifeq ($(BIG_ENDIAN),1)
UNIVERSAL_FLAGS += -me
endif


#-----------------------------------------------------------------------------
# Group GENERIC_MATH
#-----------------------------------------------------------------------------

GENERIC_MATH_C__SCHED_1_SOURCE = \
	acosh.c \
	sin.c

C__SCHED_1_SOURCE += $(GENERIC_MATH_C__SCHED_1_SOURCE)


GENERIC_MATH_C_SOURCE = \
	absd.c \
	absf.c \
	acos.c \
	acosf.c \
	acoshf.c \
	acot.c \
	acot2.c \
	acot2f.c \
	acotf.c \
	acoth.c \
	acothf.c \
	addd.c \
	addf.c \
	asin.c \
	asinf.c \
	asinh.c \
	asinhf.c \
	atan.c \
	atan2.c \
	atan2f.c \
	atanf.c \
	atanh.c \
	atanhf.c \
	ceil.c \
	ceilf.c \
	cmpd.c \
	cmpf.c \
	cos.c \
	cosf.c \
	cosh.c \
	coshf.c \
	cot.c \
	cotf.c \
	coth.c \
	cothf.c \
	cvtdf.c \
	cvtfd.c \
	div.c \
	divd.c \
	divf.c \
	exp.c \
	exp10.c \
	exp10f.c \
	exp2.c \
	exp2f.c \
	expf.c \
	fabs.c \
	fabsf.c \
	fixdb.c \
	fixdc.c \
	fixdi.c \
	fixdli.c \
	fixdlli.c \
	fixdsi.c \
	fixdu.c \
	fixdul.c \
	fixdull.c \
	fixdus.c \
	fixfb.c \
	fixfc.c \
	fixfi.c \
	fixfli.c \
	fixflli.c \
	fixfsi.c \
	fixfu.c \
	fixful.c \
	fixfull.c \
	fixfus.c \
	floor.c \
	floorf.c \
	fltbd.c \
	fltbf.c \
	fltcd.c \
	fltcf.c \
	fltid.c \
	fltif.c \
	fltlid.c \
	fltlif.c \
	fltllid.c \
	fltllif.c \
	fltsid.c \
	fltsif.c \
	fltud.c \
	fltuf.c \
	fltuld.c \
	fltulf.c \
	fltulld.c \
	fltullf.c \
	fltusd.c \
	fltusf.c \
	fmod.c \
	fmodf.c \
	fpclassify.c \
	fpclassifyf.c \
	frcaddd.c \
	frcaddf.c \
	frcdivd.c \
	frcdivf.c \
	frcmpyd.c \
	frcmpyd_div.c \
	frcmpyf.c \
	frcmpyf_div.c \
	frexp.c \
	frexpf.c \
	isfinite.c \
	isfinitef.c \
	isinf.c \
	isinff.c \
	isnan.c \
	isnanf.c \
	isnormal.c \
	isnormalf.c \
	ldexp.c \
	ldexpf.c \
	ldiv.c \
	lldiv.c \
	log.c \
	log10.c \
	log10f.c \
	log2.c \
	log2f.c \
	logf.c \
	modf.c \
	modff.c \
	modfl.c \
	mpyd.c \
	mpyf.c \
	negd.c \
	negf.c \
	pow.c \
	powf.c \
	powi.c \
	powif.c \
	renormd.c \
	renormf.c \
	round.c \
	roundf.c \
	rsqrt.c \
	rsqrtf.c \
	sinf.c \
	sinh.c \
	sinhf.c \
	sqrt.c \
	sqrtf.c \
	subd.c \
	subf.c \
	tanf.c \
	tanh.c \
	tanhf.c \
	trunc.c \
	truncf.c

C_SOURCE += $(GENERIC_MATH_C_SOURCE)


GENERIC_MATH_C__SCHED_2_SOURCE = \
	tan.c

C__SCHED_2_SOURCE += $(GENERIC_MATH_C__SCHED_2_SOURCE)


#-----------------------------------------------------------------------------
# Group NOASM_RTS
#-----------------------------------------------------------------------------
ifeq ($(VENC),1)
NOASM_RTS=1
endif

ifeq ($(NOASM_RTS),1)

NOASM_RTS_C_SOURCE = \
	divi_c.c \
	divu_c.c \
	remi_c.c \
	remu_c.c \
	strasgi_c.c

C_SOURCE += $(NOASM_RTS_C_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group C67P
#-----------------------------------------------------------------------------
ifeq ($(C67P),1)
UNIVERSAL_FLAGS += -mv67p
endif


#-----------------------------------------------------------------------------
# Group C6400
#-----------------------------------------------------------------------------
ifeq ($(C6400),1)
UNIVERSAL_FLAGS += -mv6400
endif


#-----------------------------------------------------------------------------
# Group COFFABI
#-----------------------------------------------------------------------------
ifeq ($(COFFABI),1)
UNIVERSAL_FLAGS += --abi=coffabi
endif


#-----------------------------------------------------------------------------
# Group C6700
#-----------------------------------------------------------------------------
ifeq ($(C6700),1)
UNIVERSAL_FLAGS += -mv6700
C__SCHED_1_FLAGS += -mf3
C__SCHED_2_FLAGS += -mf1
endif


#-----------------------------------------------------------------------------
# Group FULL_PORTABLE_EH
#-----------------------------------------------------------------------------
ifneq ($(C6XABI),1)
ifeq ($(EXCEPTIONS),1)
FULL_PORTABLE_EH=1
endif
endif

ifeq ($(FULL_PORTABLE_EH),1)

FULL_PORTABLE_EH_CPP_SOURCE = \
	eh_util.cpp \
	throw_edg.cpp

CPP_SOURCE += $(FULL_PORTABLE_EH_CPP_SOURCE)

endif



CPP_C_OBJS = $(patsubst %.c,$(OBJ)/%.obj,$(notdir $(CPP_C_SOURCE)))

$(CPP_C_OBJS): $(OBJ)/%.obj: %.c
	$(CC) $^ $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(CPP_FLAGS) -I$(INC) -fr $(OBJ) -fs $(OBJ) -ft $(OBJ)

LINASM_OBJS = $(patsubst %.sa,$(OBJ)/%.obj,$(notdir $(LINASM_SOURCE)))

$(LINASM_OBJS): $(OBJ)/%.obj: %.sa
	$(CC) $^ $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(C_FLAGS) -I$(INC) -fr $(OBJ) -fs $(OBJ) -ft $(OBJ)

CX_OBJS = $(patsubst %.cx,$(OBJ)/%.obj,$(notdir $(CX_SOURCE)))

$(CX_OBJS): $(OBJ)/%.obj: %.cx
	$(CC) $^ $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(C_FLAGS) -I$(INC) -fr $(OBJ) -fs $(OBJ) -ft $(OBJ)

C__SCHED_2_OBJS = $(patsubst %.c,$(OBJ)/%.obj,$(notdir $(C__SCHED_2_SOURCE)))

$(C__SCHED_2_OBJS): $(OBJ)/%.obj: %.c
	$(CC) $^ $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(C_FLAGS) $(C__SCHED_2_FLAGS) -I$(INC) -fr $(OBJ) -fs $(OBJ) -ft $(OBJ)

C_OBJS = $(patsubst %.c,$(OBJ)/%.obj,$(notdir $(C_SOURCE)))

$(C_OBJS): $(OBJ)/%.obj: %.c
	$(CC) $^ $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(C_FLAGS) -I$(INC) -fr $(OBJ) -fs $(OBJ) -ft $(OBJ)

C__SCHED_1_OBJS = $(patsubst %.c,$(OBJ)/%.obj,$(notdir $(C__SCHED_1_SOURCE)))

$(C__SCHED_1_OBJS): $(OBJ)/%.obj: %.c
	$(CC) $^ $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(C_FLAGS) $(C__SCHED_1_FLAGS) -I$(INC) -fr $(OBJ) -fs $(OBJ) -ft $(OBJ)

ASM_OBJS = $(patsubst %.asm,$(OBJ)/%.obj,$(notdir $(ASM_SOURCE)))

$(ASM_OBJS): $(OBJ)/%.obj: %.asm
	$(CC) $^ $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(C_FLAGS) -I$(INC) -fr $(OBJ) -fs $(OBJ) -ft $(OBJ)

CX0_OBJS = $(patsubst %.cx0,$(OBJ)/%.obj,$(notdir $(CX0_SOURCE)))

$(CX0_OBJS): $(OBJ)/%.obj: %.cx0
	$(CC) $^ $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(C_FLAGS) -I$(INC) -fr $(OBJ) -fs $(OBJ) -ft $(OBJ)

CPP_OBJS = $(patsubst %.cpp,$(OBJ)/%.obj,$(notdir $(CPP_SOURCE)))

$(CPP_OBJS): $(OBJ)/%.obj: %.cpp
	$(CC) $^ $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(CPP_FLAGS) -I$(INC) -fr $(OBJ) -fs $(OBJ) -ft $(OBJ)

library: $(CPP_C_OBJS) $(LINASM_OBJS) $(CX_OBJS) $(C__SCHED_2_OBJS) $(C_OBJS) $(C__SCHED_1_OBJS) $(ASM_OBJS) $(CX0_OBJS) $(CPP_OBJS)
	$(CD) $(OBJ); $(AR) -qa $(LIB) *.obj

info:
	@echo $(UNIVERSAL_FLAGS)
	@echo $(STANDARD_FLAGS)
	@echo $(EXTRA_FLAGS)
	@echo $(C_FLAGS)
	@echo $(CPP_FLAGS)
	@echo
	@echo $(C_OBJS)
	@echo $(CPP_OBJS)
