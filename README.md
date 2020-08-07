# TI-OMAP3-DSPLink
Port of the TI DSPLink module to the kernel 4.19.127 for the BeagleBoard C4

This project deals with porting of the original TI DSPLink kernel module to
work with more recent Linux kernels (4.19 in my case) in order to utilize
the OMAP3 DSP on a BeagleBoard C4 for compiler development experiments.

For those who prefer to deal with a plain kernel module instead of messing
with TI CCS (with its support for the BeagleBoard being traditionally very
lacking in absense of an additional (expensive) JTAG debugger).

As of 2020, the most Howto's on how to get the DSP running on the BeagleBoard
are very dated/not applicable. Yet the hardware (C4) is still flexible and
powerful enough to present a nice platform for various embedded development
experiments.


CONTAINS: bios-5_42_00

CONTAINS: dsplink-1_65_02

CONTAINS: GPP/DSP examples

DOES NOT CONTAIN: TI CGT (version used 7.3.23)

DOES NOT CONTAIN: TI XDC tools (version used 3.16.02.32)


Every required package is still available via TI's public site, most are not
maintained anymore though and may soon disappear entirely. Both, the module
as well as the DSPBIOS compile fine for the kernel 4.19.127 (see R.CNelson).

Current status: LOOP, MESSAGE, READWRITE and a custom AES_RIJNDAEL example
appear to be functional so far.
