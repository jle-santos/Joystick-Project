################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Apps/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="D:/Work/Joystick-Project-master/ArcadeStick" --include_path="C:/Apps/ti/bios_6_76_00_08/packages/ti/posix/ccs" --include_path="C:/Apps/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Apps/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="D:/Work/Joystick-Project-master/ArcadeStick" --include_path="C:/Apps/ti/bios_6_76_00_08/packages/ti/posix/ccs" --include_path="C:/Apps/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-469940431:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-469940431-inproc

build-469940431-inproc: ../idle.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/Apps/ti/ccs901/xdctools_3_55_00_11_core/xs" --xdcpath="C:/Apps/ti/bios_6_76_00_08/packages;" xdc.tools.configuro -o configPkg -t ti.targets.C28_large -p ti.platforms.tms320x28:TMS320F28027 -r release -c "C:/Apps/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS" --compileOptions "-g" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-469940431 ../idle.cfg
configPkg/compiler.opt: build-469940431
configPkg/: build-469940431


