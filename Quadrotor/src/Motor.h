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

#define MAX_BUF 127

class Motor {

public:
	Motor();
	void init(int motorNumber);
	void setPower(double newpower);
	int set_pwm(double duty_percent);
	virtual ~Motor();
private:
//	void Motor::changePWM();
	int set_mux_value(char* mux, int value);
	int motor;
	char* motorName;

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
#define FREQUENCY 50
#define MIN_DUTY_CYCLE 5
#define MAX_DUTY_CYCLE 7

#endif /* MOTOR_H_ */
