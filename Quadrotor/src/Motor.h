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

	virtual ~Motor();
private:
	void set_pwm(int pw);
//	void Motor::changePWM();
	int set_mux_value(char* mux, int value);
	int motor;
	char* motorName;

	double power;
	int motorNum;
	int file;
	char filename[20];
	FILE *fp;
	char path[MAX_BUF];
};

#define O_RDWR		     02
#define MOTOR_1
#define MOTOR_2
#define MOTOR_3
#define MOTOR_4
#define FREQUENCY 50
#define MIN_HIGH_TIME_NS 1000000
#define MAX_HIGH_TIME_NS 2000000

#endif /* MOTOR_H_ */
