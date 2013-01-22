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

	if (xAngle > 35) {
		xAngle = 35;
	}

	if (yAngle > 35) {
		yAngle = 35;
	}
	if (thrust > 80) {

		thrust = 80;

	}

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
	this->OuterX->UpdateSetPoint(this->requestedXAngle);
	desiredRateX = this->OuterX->UpdateOutput();

	this->InnerX->UpdateActualValue(this->realData->getXAngleSpeed());
	this->InnerX->UpdateSetPoint(desiredRateX);
	angleFactorX = this->InnerX->UpdateOutput();

	double desiredRateY;
	double angleFactorY;

	this->OuterY->UpdateActualValue(this->realData->getYAngle());
	this->OuterY->UpdateSetPoint(this->requestedYAngle);
	desiredRateY = this->OuterY->UpdateOutput();

	this->InnerY->UpdateActualValue(this->realData->getYAngleSpeed());
	this->InnerY->UpdateSetPoint(desiredRateY);
	angleFactorY = this->InnerY->UpdateOutput();

	double desiredRateZ;
	double angleFactorZ;

	this->OuterZ->UpdateActualValue(this->realData->getZAngle());
	this->OuterZ->UpdateSetPoint(this->requestedZAngle);
	desiredRateZ = this->OuterZ->UpdateOutput();

	this->InnerZ->UpdateActualValue(this->realData->getZAngleSpeed());
	this->InnerZ->UpdateSetPoint(desiredRateZ);
	angleFactorZ = this->InnerZ->UpdateOutput();

	//motor stuff here

	this->Motor1->setPower(
			this->thrust + angleFactorY - angleFactorX + angleFactorZ);
	this->Motor2->setPower(
			this->thrust + angleFactorY + angleFactorX - angleFactorZ);
	this->Motor3->setPower(
			this->thrust - angleFactorY + angleFactorX + angleFactorZ);
	this->Motor4->setPower(
			this->thrust - angleFactorY - angleFactorX - angleFactorZ);

}

void Control::controlRun() {

	this->controlStart();
	while (1) {
		if (remote) {
			this->controlCycle();
			usleep(SleepTime);
		} else {

			double desiredRateThrust;
			double thrustFactor;
			this->OuterThrust->UpdateActualValue(
					this->realData->getZVelocity());
			this->OuterThrust->UpdateSetPoint(requestedZvelocity);
			desiredRateThrust = this->OuterThrust->UpdateOutput();

			this->InnerThrust->UpdateActualValue(
					this->realData->getZAcceleration());
			this->InnerThrust->UpdateSetPoint(desiredRateThrust);
			thrustFactor = this->InnerThrust->UpdateOutput();

			double desiredXvelocity;
			double Xangle;
			Xangle = desiredXvelocity - this->realData->getXVelocity();

			double desiredYvelocity;
			double Yangle;
			Yangle = desiredXvelocity - this->realData->getXVelocity();

			void updateRequestedAngle(Xangle, Yangle, this->requestedZAngle,
					thrustFactor);
			this->controlCycle();

			usleep(SleepTime);

		}

	}

}

void Control::UpdateRequestedVelocity(double Xspeed, double Yspeed,
		double Zspeed, double zAngle){

	this->requestedXvelocity=Xspeed;
	this->requestedYvelocity=Yspeed;
	this->requestedZvelocity=Zspeed;
	this->requestedZAngle=zAngle;
}

void Control::setRemote(int on) {

	this->remote = on;

}

void Control::controlStart() {

	gettimeofday(&this->timestart, NULL);
	this->OuterX = new PID(0, 0, 0, 0, 0, timestart, OuterXKp, OuterXKi,
			OuterXKd);

	gettimeofday(&this->timestart, NULL);
	this->InnerX = new PID(0, 0, 0, 0, 0, timestart, InnerXKp, InnerXKi,
			InnerXKd);

	gettimeofday(&this->timestart, NULL);
	this->OuterY = new PID(0, 0, 0, 0, 0, timestart, OuterYKp, OuterYKi,
			OuterYKd);

	gettimeofday(&this->timestart, NULL);
	this->InnerY = new PID(0, 0, 0, 0, 0, timestart, InnerYKp, InnerYKi,
			InnerYKd);

	gettimeofday(&this->timestart, NULL);
	this->OuterZ = new PID(0, 0, 0, 0, 0, timestart, OuterZKp, OuterZKi,
			OuterZKd);

	gettimeofday(&this->timestart, NULL);
	this->InnerZ = new PID(0, 0, 0, 0, 0, timestart, InnerZKp, InnerZKi,
			InnerZKd);

	gettimeofday(&this->timestart, NULL);
	this->OuterThrust = new PID(0, 0, 0, 0, 0, timestart, OuterThrustKp, OuterThrustKi,
			OuterThrustKd);

	gettimeofday(&this->timestart, NULL);
	this->InnerThrust = new PID(0, 0, 0, 0, 0, timestart, InnerThrustKp, InnerThrustKi,
			InnerThrustKd);



	this->Motor1 = new Motor();
	Motor1->init(1);
	this->Motor2 = new Motor();
	Motor2->init(2);
	this->Motor3 = new Motor();
	Motor3->init(3);
	this->Motor4 = new Motor();
	Motor4->init(4);
}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

}/* namespace std */
