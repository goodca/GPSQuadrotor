/*
 * IMU.cpp
 *
 *  Created on: Dec 27, 2012
 *      Author: chris
 */

#include "IMU.h"

namespace std {

IMU::IMU() {
	// TODO Auto-generated constructor stub

}

void IMU::init() {
	gyro = new Gyroscope;
	acel = new Accelerometer;
//	comp = new Compass;
	printf("Initializing gyro\n");
	gyro->init();
	gyro->update();
	printf("Initializing accelerometer\n");
	acel->init();
	acel->update();
	printf("Initializing Compass\n");
//	comp->init();

	xGyroCorrection = 0;
	yGyroCorrection = 0;
	zGyroCorrection = 0;
	xGyroAngle = 0;
	yGyroAngle = 0;
	zGyroAngle = 0;
	xVelocityCorrection = 0;
	xVelocity = 0;
	yVelocityCorrection = 0;
	yVelocity = 0;
	zVelocityCorrection = 0;
	zVelocity = 0;

	clkDiv = 0;
	lowerMagnitudeForStable = 0.95;
	upperMagnitudeForStable = 1.05;

	return;
}

void IMU::update() {
	clkDiv++;
	gyro->update();
	acel->update();
//	comp->update();

	xAcceleration = acel->getX();
	yAcceleration = acel->getY();
	zAcceleration = acel->getZ();
	xAngleVelocity = gyro->getX();
	yAngleVelocity = gyro->getY();
	zAngleVelocity = gyro->getZ();

	xAngleAcceleration = (xAngleVelocity - lastXAngleVelocity) / MICRO_TO_WAIT;
	yAngleAcceleration = (yAngleVelocity - lastYAngleVelocity) / MICRO_TO_WAIT;
	zAngleAcceleration = (zAngleVelocity - lastZAngleVelocity) / MICRO_TO_WAIT;
	lastXAngleVelocity = xAngleVelocity;
	lastYAngleVelocity = yAngleVelocity;
	lastZAngleVelocity = zAngleVelocity;

	xGyroAngle += xAngleVelocity * MICRO_TO_WAIT / NUM_MICROS_IN_ONE;
	yGyroAngle += yAngleVelocity * MICRO_TO_WAIT / NUM_MICROS_IN_ONE;
	zGyroAngle += zAngleVelocity * MICRO_TO_WAIT / NUM_MICROS_IN_ONE;

	xVelocity += xAcceleration * MICRO_TO_WAIT / NUM_MICROS_IN_ONE;
	yVelocity += yAcceleration * MICRO_TO_WAIT / NUM_MICROS_IN_ONE;
	zVelocity += zAcceleration * MICRO_TO_WAIT / NUM_MICROS_IN_ONE;

	if ((acel->getMagnitude() > lowerMagnitudeForStable)
			&& (acel->getMagnitude() < upperMagnitudeForStable)) {
		correctGyro();
	} else {
		//do something maybe?
	}

	if (clkDiv > 50) {
//		printf("Corrected x: %f\n", getXAngle());
//		printf("Corrected y: %f\n", getYAngle());
//		printf("Corrected z: %f\n", getZAngle());
//		printf("Compass says %f degrees \n\n",
////				comp->getHeading(getXAngle(), getYAngle()));
//				comp->getHeading(0,0));
		clkDiv += -50;
	}
	correctHeading();

	return;
}
double IMU::getXAccel() {
	return xAcceleration;
}
double IMU::getYAccel() {
	return yAcceleration;
}
double IMU::getZAccel() {
	return zAcceleration;
}
double IMU::getXVelocity() {
	return xVelocity + xVelocityCorrection;
}
double IMU::getYVelocity() {
	return yVelocity + yVelocityCorrection;
}
double IMU::getZVelocity() {
	return zVelocity + zVelocityCorrection;
}

double IMU::getXAngleSpeed() {
	return xAngleAcceleration;
}
double IMU::getYAngleSpeed() {
	return yAngleAcceleration;
}
double IMU::getZAngleSpeed() {
	return zAngleAcceleration;
}
double IMU::getXAngle() {
	return xGyroAngle + xGyroCorrection;
}
double IMU::getYAngle() {
	return yGyroAngle + yGyroCorrection;
}
double IMU::getZAngle() {
	return zGyroAngle + zGyroCorrection;
}
double IMU::getXAngleAcceleration() {
	return xAngleAcceleration;
}
double IMU::getYAngleAcceleration() {
	return yAngleAcceleration;
}
double IMU::getZAngleAcceleration() {
	return zAngleAcceleration;
}
void IMU::correctGyro() {
	xGyroCorrection += (acel->getRoll() - (xGyroAngle + xGyroCorrection))
			/ FRACTION_TO_CORRECT;
	yGyroCorrection += (acel->getPitch() - (yGyroAngle + yGyroCorrection))
			/ FRACTION_TO_CORRECT;
	return;
}
void IMU::correctHeading() {
//	zGyroCorrection += (comp->getHeading(getXAngle(), getYAngle())
//			- (zGyroAngle + zGyroCorrection)) / COMPASS_FRACTION_TO_CORRECT;
	return;
}
void IMU::startIMUThread() {
	threadRunning = 1;
	pthread_create(&imuThread_t, 0, &IMU::start_thread, this);
}

void IMU::imuThread(void *obj) {
	//cast the obj to a thread to get original instance
	IMU *threadIMU = (IMU *) obj;
	threadIMU->init();

	while (threadIMU->getThreadRunning()) {
		threadIMU->update();
		usleep(MICRO_TO_WAIT);
	}
	return;
}

int IMU::getThreadRunning() {
	return threadRunning;
}
void IMU::stopThread() {
	threadRunning = 0;
	return;
}
IMU::~IMU() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
