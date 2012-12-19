/*
 * Control.h
 *
 *  Created on: Dec 14, 2012
 *      Author: cooperdl
 */

#ifndef CONTROL_H_
#define CONTROL_H_
#include "Motor.h"
#include <time.h>

class Control {
	int* requestedXVelocity;
	int* requestedYVelocity;
	int* requestedZVelocity;
	int* requestedYawVelocity;
	int* currentXVelocity;
	int* currentYVelocity;
	int* currentZVelocity;
	int* currentYawVelocity;
	int* requestedXAcceloration;
	int* requestedYAcceloration;
	int* requestedZAcceloration;
	int* requestedYawAcceloration;
	int* currentXAcceloration;
	int* currentYAcceloration;
	int* currentZAcceloration;
	int* currentYawAcceloration;

	Motor Motor0();
	Motor Motor1();
	Motor Motor2();
	Motor Motor3();

public:
	Control();
	void updateCurrentVelocityValues(int XVelocity, int YVelocity,
			int ZVelocity, int YawAngle);
	void updateDirections(int requestedXVelocity, int requestedYVelocity,
			int requestedZVelocity, int requestedYawAngle);
	void updateCurrentAcclerationValues(int currentXAccleration,
			int currentYAccleration, int currentZAccleration,
			int currentYawAccleration);
	void updateRequestedAccleration(int currentXAccleration,
			int currentYAccleration, int currentZAccleration,
			int currentYawAccleration);

	void controlstart();

	void controlrun();
	void PID(double* setPoint, double* actualValue, double* previousError,
			double* integral, double* output, time_t* timestart);
	void updateMotors();
	virtual ~Control();
};

#endif /* CONTROL_H_ */
