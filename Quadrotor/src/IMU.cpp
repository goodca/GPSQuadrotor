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
	gyro->init();
	gyro->update();
	acel->init();
	acel->update();
	int variable = 0;
//	pthread_create(&imuThread, 0, , this);
	printf("About to start new thread\n");
	fflush(stdout);
//	pthread_create(&imuThread, 0, &start_thread, (void *) &variable);
//	launch_pthread(&imuThread, 1, 99, start_thread, (void *) &variable);

	return;
}
double IMU::getXAccel() {
	return 0;
}
double IMU::getYAccel() {
	return 0;
}
double IMU::getZAccel() {
	return 0;
}
double IMU::getXAngle() {
	return 0;
}
double IMU::getYAngle() {
	return 0;
}
double IMU::getZAngle() {
	return 0;
}
void IMU::correctGyro() {
	return;
}
//static void imuRun(void *p) {
//	while (1) {
//		printf("IMU\n");
//		usleep(250000);
//	}
//	return NULL;
//}

IMU::~IMU() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
