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

namespace std{

class Control {

	double thrust;

	double requestedXAngle;
	double requestedYAngle;
	double requestedZAngle;
	double requestedThrust;

	double requestedXAngleRate;
	double requestedYAngleRate;
	double requestedZAngleRate;
	double requestedThrustRate;

	double realXAngle;
	double realYAngle;
	double realZAngle;
	double realXAngleRate;
	double realYAngleRate;
	double realZAngleRate;

	timeval timestart;

    Sensors *realData;

    PID *OuterX;
    PID *InnerX;
    PID *OuterY;
    PID *InnerY;
    PID *OuterZ;
    PID *InnerZ;



	Motor *Motor1;
	Motor *Motor2;
	Motor *Motor3;
	Motor *Motor4;

public:
	Control(Sensors * data);

	void updateRequestedAngle(double xAngle, double yAngle, double zAngle, double thrust);
	void getSensorClass(Sensors sense);
	void controlCycle();

	void controlStart();

	void controlRun();


	virtual ~Control();
};

} /* namespace std */

#endif /* CONTROL_H_ */
