# invoke SourceDir generated makefile for idle.p28L
idle.p28L: .libraries,idle.p28L
.libraries,idle.p28L: package/cfg/idle_p28L.xdl
	$(MAKE) -f C:\Users\lemue\Desktop\Joystick-Project\ArcadeStick/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\lemue\Desktop\Joystick-Project\ArcadeStick/src/makefile.libs clean

