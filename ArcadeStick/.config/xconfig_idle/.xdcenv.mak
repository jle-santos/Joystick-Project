#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_76_03_01/packages;C:/Users/Lemuel/OneDrive/CAPSTO~1/ROMALO~1/Code/ArcadeStick/.config
override XDCROOT = C:/ti/xdctools_3_51_01_18_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_76_03_01/packages;C:/Users/Lemuel/OneDrive/CAPSTO~1/ROMALO~1/Code/ArcadeStick/.config;C:/ti/xdctools_3_51_01_18_core/packages;..
HOSTOS = Windows
endif
