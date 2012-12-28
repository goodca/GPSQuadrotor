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
	printf("Initializing Gyroscope\n");
	GyroInterface = new i2c(3, 0x68);
	file = GyroInterface->getFile();
	printf("Before reset: %x\n", GyroInterface->getByte(file, DLPF_FS));
	GyroInterface->writeByte(file, PWR_MGM, PWR_MGM_H_RESET);
	//usleep(50000);
	printf("Before update: %x\n", GyroInterface->getByte(file, DLPF_FS));
	//Set internal clock to 1kHz with 42Hz LPF and Full Scale to 3 for proper operation
	GyroInterface->writeByte(file, DLPF_FS,
			DLPF_FS_SEL_0 | DLPF_FS_SEL_1 | DLPF_CFG_1 | DLPF_CFG_2);
	printf("init lpf is: %x\n",
			DLPF_FS_SEL_0 | DLPF_FS_SEL_1 | DLPF_CFG_1 | DLPF_CFG_2);
	printf("After update: %x\n", GyroInterface->getByte(file, DLPF_FS));
//Set sample rate divider for 100 Hz operation
	GyroInterface->writeByte(file, SMPLRT_DIV, 1); //Fsample = Fint / (divider + 1) where Fint is 1kHz

//Setup the interrupt to trigger when new data is ready.
	GyroInterface->writeByte(file, INT_CFG,
			INT_CFG_RAW_RDY_EN | INT_CFG_ITG_RDY_EN);

//Select X gyro PLL for clock source
	GyroInterface->writeByte(file, PWR_MGM, PWR_MGM_CLK_SEL_0);

	return;
}

void Gyroscope::update() {

	x = (this->GyroInterface->getByte(file, GYRO_XOUT_H) << 8)
			| this->GyroInterface->getByte(file, GYRO_XOUT_L); // get the value from gyroscope
	xCorrected = x / GCORR; //apply correction factor

	y = (this->GyroInterface->getByte(file, GYRO_YOUT_H) << 8)
			| this->GyroInterface->getByte(file, GYRO_YOUT_L);
	yCorrected = y / GCORR;

	z = (this->GyroInterface->getByte(file, GYRO_ZOUT_H) << 8)
			| this->GyroInterface->getByte(file, GYRO_ZOUT_L);
	zCorrected = z / GCORR;

	return;
}

double Gyroscope::getX() {
	return xCorrected;
}
double Gyroscope::getY() {
	return yCorrected;
}
double Gyroscope::getZ() {
	return zCorrected;
}

Gyroscope::~Gyroscope() {
	// TODO Auto-generated destructor stub
	return;
}




} /* namespace std */
