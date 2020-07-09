# This make file is used by each BIOS example's makefile. It is for Linux 
# or Windows installations.

# The user needs to redefine the INSTALL_ROOT, XDCTOOLS_DIR 
# and CnnX_CODEGEN_ROOT. 
# variables below to point to <install_dir>, where <install_dir> 
# is the destination directory specified by the user during the installation.

# The purpose of this file is to define all global variables, used by each
# makefile, in one place to eliminate having to edit multiple files for the
# same desired change. 

# Because this file is included by makefiles, use forward slashes
# ("/") only.

# Define the full path of the root directory in which DSP/BIOS and XDCtools 
# are installed.

INSTALL_ROOT = <PATH to BIOS 5  Installation, i.e., C:/ti/bios_5_42_00_05>
XDCTOOLS_DIR = <PATH to included xdctools, i.e, C:/ti/bios_5_42_00_05/xdctools>

# I.E., Linux: /usr/local/bios_5_42_00_05
# 	Windows: "C:/ti/bios_5_42_00_05"
# 	Windows: "C:/ti/bios_5_42_00_05/xdctools"
# It is best to use short file names when building with makefile where 
# paths have spaces in the directory names.
# Make sure there are no spaces at the end of the path line.


# Define the full path of the root directory in which your PSL and RTDX lives.
COMPONENT_ROOT = $(INSTALL_ROOT)/packages/ti

PSCL_ROOT = $(COMPONENT_ROOT)/pscl
PMI_ROOT = $(COMPONENT_ROOT)/pmi
PSL_ROOT = $(COMPONENT_ROOT)/psl
RTDX_ROOT = $(COMPONENT_ROOT)/rtdx

# define location of code generation tools here. 
C6X_CODEGEN_ROOT = C:/ti/ccsv5/tools/compiler/c6000_<version>
C55X_CODEGEN_ROOT = C:/ti/ccsv5/tools/compiler/c5500_<version>
C28X_CODEGEN_ROOT = C:/ti/ccsv5/tools/compiler/c2000_<version>

# I.E., Linux: /opt/TI/C6000
# 	Windows: "C:/ti/ccsv5/tools/compiler/c6000_<version>"
# Make sure there are no spaces at the end of the path line.

# use this definition of REMOVE for Windows but
# comment it out for Solaris and Linux:
# REMOVE = $(XDCTOOLS_DIR)/bin/rm.exe -f

# use this definition of REMOVE for Solaris and Linux but
# comment it out for Windows:
REMOVE = rm -f

# define the paths to bios and platforms packages

BIOS_ROOT = $(INSTALL_ROOT)/packages/ti/bios
PLATFORMS_ROOT = $(INSTALL_ROOT)
