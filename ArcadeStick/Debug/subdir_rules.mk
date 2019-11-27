################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt --include_path="D:/ti/Projects/Joystick-Project/ArcadeStick" --include_path="D:/ti/bios_6_76_03_01/packages/ti/posix/ccs" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt --include_path="D:/ti/Projects/Joystick-Project/ArcadeStick" --include_path="D:/ti/bios_6_76_03_01/packages/ti/posix/ccs" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-469940431:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-469940431-inproc

build-469940431-inproc: ../idle.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"D:/ti/xdctools_3_51_01_18_core/xs" --xdcpath="D:/ti/bios_6_76_03_01/packages;" xdc.tools.configuro -o configPkg -t ti.targets.C28_large -p ti.platforms.tms320x28:TMS320F28027 -r release -c "D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS" --compileOptions "-g" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-469940431 ../idle.cfg
configPkg/compiler.opt: build-469940431
configPkg/: build-469940431


