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
#include "Remotehandler.h"
#include <time.h>
#include <unistd.h>
#include <iostream>

namespace std {
Control::Control() {

}

void Control::updateRequestedAngle(double xAngle, double yAngle, double zAngle,
		double thrust) {

	if (xAngle > 35) {
		xAngle = 35;
	} else if (xAngle < -35) {
		xAngle = -35;
	}
	if (yAngle > 35) {
		yAngle = 35;
	} else if (yAngle < -35) {
		yAngle = -35;
	}
	if (thrust > 80) {

		thrust = 80;

	}

	this->requestedXAngle = xAngle;
	this->requestedYAngle = yAngle;
	this->requestedZAngle = zAngle;
	this->thrust = thrust;

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

	printf("xanglefactor %f\nyanglefactor %f\nzanglefactor %f\nthrust %f\n",
			angleFactorX, angleFactorY, angleFactorZ, thrust);
	printf("xangle %f\nyangle %f\nzangle %f\nheight %f\nLat: %f Long: %f\n",
			this->realData->getXAngle(), this->realData->getYAngle(),
			this->realData->getZAngle(), realData->getRelativeHeight(),
			realData->getLatitude(), realData->getLongtitude());
	printf("xanglespeed %f\nyanglespeed %f\nzanglespeed %f\nheight %f\nLat: %f Long: %f\n",
				this->realData->getXAngleSpeed(), this->realData->getYAngleSpeed(),
				this->realData->getZAngleSpeed());
	printf("xanglefactor %f\nyanglefactor %f\nzanglefactor %f\nthrust %f\n",
			angleFactorX, angleFactorY, angleFactorZ, thrust);
	printf("Rxangle %f\nRyangle %f\nRzangle %f\nRThrust %f\n",
			this->requestedXAngle, this->requestedYAngle, this->requestedZAngle,
			this->thrust);
	printf("1: %f 2: %f 3: %f 4: %f\n", remotecontrol->getch1(),
			remotecontrol->getch2(), remotecontrol->getch3(),
			remotecontrol->getch4());

	//motor stuff here
	double thrust1 = 0;
	double thrust2 = 0;
	double thrust3 = 0;
	double thrust4 = 0;
	if (this->thrust > 25) {

		if ((this->thrust + angleFactorY - angleFactorX + angleFactorZ) < 100) {
			thrust1 = this->thrust + angleFactorY - angleFactorX + angleFactorZ;
			this->Motor1->setPower(thrust1);
		} else {
			this->Motor1->setPower(100);

		}
		if ((this->thrust + angleFactorY + angleFactorX - angleFactorZ) < 100) {
			thrust2 = this->thrust + angleFactorY + angleFactorX - angleFactorZ;
			this->Motor2->setPower(thrust2);
		} else {
			this->Motor2->setPower(100);

		}
		if ((this->thrust - angleFactorY + angleFactorX + angleFactorZ) < 100) {
			thrust3 = this->thrust - angleFactorY + angleFactorX + angleFactorZ;
			this->Motor3->setPower(thrust3);
		} else {
			this->Motor3->setPower(100);

		}
		if ((this->thrust - angleFactorY - angleFactorX - angleFactorZ) < 100) {
			thrust4 = this->thrust - angleFactorY - angleFactorX - angleFactorZ;
			this->Motor4->setPower(thrust4);
		} else {
			this->Motor4->setPower(100);

		}
		printf("Motor1: %f Motor2: %f Motor3: %f Motor4: %f\n", thrust1,
				thrust2, thrust3, thrust4);
	} else {
		thrust1 = this->thrust + angleFactorY - angleFactorX + angleFactorZ;
		thrust2 = this->thrust + angleFactorY + angleFactorX - angleFactorZ;
		thrust3 = this->thrust - angleFactorY + angleFactorX + angleFactorZ;
		thrust4 = this->thrust - angleFactorY - angleFactorX - angleFactorZ;
		printf("Motor1: %f Motor2: %f Motor3: %f Motor4: %f\n", thrust1,
						thrust2, thrust3, thrust4);
		this->Motor1->setPower(0);
		this->Motor2->setPower(0);
		this->Motor3->setPower(0);
		this->Motor4->setPower(0);
	}

}

void Control::controlRun(Sensors *sense) {
	realData = sense;

//	printf("xangle %f\nyangle %f\nzangle %f\n", this->realData->getXAngle(),
//			this->realData->getYAngle(), this->realData->getYAngle());

	this->controlStart();
	this->remote = 1;

	while (1) {
		if (remote) {
			this->updateRequestedAngle(this->remotecontrol->getch1() - 50,
					this->remotecontrol->getch2() - 50,
					(this->remotecontrol->getch4() - 50)/200 + this->requestedZAngle,
					this->remotecontrol->getch3());
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

			updateRequestedAngle(Xangle, Yangle, this->requestedZAngle,
					thrustFactor);
			this->controlCycle();

			usleep(SleepTime);

		}

	}

}

void Control::UpdateRequestedVelocity(double Xspeed, double Yspeed,
		double Zspeed, double zAngle) {

	this->requestedXvelocity = Xspeed;
	this->requestedYvelocity = Yspeed;
	this->requestedZvelocity = Zspeed;
	this->requestedZAngle = zAngle;
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
	this->OuterThrust = new PID(0, 0, 0, 0, 0, timestart, OuterThrustKp,
			OuterThrustKi, OuterThrustKd);

	gettimeofday(&this->timestart, NULL);
	this->InnerThrust = new PID(0, 0, 0, 0, 0, timestart, InnerThrustKp,
			InnerThrustKi, InnerThrustKd);

	this->remotecontrol = new Remotehandler();

	this->Motor1 = new Motor();
	Motor1->init(1);
	this->Motor2 = new Motor();
	Motor2->init(2);
	this->Motor3 = new Motor();
	Motor3->init(3);
	this->Motor4 = new Motor();
	Motor4->init(4);

	sleep(2); //sleep<---------------------------
}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

}/* namespace std */
