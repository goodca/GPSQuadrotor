/*
 * Control.h
 *
 *  Created on: Dec 14, 2012
 *      Author: cooperdl
 */

#ifndef CONTROL_H_
#define CONTROL_H_

class Control {
	int* requestedX,requestedY,requestedZ,requestedYaw,currentX,currentY,currentZ,currentYaw;
	Motor Motor0();
	Motor Motor1();
	Motor Motor2();
	Motor Motor3();

public:
	Control();
	void updateCurrentValues(int XVelocity, int YVelocity, int ZVelocity, int YawAngle);
	void updateDirections(int requestedXVelocity,int requestedYVelocity,int requestedZVelocity, int requestedYawAngle);
	void updateMotors();
	virtual ~Control();
};



#endif /* CONTROL_H_ */
