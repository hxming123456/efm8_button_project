################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/EFM8BB10F2G-A-QFN20_main.c \
../src/InitDevice.c 

OBJS += \
./src/EFM8BB10F2G-A-QFN20_main.OBJ \
./src/InitDevice.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/EFM8BB10F2G-A-QFN20_main.OBJ: E:/rj/simplicity\ studio/installfile/developer/sdks/8051/v4.0.3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h E:/project/silicon\ woekspace/EFM8BB10F2G-A-QFN20/inc/InitDevice.h C:/Keil/C51/INC/STDIO.H E:/rj/simplicity\ studio/installfile/developer/sdks/8051/v4.0.3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h E:/rj/simplicity\ studio/installfile/developer/sdks/8051/v4.0.3/Device/shared/si8051Base/si_toolchain.h E:/rj/simplicity\ studio/installfile/developer/sdks/8051/v4.0.3/Device/shared/si8051Base/stdint.h E:/rj/simplicity\ studio/installfile/developer/sdks/8051/v4.0.3/Device/shared/si8051Base/stdbool.h

src/InitDevice.OBJ: E:/rj/simplicity\ studio/installfile/developer/sdks/8051/v4.0.3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h E:/project/silicon\ woekspace/EFM8BB10F2G-A-QFN20/inc/InitDevice.h E:/rj/simplicity\ studio/installfile/developer/sdks/8051/v4.0.3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h E:/rj/simplicity\ studio/installfile/developer/sdks/8051/v4.0.3/Device/shared/si8051Base/si_toolchain.h E:/rj/simplicity\ studio/installfile/developer/sdks/8051/v4.0.3/Device/shared/si8051Base/stdint.h E:/rj/simplicity\ studio/installfile/developer/sdks/8051/v4.0.3/Device/shared/si8051Base/stdbool.h


