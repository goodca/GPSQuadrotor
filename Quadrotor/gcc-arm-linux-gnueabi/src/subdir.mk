################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Accelerometer.cpp \
../src/Compass.cpp \
../src/Control.cpp \
../src/DM3730pwm.cpp \
../src/GPS.cpp \
../src/GPSNavigator.cpp \
../src/GPSWaypoints.cpp \
../src/GPScontrol.cpp \
../src/Gyroscope.cpp \
../src/IMU.cpp \
../src/Motor.cpp \
../src/PID.cpp \
../src/Quadrotor.cpp \
../src/RangeFinder.cpp \
../src/RemoteInput.cpp \
../src/Remotehandler.cpp \
../src/Sensors.cpp \
../src/Waypoint.cpp \
../src/i2c.cpp 

C_SRCS += \
../src/quadthread.c 

OBJS += \
./src/Accelerometer.o \
./src/Compass.o \
./src/Control.o \
./src/DM3730pwm.o \
./src/GPS.o \
./src/GPSNavigator.o \
./src/GPSWaypoints.o \
./src/GPScontrol.o \
./src/Gyroscope.o \
./src/IMU.o \
./src/Motor.o \
./src/PID.o \
./src/Quadrotor.o \
./src/RangeFinder.o \
./src/RemoteInput.o \
./src/Remotehandler.o \
./src/Sensors.o \
./src/Waypoint.o \
./src/i2c.o \
./src/quadthread.o 

C_DEPS += \
./src/quadthread.d 

CPP_DEPS += \
./src/Accelerometer.d \
./src/Compass.d \
./src/Control.d \
./src/DM3730pwm.d \
./src/GPS.d \
./src/GPSNavigator.d \
./src/GPSWaypoints.d \
./src/GPScontrol.d \
./src/Gyroscope.d \
./src/IMU.d \
./src/Motor.d \
./src/PID.d \
./src/Quadrotor.d \
./src/RangeFinder.d \
./src/RemoteInput.d \
./src/Remotehandler.d \
./src/Sensors.d \
./src/Waypoint.d \
./src/i2c.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	/usr/local/angstrom/arm/bin/arm-angstrom-linux-gnueabi-g++ -I/usr/local/angstrom/arm/arm-angstrom-linux-gnueabi/usr/include -O0 -g3 -Wall -c -pthread -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	/usr/local/angstrom/arm/bin/arm-angstrom-linux-gnueabi-gcc -I/usr/local/angstrom/arm/arm-angstrom-linux-gnueabi/usr/include -O0 -g3 -Wall -c -pthread -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


