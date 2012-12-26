/*
 * Sensors.cpp
 *
 *  Created on: Dec 23, 2012
 *      Author: chris
 */

#include "Sensors.h"

namespace std {

Sensors::Sensors() {
	// TODO Auto-generated constructor stub

}
void Sensors::update() {

	return;
}
void Sensors::runTest() {
	printf("Beginning test of sensors\n");
	gps = new GPS;
	gps->init();
	while(true){
		gps->getGPSData();
	}
//	gyro = new Gyroscope;
//	acel = new Accelerometer;
//	gyro->init();
//	sleep(1);
//	gyro->update();
//	sleep(1);
//	acel->init();
//	sleep(1);
//	acel->update();
//	sleep(1);
//	xInt = 0;
//	yInt = 0;
//	zInt = 0;
//	double xAcel;
//	double yAcel;
//	double zAcel;
//	double magnitude;
//	int uToWait = 50000;
//	int clkDiv = 0;
//	printf("Starting loop:\n");
//	while (true) {
////		printf(" ");
//		clkDiv++;
//		gyro->update();
////		usleep(uToWait / 2);
//		acel->update();
//		xInt += gyro->getX() * uToWait / 1000000;
//		yInt += gyro->getY() * uToWait / 1000000;
//		zInt += gyro->getZ() * uToWait / 1000000;
//		xAcel = acel->getX();
//		yAcel = acel->getY();
//		zAcel = acel->getZ();
//		magnitude = sqrt(xAcel * xAcel + yAcel * yAcel + zAcel * zAcel);
//		if (clkDiv > 10) {
//			printf("\n");
////			printf("X Raw: %f\n", gyro->getX());
////			printf("Y Raw: %f\n", gyro->getY());
////			printf("Z Raw: %f\n", gyro->getZ());
//			printf("Uncorrected Gyro x; %f\n", xInt);
//			printf("Uncorrected Gyro y; %f\n", yInt);
//
//			printf("Gyro x; %f\n", xInt + xGyroCorrection);
//			printf("Gyro y; %f\n", yInt + yGyroCorrection);
//
////			printf("Accel x; %f\n", xAcel);
////			printf("Accel y; %f\n", yAcel);
////			printf("Accel z; %f\n", zAcel);
//			if ((magnitude > 0.996) && (magnitude < 1.04)) {
//
//				printf("total magnitude: %f\n", magnitude);
//				printf("Roll: %f*\n", acel->getRoll());
//				printf("Pitch: %f*\n", acel->getPitch());
//
//				correctGyro();
//			} else {
//				printf("\n\n\n");
//			}
//			clkDiv += -10;
//		}
//		usleep(uToWait);
//	}
}

void Sensors::correctGyro() {
	xGyroCorrection += acel->getRoll() - (xInt + xGyroCorrection) ;
	yGyroCorrection += acel->getPitch() - (yInt + yGyroCorrection);
}

void updateGyroWCorr() {

}

Sensors::~Sensors() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
