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
#include <iostream>
#include <fcntl.h>      /*Enables use of flags to modify open(), read(), write() functions*/
#include <unistd.h>     /*Enables use of open(), read(), write()*/
#include <stdio.h>

namespace std {

class Sensors {
public:
	Sensors();
	void runTest();
	void update();
	virtual ~Sensors();
	void correctGyro();

private:
	GPS *gps;
	Gyroscope *gyro;
	Accelerometer *acel;
	double xGyroCorrection; //the amount the gyro is thought to be off
	double yGyroCorrection;
	double zGyroCorrection;
	double xInt;
	double yInt;
	double zInt;
};

} /* namespace std */
#endif /* SENSORS_H_ */
