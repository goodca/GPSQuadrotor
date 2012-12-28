/*
 * Sensors.cpp
 *
 *  Created on: Dec 23, 2012
 *      Author: chris
 */

#include "Sensors.h"
#include "IMU.h"

namespace std {

Sensors::Sensors() {
	// TODO Auto-generated constructor stub

}
void Sensors::update() {

	return;
}
void Sensors::runTest() {
	printf("Beginning test of sensors\n");
	comp = new Compass;
	comp->init();
	printf("In Sensors, about to imu->init()\n");
	imu->init();
//	pthread_create(&imuThread, NULL, imuRun, (void *) &variable);

//	gps = new GPS;
//	gps->init();

//	while (true) {
//		comp->update();
//		printf("X: %f\nY: %f\nZ: %f\n\n", comp->getX(), comp->getY(),
//				comp->getZ());
//		double heading = atan(comp->getY() / comp->getX());
//		printf("Heading in radians: %f\n", heading);
//		printf("Heading in degrees: %f\n", heading * 180 / 3.14159);
//		sleep(1);
//	}

//	int uToWait = 50000;
//	int clkDiv = 0;
//	printf("Starting loop:\n"return);
//	while (true) {
////		printf(" ");
//		clkDiv++;
//		gyro->update();
////		usleep(uToWait / 2);
//		acel->update();
//		comp->update();
//		xGyroAngle += gyro->getX() * uToWait / 1000000;
//		yGyroAngle += gyro->getY() * uToWait / 1000000;
//		zInt += gyro->getZ() * uToWait / 1000000;
//		xAcel = acel->getX();
//		yAcel = acel->getY();
//		zAcel = acel->getZ();
//
//		if (clkDiv > 10) {
//			printf("\n");
////			printf("X Raw: %f\n", gyro->getX());
////			printf("Y Raw: %f\n", gyro->getY());
////			printf("Z Raw: %f\n", gyro->getZ());
////			printf("Uncorrected Gyro x; %f\n", xInt);
////			printf("Uncorrected Gyro y; %f\n", yInt);
//
////			printf("Gyro x; %f\n", xInt + xGyroCorrection);
////			printf("Gyro y; %f\n", yInt + yGyroCorrection);
//
////			printf("Accel x; %f\n", xAcel);
////			printf("Accel y; %f\n", yAcel);
////			printf("Accel z; %f\n", zAcel);
//			if ((magnitude > 0.95) && (magnitude < 1.05)) {
//
////				printf("total magnitude: %f\n", magnitude);
////				printf("Roll: %f*\n", acel->getRoll());
////				printf("Pitch: %f*\n", acel->getPitch());
//				correctGyro();
//				double angleFromComp;
//				angleFromComp = comp->tiltComponsation(acel->getPitch()*pi/180, acel->getRoll()*pi/180) * 180 / 3.14159;
////				printf("heading is %f\n",
////						(comp->tiltComponsation(acel->getRoll(),
////								acel->getPitch()))*180/3.14159);
//				printf("heading is %f\n", angleFromComp);
//				if((angleFromComp >= 337.5)||(angleFromComp <=22.5)){
//					printf("N\n");
//				}else if((angleFromComp >= 22.5)&&(angleFromComp <=67.5)){
//					printf("NE\n");
//				}else if((angleFromComp >= 67.5)&&(angleFromComp <=112.5)){
//					printf("E\n");
//				}else if((angleFromComp >= 112.5)&&(angleFromComp <=157.5)){
//					printf("SE\n");
//				}else if((angleFromComp >= 157.5)&&(angleFromComp <=202.5)){
//					printf("S\n");
//				}else if((angleFromComp >= 202.5)&&(angleFromComp <=247.5)){
//					printf("SW\n");
//				}else if((angleFromComp >= 247.5)&&(angleFromComp <=292.5)){
//					printf("W\n");
//				}else if((angleFromComp >= 292.5)&&(angleFromComp <=337.5)){
//					printf("NW\n");
//				}
//			} else {
////				printf("\n\n\n");
//			}
//			clkDiv += -10;
//		}
//		usleep(uToWait);
//	}
}

//void Sensors::correctGyro() {
//	xGyroCorrection += acel->getRoll() - (xGyroAngle + xGyroCorrection);
//	yGyroCorrection += acel->getPitch() - (yGyroAngle + yGyroCorrection);
//}

void updateGyroWCorr() {

}

Sensors::~Sensors() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
