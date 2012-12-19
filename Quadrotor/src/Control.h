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
	int* requestedX;
	int* requestedY;
	int* requestedZ;
	int* requestedYaw;
	int* currentX;
	int* currentY;
	int*currentZ;
	int*currentYaw;
	Motor Motor0();
	Motor Motor1();
	Motor Motor2();
	Motor Motor3();


public:
	Control();
	void updateCurrentValues(int XVelocity, int YVelocity, int ZVelocity, int YawAngle);
	void updateDirections(int requestedXVelocity,int requestedYVelocity,int requestedZVelocity, int requestedYawAngle);
	void controlstart();
	void controlrun();
	void PID(double* setPoint, double* actualValue, double* previousError, double* integral, double* output, time_t* timestart);
	void updateMotors();
	virtual ~Control();
};



#endif /* CONTROL_H_ */
