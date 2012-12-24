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
#include <iostream>

namespace std {

class Sensors {
public:
	Sensors();
	void runTest();
	void update();
	virtual ~Sensors();
	void correctGyro();

private:
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
