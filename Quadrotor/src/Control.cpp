/*
 * Control.cpp
 *
 *  Created on: Dec 14, 2012
 *      Author: cooperdl
 */

#include "Control.h"
#include "Motor.h"
#include "constants.h"
#include <time.h>
#include <unistd.h>

Control::Control() {
	// TODO Auto-generated constructor stub

}

void Control::updateCurrentVelocityValues(int XVelocity, int YVelocity,
		int ZVelocity, int YawAngle) {
	*currentXVelocity = XVelocity;
	*currentYVelocity = YVelocity;
	*currentZVelocity = ZVelocity;
	*currentYawVelocity = YawAngle;
}
void Control::updateDirections(int updatedXVelocity, int updatedYVelocity,
		int updatedZVelocity, int updatedYawVelocity) {
	*requestedXVelocity = updatedXVelocity;
	*requestedYVelocity = updatedYVelocity;
	*requestedZVelocity = updatedZVelocity;
	*requestedYawVelocity = updatedYawVelocity;
}
void Control::updateCurrentAcclerationValues(int XAccleration, int YAccleration,
		int ZAccleration, int YawAccleration) {
	*currentXAcceloration = XAccleration;
	*currentYAcceloration = YAccleration;
	*currentZAcceloration = ZAccleration;
	*currentYawAcceloration = YawAccleration;
}

void Control::updateRequestedAccleration(int updatedXAccleration,
		int updatedYAccleration, int updatedZAccleration,
		int updatedYawAccleration) {
	*requestedXAcceloration = updatedXAccleration;
	*requestedYAcceloration = updatedYAccleration;
	*requestedZAcceloration = updatedZAccleration;
	*requestedYawAcceloration = updatedYawAccleration;
}

void Control::PID(double* setPoint, double* actualValue, double* previousError,
		double* integral, double* output, time_t* timestart) {

	double error = *setPoint - *actualValue;
	time_t end;
	time(&end);
	double timechange = difftime(end, *timestart);
	timestart = &end;
	*integral = *integral + error * timechange;
	double derivitive = (error - *previousError) / timechange;
//	TODO:*output = Kp * error + Ki * *integral + Kd * derivitive;
	*previousError = error;
	sleep(dt);

}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

