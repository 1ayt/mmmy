################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/Angle_Calculate.c \
../CODE/Balance.c \
../CODE/Motor_A.c \
../CODE/PIT_Init.c \
../CODE/encoder.c \
../CODE/iic.c \
../CODE/image.c \
../CODE/oled_iic.c 

OBJS += \
./CODE/Angle_Calculate.o \
./CODE/Balance.o \
./CODE/Motor_A.o \
./CODE/PIT_Init.o \
./CODE/encoder.o \
./CODE/iic.o \
./CODE/image.o \
./CODE/oled_iic.o 

COMPILED_SRCS += \
./CODE/Angle_Calculate.src \
./CODE/Balance.src \
./CODE/Motor_A.src \
./CODE/PIT_Init.src \
./CODE/encoder.src \
./CODE/iic.src \
./CODE/image.src \
./CODE/oled_iic.src 

C_DEPS += \
./CODE/Angle_Calculate.d \
./CODE/Balance.d \
./CODE/Motor_A.d \
./CODE/PIT_Init.d \
./CODE/encoder.d \
./CODE/iic.d \
./CODE/image.d \
./CODE/oled_iic.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/%.src: ../CODE/%.c CODE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fC:/Users/xqx/Desktop/TC264_Library/Example/Printf_Demo/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/%.o: ./CODE/%.src CODE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


