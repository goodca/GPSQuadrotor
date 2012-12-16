/*
 * Motor.h
 *
 *  Created on: Dec 16, 2012
 *      Author: cooperdl
 */

#ifndef MOTOR_H_
#define MOTOR_H_

class Motor {
	double power;
public:
	Motor();
	void setPower(int newpower);
	virtual ~Motor();
};

#endif /* MOTOR_H_ */
