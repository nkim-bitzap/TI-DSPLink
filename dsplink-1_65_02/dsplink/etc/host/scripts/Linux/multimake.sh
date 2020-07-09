echo off
#   =========================================================
#   DSP/BIOS LINK Configuration file.
#
#   CAUTION! This is a generated file.
#            All changes will be lost.
#
#   This file was generated on JUL 8, 2020  16:5:03
#   =========================================================
echo on
echo off
#   =========================================================
#   Build DSP side binary for OMAP3530
#   =========================================================
export TI_DSPLINK_BUILD_DEFAULTDSP=0
export TI_DSPLINK_DSPDEVICE=OMAP3530
export TI_DSPLINK_DSPDEVICE_EXTERNAL=
export TI_DSPLINK_DSPDISTRIBUTION=c64xxp_5.xx_linux
export TI_DSPLINK_DSPOS=DspBios
export TI_DSPLINK_DSPOSVERSION=5.XX
export TI_DSPLINK_PROCID=0
export TI_DSPLINK_DSPDEVICECLASS=C64XX
export TI_DSPLINK_DSPTEMPPATH=
echo on
gmake -f Makefile $@
echo off
export TI_DSPLINK_BUILD_DEFAULTDSP=
echo on


