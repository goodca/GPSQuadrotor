///*
// * GPSNavigtor.h
// *
// *  Created on: Jan 29, 2013
// *      Author: cooperdl
// */
//
//#ifndef GPSNAVIGTOR_H_
//#define GPSNAVIGTOR_H_
//#include "Waypoint.h"
//#include "Control.h"
//#include "PID.h"
//
//
//namespace std {
//
//class GPSNavigtor {
//public:
//
//	Control QuadControl;
//
//	Waypoint requestedLocation;
//
//	PID zAngle;
//
//	PID yLocationInner;
//	PID yLocationOuter;
//
//	PID xLocationInner;
//	PID xLocationOuter;
//
//	PID zLocationInner;
//	PID zLocationOuter;
//
//	double RequestedLongtitude;			//in degrees
//	double RequestedLatitude;				//in degrees
//	double ReqestedVelocity;				//in m/s
//	double RequestedAbsoluteHeight;		//height above sea level
//	double RequestedTimeAtWaypoint; 		//time in seconds to stay at waypoint after reached
//	double RequestedHeadingRotationSpeed; 	//in degrees/s
//	double RequestedHeadingAtWaypoint; 	//in degrees from north
//	int takeoffWaypoint;
//	int landWaypoint;
//
//	GPSNavigtor();
//	virtual ~GPSNavigtor();
//	void GPSNavigtorRun();
//
//	void nextPoint();
//	void navigateCycle();
//	void startUp();
//
//
//
//
//
//
//
//};
//
//} /* namespace std */
//#endif /* GPSNAVIGTOR_H_ */
