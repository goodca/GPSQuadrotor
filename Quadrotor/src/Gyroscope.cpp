/*
 * Gyroscope.cpp
 *
 *  Created on: Dec 20, 2012
 *      Author: chris
 */

#include "Gyroscope.h"

namespace std {


Gyroscope::Gyroscope() {
	interface = new i2c(3, 0x68);
	return;
}

void Gyroscope::update() {\
	char temp = this->interface->getByte(0x1D);
	printf("%c\n", temp);
	x = (temp << 8) | this->interface->getByte(0x1E);
	printf("%f\n", x);
	y = (this->interface->getByte(GYRO_YOUT_H) << 8) | this->interface->getByte(GYRO_YOUT_L);

	z = (this->interface->getByte(GYRO_ZOUT_H) << 8) | this->interface->getByte(GYRO_ZOUT_L);

}

Gyroscope::~Gyroscope() {
	// TODO Auto-generated destructor stub
}

double Gyroscope::getX(){
	return x;
}
double Gyroscope::getY(){
	return y;
}
double Gyroscope::getZ(){
	return z;
}

} /* namespace std */
