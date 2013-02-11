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
#include "Sensors.h"
#include "PID.h"
#include "Remotehandler.h"

namespace std{

class Control {

private:
	int remote;
	FILE *angleSpeedFile;
	FILE *PIDFile;

	double thrust;

	double requestedXAngle;
	double requestedYAngle;
	double requestedZAngle;
	double requestedThrust;


	double requestedXvelocity;
	double requestedYvelocity;
	double requestedZvelocity;



	timeval timestart;

    Sensors *realData;

    PID *OuterX;
    PID *InnerX;
    PID *OuterY;
    PID *InnerY;
    PID *OuterZ;
    PID *InnerZ;

    PID *InnerThrust;
    PID *OuterThrust;

    PID *Xvelocity;
    PID *Yvelocity;

    Remotehandler *remotecontrol;

	Motor *Motor1;
	Motor *Motor2;
	Motor *Motor3;
	Motor *Motor4;

	void controlCycle();
	void updateRequestedAngle(double xAngle, double yAngle, double zAngle, double thrust);
	void setRemote(int on);
	void controlStart();


public:
	Control();


	void UpdateRequestedVelocity(double Xspeed, double yspeed, double zspeed, double zAngle);


	void controlRun(Sensors * data);


	virtual ~Control();
};

} /* namespace std */

#endif /* CONTROL_H_ */
