/*
 * GPSNavigtor.cpp
 *
 *  Created on: Jan 29, 2013
 *      Author: cooperdl
 */

#include "GPSNavigtor.h"

namespace std {

GPSNavigtor::GPSNavigtor() {
	// TODO Auto-generated constructor stub

}

void GPSNavigtor::startUp() {

}

void GPSNavigtor::nextPoint() {

	this->ReqestedVelocity = this->requestedLocation.getReqestedVelocity()
	this->RequestedLongtitude=this->requestedLocation.getRequestedLongtitude(); //in degrees
	this->RequestedLatitude=this->requestedLocation.getRequestedLatitude(); //in degrees
	this->ReqestedVelocity=this->requestedLocation.getReqestedVelocity(); //in m/s
	this->RequestedAbsoluteHeight=this->requestedLocation.getRequestedAbsoluteHeight(); //height above sea level
	this->RequestedTimeAtWaypoint=this->requestedLocation.getRequestedTimeAtWaypoint(); //time in seconds to stay at waypoint after reached
	this->RequestedHeadingRotationSpeed=this->requestedLocation.getRequestedHeadingRotationSpeed(); //in degrees/s
	this->RequestedHeadingAtWaypoint=this->requestedLocation.getRequestedHeadingAtWaypoint(); //in degrees from north
	this->takeoffWaypoint=this->requestedLocation.takeoffWaypoint();
	this->landWaypoint=this->requestedLocation.landWaypoint();

}

GPSNavigtor::~GPSNavigtor() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
