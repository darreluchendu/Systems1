################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/date.c \
../src/tldlist.c \
../src/tldmonitor.c 

O_SRCS += \
../src/date.o \
../src/tldlist.o \
../src/tldmonitor.o 

OBJS += \
./src/date.o \
./src/tldlist.o \
./src/tldmonitor.o 

C_DEPS += \
./src/date.d \
./src/tldlist.d \
./src/tldmonitor.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


