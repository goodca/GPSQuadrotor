/*
 * IMU.h
 *
 *  Created on: Dec 27, 2012
 *      Author: chris
 */

#ifndef IMU_H_
#define IMU_H_
//#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "Gyroscope.h"
#include "Accelerometer.h"
#include "Compass.h"
#include <unistd.h>
#include <pthread.h>

namespace std {

class IMU {
public:
	IMU();
	virtual ~IMU();
	void init();
	double getXAccel();
	double getYAccel();
	double getZAccel();
	double getXVelocity();
	double getYVelocity();
	double getZVelocity();
	double getXAngleSpeed();
	double getYAngleSpeed();
	double getZAngleSpeed();
	double getXAngleAcceleration();
	double getYAngleAcceleration();
	double getZAngleAcceleration();
	double getXAngle();
	double getYAngle();
	double getZAngle();


	void update();
	void startIMUThread();

	int getThreadRunning();
	void stopThread();
private:
	Accelerometer *acel;
	Gyroscope *gyro;
	Compass *comp;
	int threadRunning;
	int clkDiv;

	double xGyroCorrection; //the amount the gyro is thought to be off
	double yGyroCorrection;
	double zGyroCorrection;

	double xGyroAngle; //what the gyro thinks it has gotten to, integration
	double yGyroAngle;
	double zGyroAngle;

	double xAngleVelocity; //rate the gyro thinks it is rotating
	double yAngleVelocity;
	double zAngleVelocity;

	double xAngleAcceleration; //rate of acceleration calculated from the gyro
	double yAngleAcceleration;
	double zAngleAcceleration;

	double lastXAngleVelocity; //temp placeholder in order to calculate acceleration
	double lastYAngleVelocity;
	double lastZAngleVelocity;

	double xVelocityCorrection; //the amount the velocity is thought to be off
	double yVelocityCorrection;
	double zVelocityCorrection;

	double xVelocity; //what the accelerometer thinks it has gotten to, integration
	double yVelocity;
	double zVelocity;

	double xAcceleration; //acceleration as reported by the accelerometer
	double yAcceleration;
	double zAcceleration;

	double upperMagnitudeForStable; //bounds for what the magnitude is to be considered for the accelerometer to say we aren't accelerating
	double lowerMagnitudeForStable;

	pthread_t imuThread_t;
	void correctGyro();
	void correctHeading();
	void imuThread(void *obj);
	static void * start_thread(void *obj) {
		reinterpret_cast<IMU *>(obj)->imuThread(obj);
		return 0;
	}
};
#define MICRO_TO_WAIT 10000
#define NUM_MICROS_IN_ONE 1000000
#define FRACTION_TO_CORRECT 20
#define COMPASS_FRACTION_TO_CORRECT 5000
} /* namespace std */
#endif /* IMU_H_ */
