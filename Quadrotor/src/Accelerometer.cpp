/*
 * Accelerometer.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: chris
 */

#include "Accelerometer.h"

namespace std {

Accelerometer::Accelerometer() {
	// TODO Auto-generated constructor stub
	return;

}

void Accelerometer::init() {
	printf("Initializing Accelerometer\n");
	AccelInterface = new i2c(3, 0x53);
	file = AccelInterface->getFile();

	AccelInterface->writeByte(file, POWER_CTL, MEASURE);
	AccelInterface->writeByte(file, DATA_FORMAT, RANGE_0);
//	AccelInterface->setName('A');
	return;
}

void Accelerometer::update() {
//	printf("Accel I2C address: %d\n", AccelInterface->getAddress());
	//this->AccelInterface->openFile();
	x = (this->AccelInterface->getByte(file, DATAX1) << 8)
			| this->AccelInterface->getByte(file, DATAX0);

	xCorr = x * SCALE4G;
	y = (this->AccelInterface->getByte(file, DATAY1) << 8)
			| this->AccelInterface->getByte(file, DATAY0);
	yCorr = y * SCALE4G;
	z = (this->AccelInterface->getByte(file, DATAZ1) << 8)
			| this->AccelInterface->getByte(file, DATAZ0);
	zCorr = z * SCALE4G;

	magnitude = sqrt(xCorr * xCorr + yCorr * yCorr + zCorr * zCorr);
	return;
}
double Accelerometer::getMagnitude() {
	return magnitude;
}

double Accelerometer::getX() {
	return xCorr;
}
double Accelerometer::getY() {
	return yCorr;
}
double Accelerometer::getZ() {
	return zCorr;
}
double Accelerometer::getPitch() {
	return atan(x / sqrt(y * y + z * z)) * 180 / 3.14159;
}
double Accelerometer::getRoll() {
	return atan(-y / sqrt(x * x + z * z)) * 180 / 3.14159;
}
Accelerometer::~Accelerometer() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
