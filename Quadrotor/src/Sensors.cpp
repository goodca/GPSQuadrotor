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
void Sensors::startSensorsThreads() {

	threadRunning = 1;
	//start other sensor threads
	imu = new IMU;
	imu->startIMUThread();
	usleep(100000);
	comp = new Compass;
//	comp->startCompassThread();
	usleep(100000);
	gps = new GPS;
//	gps->startGPSThread();
	usleep(100000);
	range = new RangeFinder;
	range->start();
	usleep(100000);


	//start main sensor thread
	pthread_create(&sensorsThread_t, 0, &Sensors::start_thread, this);

	return;
}
void Sensors::sensorsThread(void *obj) {
	Sensors *threadSense = (Sensors *) obj;
	//All we do here is call the do_work() function

	while (threadSense->getThreadRunning()) {
//		printf("Sensors looping\n");

//		update();
		usleep(500000);
	}
}
void Sensors::update() {

	return;
}
int Sensors::getThreadRunning() {
	return threadRunning;
}
void Sensors::stopThread() {
	threadRunning = 0;
	imu->stopThread();
	comp->stopThread();
	gps->stopThread();
	return;
}

void Sensors::runTest() {
	printf("Beginning test of sensors\n");
	imu = new IMU;
	imu->init();
	imu->update(); //while loop in there, won't return
//	comp = new Compass;
//	comp->init();
//	printf("In Sensors, about to imu->init()\n");
//	Gyroscope *gyro = new Gyroscope;
//	gyro->init();
//	gyro->update();
//	Accelerometer *acel = new Accelerometer;
//	acel->init();
//	acel->update();
//	imu->init();
//	pthread_create(&imuThread, NULL, imuRun, (void *) &variable);

//	gps = new GPS;
//	gps->init();

//	while (true){
//		gps->getGPSData();
//	}
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
//	int magnitude = 0;
//	double xGyroAngle = 0;
//	double yGyroAngle = 0;
//	double zGyroAngle = 0;
//	double xAcel;
//	double yAcel;
//	double zAcel;
//	double zInt = 0;
//	double yInt = 0;
//	double xInt = 0;

//	printf("Starting loop:\n");
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



double Sensors::getXAngle(){
	return imu->getXAngle();
}
double Sensors::getYAngle(){
	return imu->getYAngle();
}
double Sensors::getZAngle(){
	return imu->getZAngle();
}
double Sensors::getXAngleSpeed(){
	return imu->getXAngleSpeed();
}
double Sensors::getYAngleSpeed(){
	return imu->getYAngleSpeed();
}
double Sensors::getZAngleSpeed(){
	return imu->getZAngleSpeed();
}
double Sensors::getXAngleAcceleration(){
	return imu->getXAngleAcceleration();
}
double Sensors::getYAngleAcceleration(){
	return imu->getYAngleAcceleration();
}
double Sensors::getZAngleAcceleration(){
	return imu->getZAngleAcceleration();
}
double Sensors::getXVelocity(){
	return imu->getXVelocity();
}
double Sensors::getYVelocity(){
	return imu->getYVelocity();
}
double Sensors::getZVelocity(){
	return imu->getZVelocity();
}
double Sensors::getXAcceleration(){
	return imu->getXAccel();
}
double Sensors::getYAcceleration(){
	return imu->getYAccel();
}
double Sensors::getZAcceleration(){
	return imu->getZAccel();
}
double Sensors::getLatitude(){
	return 0;
}
double Sensors::getLongtitude(){
	return 0;
}
double Sensors::getHeight(){
	return 0;
}
double Sensors::getRelativeHeight(){
	return range->getDistance();
}
Sensors::~Sensors() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
