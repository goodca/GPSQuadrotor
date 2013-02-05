/*
 * Waypoint.cpp
 *
 *  Created on: Dec 13, 2012
 *      Author: chris
 */

#include "Waypoint.h"

Waypoint::Waypoint() {
	// TODO Auto-generated constructor stub

}

double Waypoint::getRequestedLongtitude(){
	return 0;
}
double Waypoint::getRequestedLatitude(){
	return 0;
} //in degrees
double Waypoint::getReqestedVelocity(){
	return 0;
} //in m/s
double Waypoint::getRequestedAbsoluteHeight(){
	return 0;
} //height above sea level
double Waypoint::getRequestedTimeAtWaypoint(){
	return 0;
} //time in seconds to stay at waypoint after reached
double Waypoint::getRequestedHeadingRotationSpeed(){
	return 0;
} //in degrees/s
double Waypoint::getRequestedHeadingAtWaypoint(){
	return 0;
} //in degrees from north
int Waypoint::takeoffWaypoint(){
	return 0;
}
int Waypoint::landWaypoint(){
	return 0;
}

Waypoint::~Waypoint() {
	// TODO Auto-generated destructor stub
}

