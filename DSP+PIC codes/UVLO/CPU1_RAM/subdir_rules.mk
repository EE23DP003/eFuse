################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -Ooff --include_path="C:/Users/Abhinav/OneDrive - IIT Dharwad/Documents/GitHub/E-Fuse-Temp-codes/DSP+PIC codes/UVLO" --include_path="C:/Users/Abhinav/OneDrive - IIT Dharwad/Documents/GitHub/E-Fuse-Temp-codes/DSP+PIC codes/UVLO/device" --include_path="C:/ti/c2000/C2000Ware_5_01_00_00/driverlib/f2837xd/driverlib" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=_LAUNCHXL_F28379D --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/Abhinav/OneDrive - IIT Dharwad/Documents/GitHub/E-Fuse-Temp-codes/DSP+PIC codes/UVLO/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-389552017: ../lab_blinkyled_launchpad.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1260/ccs/utils/sysconfig_1.19.0/sysconfig_cli.bat" --script "C:/Users/Abhinav/OneDrive - IIT Dharwad/Documents/GitHub/E-Fuse-Temp-codes/DSP+PIC codes/UVLO/lab_blinkyled_launchpad.syscfg" -o "syscfg" -s "C:/ti/c2000/C2000Ware_5_01_00_00/.metadata/sdk.json" -b "/boards/LAUNCHXL_F28379D" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-389552017 ../lab_blinkyled_launchpad.syscfg
syscfg/board.h: build-389552017
syscfg/board.cmd.genlibs: build-389552017
syscfg/board.opt: build-389552017
syscfg/pinmux.csv: build-389552017
syscfg/epwm.dot: build-389552017
syscfg/adc.dot: build-389552017
syscfg/c2000ware_libraries.cmd.genlibs: build-389552017
syscfg/c2000ware_libraries.opt: build-389552017
syscfg/c2000ware_libraries.c: build-389552017
syscfg/c2000ware_libraries.h: build-389552017
syscfg/clocktree.h: build-389552017
syscfg: build-389552017

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -Ooff --include_path="C:/Users/Abhinav/OneDrive - IIT Dharwad/Documents/GitHub/E-Fuse-Temp-codes/DSP+PIC codes/UVLO" --include_path="C:/Users/Abhinav/OneDrive - IIT Dharwad/Documents/GitHub/E-Fuse-Temp-codes/DSP+PIC codes/UVLO/device" --include_path="C:/ti/c2000/C2000Ware_5_01_00_00/driverlib/f2837xd/driverlib" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=_LAUNCHXL_F28379D --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/Abhinav/OneDrive - IIT Dharwad/Documents/GitHub/E-Fuse-Temp-codes/DSP+PIC codes/UVLO/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


