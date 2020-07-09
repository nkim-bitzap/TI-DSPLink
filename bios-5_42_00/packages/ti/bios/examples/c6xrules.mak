#
#  This file contains the definitions and rules necessary to 
#  build an application for the C62, C64 and C67 with GNU make.
#

#The cl6x acts as the compiler, assembler, and linker for C6x architectures.  
#The "-z" option in LD6x specifies that all options following the "-z" will be
#linker options.

CC6x = $(C6X_CODEGEN_ROOT)/bin/cl6x
AS6x = $(C6X_CODEGEN_ROOT)/bin/cl6x
LD6x = $(C6X_CODEGEN_ROOT)/bin/cl6x -z

#specify the C6x compiler options
CC6xOPTS = -g -pdr -ml0 -I. -I.. -I$(BIOS_ROOT)/include \
    -I$(RTDX_ROOT)/include/c6000 -I$(C6X_CODEGEN_ROOT)/include

#specify the 6x assembler options
AS6xOPTS = -g -I. -I.. -I$(BIOS_ROOT)/include

#specify the 6x linker options
LD6xOPTS = -c -x -w -I.. -I$(BIOS_ROOT)/lib \
    -I$(PSCL_ROOT)/lib \
    -I$(PMI_ROOT)/lib \
    -I$(RTDX_ROOT)/lib/c6000 \
    -I$(C6X_CODEGEN_ROOT)/lib

TCONF = $(XDCTOOLS_DIR)/tconf

# Mark the *cfg.s62 file as "PRECIOUS" so that it is not deleted as an
# intermediate file by gmake

.PRECIOUS : %cfg.s62

#Rule for building the configuration files

%.cdb %cfg.s62 %cfg.h62 %cfg.h %cfg_c.c %cfg.cmd : %.tcf
	$(TCONF) $(TCONFOPTS) $<

#  Pattern rules to build C6000 executables

%.obj : ../%.cpp
	$(CC6x) $(CC6xOPTS) $(CC6xFLAGS) $<

%.obj : %.cpp
	$(CC6x) $(CC6xOPTS) $(CC6xFLAGS) $<

%.obj : ../%.c
	$(CC6x) $(CC6xOPTS) $(CC6xFLAGS) $<

%.obj : %.c
	$(CC6x) $(CC6xOPTS) $(CC6xFLAGS) $<

%.obj : %.s62
	$(AS6x) $(AS6xOPTS) $(AS6xFLAGS) $<

%.out : %.obj
	$(LD6x) $(LD6xOPTS) $(LD6xFLAGS) -o $@ $^
