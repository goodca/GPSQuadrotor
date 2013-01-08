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
	double getXAngle();
	double getYAngle();
	double getZAngle();
	void correctGyro();
	void update();
	void startIMUThread();

	int getThreadRunning();
	void stopThread();
private:
	int threadRunning;
	int clkDiv;
	Accelerometer *acel;
	Gyroscope *gyro;
	double xGyroCorrection; //the amount the gyro is thought to be off
	double yGyroCorrection;
	double zGyroCorrection;
	double xGyroAngle; //what the gyro thinks it has gotten to, integration
	double yGyroAngle;
	double zGyroAngle;

	double xVelocity; //what the accelerometer thinks it has gotten to, integration
	double yVelocity;
	double zVelocity;

	pthread_t imuThread_t;
	void imuThread(void *obj);
	static void * start_thread(void *obj) {
		reinterpret_cast<IMU *>(obj)->imuThread(obj);
		return 0;
	}
};
#define MICRO_TO_WAIT 10000
} /* namespace std */
#endif /* IMU_H_ */
