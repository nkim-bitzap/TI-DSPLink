#
#  This file contains the definitions and rules necessary to 
#  build an application for the C28 with GNU make.
#

#The cl2000 acts as the compiler, assembler, and linker for C28x architectures.
#The "-z" option in LD28 specifies that all options following the "-z" will be
#linker options.

CC28 = $(C28X_CODEGEN_ROOT)/bin/cl2000
AS28 = $(C28X_CODEGEN_ROOT)/bin/cl2000
LD28 = $(C28X_CODEGEN_ROOT)/bin/cl2000 -z

#specify the C28x compiler options
CC28OPTS = -g -pdr -I. -I.. -I$(BIOS_ROOT)/include \
    -I$(RTDX_ROOT)/include/c2000 -I$(C28X_CODEGEN_ROOT)/include

#specify the 28x assembler options
AS28OPTS = -g -I. -I.. -I$(BIOS_ROOT)/include

#specify the 28x linker options
LD28OPTS = -c -x -w -I.. -I$(BIOS_ROOT)/lib \
    -I$(RTDX_ROOT)/lib/c2000 \
    -I$(C28X_CODEGEN_ROOT)/lib

TCONF = $(XDCTOOLS_DIR)/tconf

# Mark the *cfg.s28 file as "PRECIOUS" so that it is not deleted as an
# intermediate file by gmake

.PRECIOUS : %cfg.s28

#Rule for building the configuration files

%.cdb %cfg.s28 %cfg.h28 %cfg.h %cfg_c.c %cfg.cmd : %.tcf
	$(TCONF) $(TCONFOPTS) $<

#  Pattern rules to build C2000 executables

%.obj : ../%.cpp
	$(CC28) $(CC28OPTS) $(CC28FLAGS) $<

%.obj : %.cpp
	$(CC28) $(CC28OPTS) $(CC28FLAGS) $<

%.obj : ../%.c
	$(CC28) $(CC28OPTS) $(CC28FLAGS) $<

%.obj : %.c
	$(CC28) $(CC28OPTS) $(CC28FLAGS) $<

%.obj : %.s28
	$(AS28) $(AS28OPTS) $(AS28FLAGS) $<

%.out : %.obj
	$(LD28) $(LD28OPTS) $(LD28FLAGS) -o $@ $^
