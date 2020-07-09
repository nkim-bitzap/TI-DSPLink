#
#  This file contains the definitions and rules necessary to 
#  build an application for the C55 with GNU make.
#

#The cl55 acts as the compiler, assembler, and linker for C55x architectures.  
#The "-z" option in LD55 specifies that all options following the "-z" will be
#linker options.

CC55 = $(C55X_CODEGEN_ROOT)/bin/cl55
AS55 = $(C55X_CODEGEN_ROOT)/bin/cl55
LD55 = $(C55X_CODEGEN_ROOT)/bin/cl55 -z

# *** It is suggested that the "-v" or "-vcore" options be used in the 
#     compiler and assembler command lines to generate the most efficient 
#     code for the user's target device. For example:
# 
#     -vcore:2.2 
#
#     will generate code suited for execution on all 55x DSPs with the 2.2 CPU 
#     core (ie 5509A, OMAP1610/11/12, 5903, 5905, 5907, 5912, etc).
# 
#     The specific -v or -vcore options available can be found in the compiler 
#     user's manual.

#specify the C55x compiler options
CC55OPTS = -g -pdr -mg -I. -I.. -I$(BIOS_ROOT)/include \
    -I$(RTDX_ROOT)/include/c5500 -I$(C55X_CODEGEN_ROOT)/include

#specify the 55x assembler options
AS55OPTS = -g -mg -I. -I.. -I$(BIOS_ROOT)/include

#specify the 55x linker options
LD55OPTS = -c -x -w -I.. -I$(BIOS_ROOT)/lib \
    -I$(RTDX_ROOT)/lib/c5500 \
    -I$(PSL_ROOT)/lib -I$(C55X_CODEGEN_ROOT)/lib

TCONF = $(XDCTOOLS_DIR)/tconf

# Mark the *cfg.s55 file as "PRECIOUS" so that it is not deleted as an
# intermediate file by gmake

.PRECIOUS : %cfg.s55

#Rule for building the configuration files

%.c : %cfg.h

%.cdb %cfg.s55 %cfg.h55 %cfg.h %cfg_c.c %cfg.cmd : %.tcf
	$(TCONF) $(TCONFOPTS) $<

#  Pattern rules to build C55 executables

%.obj : ../%.cpp
	$(CC55) $(CC55OPTS) $(CC55FLAGS) $<

%.obj : %.cpp
	$(CC55) $(CC55OPTS) $(CC55FLAGS) $<

%.obj : ../%.c
	$(CC55) $(CC55OPTS) $(CC55FLAGS) $<

%.obj : %.c
	$(CC55) $(CC55OPTS) $(CC55FLAGS) $<

%.obj : %.asm
	$(AS55) $(AS55OPTS) $(AS55FLAGS) $<

%.obj : %.s55
	$(AS55) $(AS55OPTS) $(AS55FLAGS) $<

%.out : %.obj
	$(LD55) $(LD55OPTS) $(LD55FLAGS) -o $@ $^
