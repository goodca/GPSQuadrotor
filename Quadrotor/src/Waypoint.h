/*
 * Waypoint.h
 *
 *  Created on: Dec 13, 2012
 *      Author: chris
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_

class Waypoint {
public:
	Waypoint();
	virtual ~Waypoint();
	double getRequestedLongtitude();			//in degrees
	double getRequestedLatitude();				//in degrees
	double getReqestedVelocity();				//in m/s
	double getRequestedAbsoluteHeight();		//height above sea level
	double getRequestedTimeAtWaypoint(); 		//time in seconds to stay at waypoint after reached
	double getRequestedHeadingRotationSpeed(); 	//in degrees/s
	double getRequestedHeadingAtWaypoint(); 	//in degrees from north
	int takeoffWaypoint();
	int landWaypoint();
};

#endif /* WAYPOINT_H_ */
