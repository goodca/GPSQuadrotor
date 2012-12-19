################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Control.cpp \
../src/GPScontrol.cpp \
../src/Motor.cpp \
../src/Quadrotor.cpp \
../src/Sensors.cpp \
../src/Waypoint.cpp 

OBJS += \
./src/Control.o \
./src/GPScontrol.o \
./src/Motor.o \
./src/Quadrotor.o \
./src/Sensors.o \
./src/Waypoint.o 

CPP_DEPS += \
./src/Control.d \
./src/GPScontrol.d \
./src/Motor.d \
./src/Quadrotor.d \
./src/Sensors.d \
./src/Waypoint.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


