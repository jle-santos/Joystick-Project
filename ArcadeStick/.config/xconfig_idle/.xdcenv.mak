#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/Apps/ti/bios_6_76_00_08/packages;D:/Work/Joystick-Project-master/ArcadeStick/.config
override XDCROOT = C:/Apps/ti/ccs901/xdctools_3_55_00_11_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/Apps/ti/bios_6_76_00_08/packages;D:/Work/Joystick-Project-master/ArcadeStick/.config;C:/Apps/ti/ccs901/xdctools_3_55_00_11_core/packages;..
HOSTOS = Windows
endif
