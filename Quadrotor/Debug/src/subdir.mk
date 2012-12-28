################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Accelerometer.cpp \
../src/Compass.cpp \
../src/Control.cpp \
../src/GPS.cpp \
../src/GPScontrol.cpp \
../src/Gyroscope.cpp \
../src/IMU.cpp \
../src/Motor.cpp \
../src/Quadrotor.cpp \
../src/Sensors.cpp \
../src/Thread.cpp \
../src/Waypoint.cpp \
../src/i2c.cpp 

OBJS += \
./src/Accelerometer.o \
./src/Compass.o \
./src/Control.o \
./src/GPS.o \
./src/GPScontrol.o \
./src/Gyroscope.o \
./src/IMU.o \
./src/Motor.o \
./src/Quadrotor.o \
./src/Sensors.o \
./src/Thread.o \
./src/Waypoint.o \
./src/i2c.o 

CPP_DEPS += \
./src/Accelerometer.d \
./src/Compass.d \
./src/Control.d \
./src/GPS.d \
./src/GPScontrol.d \
./src/Gyroscope.d \
./src/IMU.d \
./src/Motor.d \
./src/Quadrotor.d \
./src/Sensors.d \
./src/Thread.d \
./src/Waypoint.d \
./src/i2c.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fpermissive -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


