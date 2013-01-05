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
	printf("Initializing gyro\n");
	gyro->init();
	gyro->update();
	printf("Initializing accelerometer\n");
	acel->init();
	acel->update();
	xGyroCorrection = 0;
	yGyroCorrection = 0;
	zGyroCorrection = 0;

	int variable = 0;
//	pthread_create(&imuThread, 0, , this);
//	printf("About to start new thread\n");
//	fflush(stdout);
//	pthread_create(&imuThread, 0, &start_thread, (void *) &variable);
//	launch_pthread(&imuThread, 1, 99, start_IMU_thread2, (void *) &variable);

	return;
}

void IMU::update() {
	int uToWait = 10000;
	int clkDiv = 0;
//	while (true) {
	clkDiv++;
	gyro->update();
	//		usleep(uToWait / 2);
	acel->update();
	xGyroAngle += gyro->getX() * uToWait / 1000000;
	yGyroAngle += gyro->getY() * uToWait / 1000000;
	zGyroAngle += gyro->getZ() * uToWait / 1000000;

	if (clkDiv > 50) {
		printf("\n");
//						printf("X Raw: %f\n", gyro->getX());
//						printf("Y Raw: %f\n", gyro->getY());
//						printf("Z Raw: %f\n", gyro->getZ());
		printf("acel x: %f\n", acel->getX());
		printf("acel y: %f\n", acel->getY());
		printf("acel z: %f\n", acel->getZ());
		printf("Uncorrected Gyro x; %f\n", xGyroAngle);
		printf("Uncorrected Gyro y; %f\n", yGyroAngle);
		printf("Uncorrected Gyro z; %f\n", zGyroAngle);
		//			printf("Gyro x; %f\n", xInt + xGyroCorrection);
		//			printf("Gyro y; %f\n", yInt + yGyroCorrection);

		//			printf("Accel x; %f\n", xAcel);
		//			printf("Accel y; %f\n", yAcel);
		//			printf("Accel z; %f\n", zAcel);
		printf("magnitude: %f\n", acel->getMagnitude());
		if ((acel->getMagnitude() > 0.95) && (acel->getMagnitude() < 1.05)) {

			//				printf("total magnitude: %f\n", magnitude);
			//				printf("Roll: %f*\n", acel->getRoll());
			//				printf("Pitch: %f*\n", acel->getPitch());
			correctGyro();
			printf("roll: %f\n", acel->getRoll());
			printf("pitch: %f\n", acel->getPitch());
//				double angleFromComp;yGyroCorrection += acel->getPitch() - (yGyroAngle + yGyroCorrection);
//				angleFromComp = comp->tiltComponsation(
//						acel->getPitch() * pi / 180, acel->getRoll() * pi / 180)
//						* 180 / 3.14159;
			//				printf("heading is %f\n",
			//						(comp->tiltComponsation(acel->getRoll(),
			//								acel->getPitch()))*180/3.14159);
//				printf("heading is %f\n", angleFromComp);
//				if ((angleFromComp >= 337.5) || (angleFromComp <= 22.5)) {
//					printf("N\n");
//				} else if ((angleFromComp >= 22.5) && (angleFromComp <= 67.5)) {
//					printf("NE\n");
//				} else if ((angleFromComp >= 67.5)
//						&& (angleFromComp <= 112.5)) {
//					printf("E\n");
//				} else if ((angleFromComp >= 112.5)
//						&& (angleFromComp <= 157.5)) {
//					printf("SE\n");
//				} else if ((angleFromComp >= 157.5)
//						&& (angleFromComp <= 202.5)) {
//					printf("S\n");
//				} else if ((angleFromComp >= 202.5)
//						&& (angleFromComp <= 247.5)) {
//					printf("SW\n");
//				} else if ((angleFromComp >= 247.5)
//						&& (angleFromComp <= 292.5)) {
//					printf("W\n");
//				} else if ((angleFromComp >= 292.5)
//						&& (angleFromComp <= 337.5)) {
//					printf("NW\n");
//				}
		} else {
			printf("\n\n\n");
		}
		clkDiv += -50;
	}
	usleep(uToWait);

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

	while (1) {
		printf("in get z angle\n");
	}
	return 0;
}
void IMU::correctGyro() {
	xGyroCorrection += acel->getRoll() - (xGyroAngle + xGyroCorrection);
	yGyroCorrection += acel->getPitch() - (yGyroAngle + yGyroCorrection);
	printf("Corrected x: %f\n", xGyroAngle + xGyroCorrection);
	printf("Corrected y: %f\n", yGyroAngle + yGyroCorrection);
	printf("\n");
	return;
}
//static void imuRun(void *p) {
//	while (1) {
//		printf("IMU\n");
//		usleep(250000);
//	}
//	return NULL;
//}
void IMU::startIMUThread() {
	threadRunning = 1;
pthread_create(&imuThread_t, 0, &IMU::start_thread, this);
}

void IMU::imuThread(void *obj) {
	IMU *threadIMU = (IMU *) obj;
	//All we do here is call the do_work() function

	while (threadIMU->getThreadRunning()) {
		printf("IMU looping\n");

//		update();
		usleep(500000);
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
