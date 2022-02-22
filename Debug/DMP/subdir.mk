################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DMP/IOI2C.c \
../DMP/MPU6050.c \
../DMP/inv_mpu.c \
../DMP/inv_mpu_dmp_motion_driver.c 

OBJS += \
./DMP/IOI2C.o \
./DMP/MPU6050.o \
./DMP/inv_mpu.o \
./DMP/inv_mpu_dmp_motion_driver.o 

COMPILED_SRCS += \
./DMP/IOI2C.src \
./DMP/MPU6050.src \
./DMP/inv_mpu.src \
./DMP/inv_mpu_dmp_motion_driver.src 

C_DEPS += \
./DMP/IOI2C.d \
./DMP/MPU6050.d \
./DMP/inv_mpu.d \
./DMP/inv_mpu_dmp_motion_driver.d 


# Each subdirectory must supply rules for building sources it contributes
DMP/%.src: ../DMP/%.c DMP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fC:/Users/xqx/Desktop/TC264_Library/Example/Printf_Demo/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

DMP/%.o: ./DMP/%.src DMP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


