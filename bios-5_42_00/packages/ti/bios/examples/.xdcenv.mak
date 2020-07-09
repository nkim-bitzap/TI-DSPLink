#
_XDCBUILDCOUNT = 1
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /db/ztree/library/trees/xdctools/xdctools-q29/src
override XDCROOT = /db/rtree/install/trees/products/xdcprod/xdcprod-q29/product/Linux/xdctools_3_24_01_29
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /db/ztree/library/trees/xdctools/xdctools-q29/src;/db/rtree/install/trees/products/xdcprod/xdcprod-q29/product/Linux/xdctools_3_24_01_29/packages;../../..
HOSTOS = Linux
endif
