/*
 * Gyroscope.cpp
 *
 *  Created on: Dec 20, 2012
 *      Author: chris
 */

#include "Gyroscope.h"

namespace std {

Gyroscope::Gyroscope() {

	return;
}
void Gyroscope::init() {
	interface = new i2c(3, 0x68);
	printf("Before update: %x\n", interface->getByte(DLPF_FS));
	//Set internal clock to 1kHz with 42Hz LPF and Full Scale to 3 for proper operation
	interface->writeByte(DLPF_FS, DLPF_FS_SEL_0 | DLPF_FS_SEL_1 | DLPF_CFG_1 | DLPF_CFG_2);
	printf("init lpf is: %x\n", DLPF_FS_SEL_0 | DLPF_FS_SEL_1 | DLPF_CFG_1 | DLPF_CFG_2);
	printf("After update: %x\n", interface->getByte(DLPF_FS));
//Set sample rate divider for 100 Hz operation
	interface->writeByte(SMPLRT_DIV, 1); //Fsample = Fint / (divider + 1) where Fint is 1kHz

//Setup the interrupt to trigger when new data is ready.
	interface->writeByte(INT_CFG, INT_CFG_RAW_RDY_EN | INT_CFG_ITG_RDY_EN);

//Select X gyro PLL for clock source
	interface->writeByte(PWR_MGM, PWR_MGM_CLK_SEL_0);
}

void Gyroscope::update() {
	//char temp = this->interface->getByte(0x1D);
	//printf("%c\n", temp);
	x = (this->interface->getByte(GYRO_XOUT_H) << 8)
			| this->interface->getByte(GYRO_XOUT_L);
	//printf("%f\n", x);
	y = (this->interface->getByte(GYRO_YOUT_H) << 8)
			| this->interface->getByte(GYRO_YOUT_L);

	z = (this->interface->getByte(GYRO_ZOUT_H) << 8)
			| this->interface->getByte(GYRO_ZOUT_L);

}

Gyroscope::~Gyroscope() {
	// TODO Auto-generated destructor stub
}

double Gyroscope::getX() {
	return x;
}
double Gyroscope::getY() {
	return y;
}
double Gyroscope::getZ() {
	return z;
}

} /* namespace std */
