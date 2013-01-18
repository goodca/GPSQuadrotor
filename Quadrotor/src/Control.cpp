/*
 * Control.cpp
 *
 *  Created on: Dec 14, 2012
 *      Author: cooperdl
 */

#include "Control.h"
#include "Motor.h"
#include "constants.h"
#include "Sensors.h"
#include "PID.h"
#include <time.h>
#include <unistd.h>

namespace std {
Control::Control(Sensors * data) {

	realData = data;



}

void Control::updateRequestedAngle(double xAngle, double yAngle, double zAngle,
		double thrust) {

	this->requestedXAngle = xAngle;
	this->requestedYAngle = yAngle;
	this->requestedZAngle = zAngle;
	this->requestedThrust = thrust;

}

void Control::controlCycle() {
	//this->updateRequestedAngle();

	double desiredRateX;
	double angleFactorX;

	this->OuterX->UpdateActualValue(this->realData->getXAngle());
	this->OuterX->UpdateSetPoint(requestedXAngle);
	desiredRateX = this->OuterX->UpdateOutput();

	this->InnerX->UpdateActualValue(this->realData->getXAngleSpeed());
	this->InnerX->UpdateSetPoint(desiredRateX);
	angleFactorX = this->InnerX->UpdateOutput();

	double desiredRateY;
	double angleFactorY;

	this->OuterY->UpdateActualValue(this->realData->getYAngle());
	this->OuterY->UpdateSetPoint(requestedYAngle);
	desiredRateY = this->OuterY->UpdateOutput();

	this->InnerY->UpdateActualValue(this->realData->getYAngleSpeed());
	this->InnerY->UpdateSetPoint(desiredRateY);
	angleFactorY = this->InnerY->UpdateOutput();

	double desiredRateZ;
	double angleFactorZ;

	this->OuterZ->UpdateActualValue(this->realData->getZAngle());
	this->OuterZ->UpdateSetPoint(requestedZAngle);
	desiredRateZ = this->OuterZ->UpdateOutput();

	this->InnerZ->UpdateActualValue(this->realData->getZAngleSpeed());
	this->InnerZ->UpdateSetPoint(desiredRateZ);
	angleFactorZ = this->InnerZ->UpdateOutput();

	//motor stuff here

}

void Control::controlRun() {

	this->controlStart();
	while (1) {
		this->controlCycle();
		usleep(SleepTime);

	}

}

void Control::controlStart() {

	gettimeofday(&this->timestart, NULL);
	this->OuterX = new PID(0, 0, 1, 0, 0, timestart, OuterXKp, OuterXKi,
			OuterXKd);

	gettimeofday(&this->timestart, NULL);
	this->InnerX = new PID(0, 0, 1, 0, 0, timestart, InnerXKp, InnerXKi,
			InnerXKd);

	gettimeofday(&this->timestart, NULL);
	this->OuterY = new PID(0, 0, 1, 0, 0, timestart, OuterYKp, OuterYKi,
			OuterYKd);

	gettimeofday(&this->timestart, NULL);
	this->InnerY = new PID(0, 0, 1, 0, 0, timestart, InnerYKp, InnerYKi,
			InnerYKd);

	gettimeofday(&this->timestart, NULL);
	this->OuterZ = new PID(0, 0, 1, 0, 0, timestart, OuterZKp, OuterZKi,
			OuterZKd);

	gettimeofday(&this->timestart, NULL);
	this->InnerZ = new PID(0, 0, 1, 0, 0, timestart, InnerZKp, InnerZKi,
			InnerZKd);

}

void updateMotors();

Control::~Control() {
	// TODO Auto-generated destructor stub
}

}/* namespace std */
