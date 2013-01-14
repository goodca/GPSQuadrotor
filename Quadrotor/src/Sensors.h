/*
 * Sensors.h
 *
 *  Created on: Dec 23, 2012
 *      Author: chris
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include "Gyroscope.h"
#include "Accelerometer.h"
#include "GPS.h"
#include "Compass.h"
#include "IMU.h"
#include <iostream>
#include <fcntl.h>      /*Enables use of flags to modify open(), read(), write() functions*/
#include <unistd.h>     /*Enables use of open(), read(), write()*/
#include <stdio.h>
#include <pthread.h>

namespace std {

class Sensors {

public:
	Sensors();
	void runTest();
	void update();
	virtual ~Sensors();

	double getXAngle(); //angle in degrees, 0 means level, positive is clockwise
	double getYAngle(); //angle in degrees, 0 means level, positive means looking up
	double getZAngle(); //angle in degrees, 0 is north, clockwise, no negatives, wraps at 360
	double getXAngleSpeed(); //in degrees/second
	double getYAngleSpeed(); //in degrees/second
	double getZAngleSpeed(); //in degrees/second
	double getXAngleAcceleration(); //in degrees/second^2
	double getYAngleAcceleration(); //in degrees/second^2
	double getZAngleAcceleration(); //in degrees/second^2
	double getXVelocity(); //velocity in Meters per second
	double getYVelocity(); //velocity in Meters per second
	double getZVelocity(); //velocity in Meters per second
	double getXAcceleration(); //in meters/second^2
	double getYAcceleration(); //in meters/second^2
	double getZAcceleration(); //in meters/second^2
	double getLatitude(); //in degrees
	double getLongtitude(); //in degrees
	double getHeight(); //not sure on units yet

	void startSensorsThreads();
	int getThreadRunning();
	void stopThread();

private:
	int threadRunning;
	pthread_t sensorsThread_t;

	Compass *comp;
	GPS *gps;
	IMU *imu;
	void sensorsThread(void *obj);
	static void * start_thread(void *obj) {
		reinterpret_cast<Sensors *>(obj)->sensorsThread(obj);
		return 0;
	}

	double xAngle;
	double yAngle;
	double zAngle;
	double xVelocity;
	double yVelocity;
	double zVelocity;



};

} /* namespace std */
#endif /* SENSORS_H_ */
