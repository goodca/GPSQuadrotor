/*
 * Motor.cpp
 *
 *  Created on: Dec 16, 2012
 *      Author: cooperdl
 */

#include "Motor.h"

Motor::Motor(int motorNumber) {
	motorNum = motorNumber;
	if(motorNumber==1){

	}else if(motorNumber==2){

	}else if(motorNumber==3){

	}else if(motorNumber==4){

	}else{
		printf("Motor number must be an integer 1, 2, 3, or 4");
		return;
	}
//	sprintf(filename, "/dev/i2c-%d", i2cbus);
//	open(filename, O_RDWR);
}

void Motor::setPower(double newPower){
	power=newPower;
}

//void Motor::changePWM(){
//	return;
//}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}
