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

}

void Accelerometer::init() {
	interface = new i2c(3, 0x53);
	interface->writeByte(POWER_CTL, MEASURE);
	interface->writeByte(DATA_FORMAT, RANGE_0);
}

void Accelerometer::update() {

	x = (this->interface->getByte(DATAX1) << 8)
			| this->interface->getByte(DATAX0);

	y = (this->interface->getByte(DATAY1) << 8)
			| this->interface->getByte(DATAY0);

	z = (this->interface->getByte(DATAZ1) << 8)
			| this->interface->getByte(DATAZ0);
}

double Accelerometer::getX() {
	return x * SCALE4G;
}
double Accelerometer::getY() {
	return y * SCALE4G;
}
double Accelerometer::getZ() {
	return z * SCALE4G;
}
double Accelerometer::getPitch() {
	return atan(x / sqrt(y * y + z * z)) * 180 / 3.14159;
}
double Accelerometer::getRoll() {
	return atan(y / sqrt(x * x + z * z)) * 180 / 3.14159;
}
Accelerometer::~Accelerometer() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
