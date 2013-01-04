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

void Compass::init() {
	printf("Initializing Compass\n");
	compassInterface = new i2c(I2C_PORT, ADXL_ADDR);
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
	return;
	return;
}

double Compass::getX() {
	return x;
}

double Compass::getY() {
	return y;
}

double Compass::getZ() {
	while(1){
		printf("in compass getZ()\n");
	}

	return z;
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
double Compass::tiltComponsation(double phi, double theta) {

//magnetometer_readings_to_tilt_compensated_heading
//Takes in raw magnetometer values, pitch and roll and turns it into a tilt-compensated heading value ranging from -pi to pi (everything in this function should be in radians).

	double Xh = x * cos(theta) + y * sin(phi) * sin(theta)
			+ z * cos(phi) * sin(theta);
	printf("Xh: %f\n", Xh);

	double Yh = y * cos(phi) - z * sin(phi);
	printf("Yh: %f\n", Yh);
	double angle = atan2(-Yh, Xh);
	angle += MAG_DECLINATION;
	angle = unWrap(angle);
	return angle;
}

void Compass::startCompass(){
	void *env;
	pthread_create(&compassThread, 0, &Compass::start_thread, env);
}

Compass::~Compass() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
