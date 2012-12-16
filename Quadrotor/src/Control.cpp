/*
 * Control.cpp
 *
 *  Created on: Dec 14, 2012
 *      Author: cooperdl
 */

#include "Control.h"
#include "Motor.h"
#include "Quadrotor.h"

Control::Control() {
	// TODO Auto-generated constructor stub


}

void Control::updateCurrentValues(int XVelocity, int YVelocity, int ZVelocity, int YawAngle){
	currentX=XVelocity;
	currentY=YVelocity;
	currentZ=ZVelocity;
	currentYaw=YawAngle;
}
void Control::updateDirections(int requestedXVelocity,int requestedYVelocity,int requestedZVelocity, int requestedYawAngle){
	 	requestedX=requestedXVelocity;
	 	requestedY=requestedYVelocity;
	 	requestedZ=requestedZVelocity;
	 	requestedYaw=requestedYawAngle;

}



Control::~Control() {
	// TODO Auto-generated destructor stub
}

