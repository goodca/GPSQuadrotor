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
#include "Thread.h"

namespace std {

class Sensors {
public:
	Sensors();
	void runTest();
	void update();
	virtual ~Sensors();


private:
	Compass *comp;
	GPS *gps;
	IMU *imu;
};

} /* namespace std */
#endif /* SENSORS_H_ */
