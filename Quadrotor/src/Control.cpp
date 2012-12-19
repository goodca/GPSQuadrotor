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

void Control::updateCurrentValues(int XVelocity, int YVelocity, int ZVelocity,
		int YawAngle) {
	*currentX = XVelocity;
	*currentY = YVelocity;
	*currentZ = ZVelocity;
	*currentYaw = YawAngle;
}
void Control::updateDirections(int requestedXVelocity, int requestedYVelocity,
		int requestedZVelocity, int requestedYawAngle) {
	*requestedX = requestedXVelocity;
	*requestedY = requestedYVelocity;
	*requestedZ = requestedZVelocity;
	*requestedYaw = requestedYawAngle;
}

void PID(double* setPoint, double* actualValue, double* previousError,
		double* integral, double* output, time_t* timestart) {

	double error = *setPoint - *actualValue;
	time_t end;
	time(&end);
	double timechange = difftime(end, *timestart);
	timestart = &end;
	*integral = *integral + error * timechange;
	double derivitive = (error - *previousError) / timechange;
	*output = Kp*error + Ki * *integral + Kd * derivitive;
	*previousError = error;
	sleep(.01);

}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

