#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/ti/bios_6_76_03_01/packages
override XDCROOT = D:/ti/xdctools_3_51_01_18_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/ti/bios_6_76_03_01/packages;D:/ti/xdctools_3_51_01_18_core/packages;..
HOSTOS = Windows
endif
