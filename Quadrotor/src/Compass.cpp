/*
 * Compass.cpp
 *
 *  Created on: Dec 26, 2012
 *      Author: chris
 */

#include "Compass.h"

namespace std {

Compass::Compass() {
	// TODO Auto-generated constructor stub
	return;
}

void Compass::compassThread(void *obj) {
	Compass *threadCompass = (Compass *) obj;
	threadCompass->init();
	while (threadCompass->getThreadRunning()) {
//		printf("Compass Running\n");
		usleep(500000);
	}
	//TODO: join the thread
	return;
}
double Compass::getThreadRunning() {
	return threadRunning;
}
void Compass::stopThread() {
	threadRunning = 0;
}

void Compass::init() {
	compassInterface = new i2c(COMP_I2C_PORT, COMP_ADDR);
	compassFile = compassInterface->getFile();
//	compassInterface->writeByte(compassFile, CONFIG_REG_A, 0b00110000);
//	compassInterface->writeByte(compassFile, CONFIG_REG_B, 0b00100000);
	compassInterface->writeByte(compassFile, MODE_REG, 0); // set to continuous measurement
	return;

}
void Compass::update() {
	x = (this->compassInterface->getByte(compassFile, X_MSB) << 8)
			| this->compassInterface->getByte(compassFile, X_LSB);

	y = (this->compassInterface->getByte(compassFile, Y_MSB) << 8)
			| this->compassInterface->getByte(compassFile, Y_LSB);

	z = (this->compassInterface->getByte(compassFile, Z_MSB) << 8)
			| this->compassInterface->getByte(compassFile, Z_LSB);
//	printf("compass x %d y %d z %d\n", x, y, z);
	return;
}

double Compass::getHeading(double xAngle, double yAngle) {
	double phi = yAngle * pi / 180;
	double theta = xAngle * pi / 180;
	double Xh = x * cos(theta) + y * sin(phi) * sin(theta)
			+ z * cos(phi) * sin(theta);
//	printf("Xh: %f\n", Xh);

	double Yh = y * cos(phi) - z * sin(phi);
//	printf("Yh: %f\n", Yh);
	double angle = atan2(-Yh, Xh);
	angle += MAG_DECLINATION;
	angle = unWrap(angle);
	angle = angle * 180 / pi;
//	printf("%f degrees from north\n", angle);
	return angle;
}

double Compass::unWrap(double angle) {
	if (angle > pi) {

		angle -= (2 * pi);
	}

	if (angle < -pi) {

		angle += (2 * pi);
	}
	if (angle < 0) {

		angle += 2 * pi;
	}
	return angle;
}

void Compass::startCompassThread() {
	threadRunning = 1;
	pthread_create(&compassThread_t, 0, &Compass::start_thread, this);
}

Compass::~Compass() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
