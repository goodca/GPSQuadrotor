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
	void startIMU();


	//static void imuRun(void *p);
private:
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

	pthread_t imuThread;
	static void * start_thread(void *obj)
	    {
	        //All we do here is call the do_work() function
			printf("in start_thread\n");
	        reinterpret_cast<IMU *>(obj)->getZAngle();
	    }


//	static void start_thread(void *obj) {
//		//All we do here is call the do_work() function
//		printf("In start_thread\n");
//		fflush(stdout);
//
//		reinterpret_cast<IMU *>(obj)->do_work();
//	}
//	void do_work() {
//		printf("in do_work\n");
//		fflush(stdout);
//		while (true) {
//			printf("IMU\n");
//		}
//	}

};
extern "C" void * start_IMU_thread2(void *var);



} /* namespace std */
#endif /* IMU_H_ */