# invoke SourceDir generated makefile for idle.p28L
idle.p28L: .libraries,idle.p28L
.libraries,idle.p28L: package/cfg/idle_p28L.xdl
	$(MAKE) -f D:\ti\Projects\Joystick-Project\ArcadeStick/src/makefile.libs

clean::
	$(MAKE) -f D:\ti\Projects\Joystick-Project\ArcadeStick/src/makefile.libs clean

