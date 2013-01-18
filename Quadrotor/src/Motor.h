/*
 * Motor.h
 *
 *  Created on: Dec 16, 2012
 *      Author: cooperdl
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdio.h>
#include <stdlib.h>

class Motor {

public:
	Motor(int motorNumber);
	void setPower(double newpower);
	virtual ~Motor();
private:
//	void Motor::changePWM();
	int motor;
	double power;
	int motorNum;
	int file;
	char filename[20];
};

#define O_RDWR		     02
#define MOTOR_1
#define MOTOR_2
#define MOTOR_3
#define MOTOR_4

#endif /* MOTOR_H_ */
