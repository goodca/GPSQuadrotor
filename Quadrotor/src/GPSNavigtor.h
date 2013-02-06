/*
 * GPSNavigtor.h
 *
 *  Created on: Jan 29, 2013
 *      Author: cooperdl
 */

#ifndef GPSNAVIGTOR_H_
#define GPSNAVIGTOR_H_
#include "Waypoint.h"
#include "GPSWaypoints.h"
#include "Control.h"

#include "PID.h"

namespace std {

class GPSNavigtor {

	Control *QuadControl;

	GPSWaypoints *GPSCords;

	Waypoint *requestedLocation;

	PID * zAngle;

	PID * yLocationInner;
	PID * yLocationOuter;

	PID * xLocationInner;
	PID * xLocationOuter;

	PID * zLocationInner;
	PID * zLocationOuter;


public:

	GPSNavigtor();
	virtual ~GPSNavigtor();
	void GPSNavigtorRun();
	void nextPoint();
	void navigateCycle();
	void startUp();
private:
	double requestedLongtitude; //in degrees
	double requestedLatitude; //in degrees
	double reqestedVelocity; //in m/s
	double requestedAbsoluteHeight; //height above sea level
	double requestedTimeAtWaypoint; //time in seconds to stay at waypoint after reached
	double requestedHeadingRotationSpeed; //in degrees/s
	double requestedHeadingAtWaypoint; //in degrees from north
	int takeoffWaypoint;
	int landWaypoint;

};

} /* namespace std */
#endif /* GPSNAVIGTOR_H_ */
