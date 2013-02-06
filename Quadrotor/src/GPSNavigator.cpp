/*
 * GPSNavigtor.cpp
 *
 *  Created on: Jan 29, 2013
 *      Author: cooperdl
 */

#include "GPSNavigtor.h"
#include "GPSWaypoints.h"
#include "Waypoint.h"



namespace std {

GPSNavigtor::GPSNavigtor() {
	// TODO Auto-generated constructor stub

}

void GPSNavigtor::startUp() {

	GPSCords = new GPSWaypoints();


}

void GPSNavigtor::GPSNavigtorRun(){

	this->startUp();

	while(1){
		this->nextPoint();






	}


}

void GPSNavigtor::nextPoint() {

	requestedLocation = GPSCords->getNextWaypoint();

	reqestedVelocity = requestedLocation->getReqestedVelocity();
	requestedLatitude = requestedLocation->getRequestedLatitude();
	requestedLatitude = requestedLocation->getRequestedLatitude();
	requestedAbsoluteHeight = requestedLocation->getRequestedAbsoluteHeight();
	requestedTimeAtWaypoint = requestedLocation->getRequestedTimeAtWaypoint();
	requestedHeadingAtWaypoint = requestedLocation->getRequestedHeadingAtWaypoint();
	requestedHeadingRotationSpeed = requestedLocation->getRequestedHeadingRotationSpeed();
	landWaypoint=requestedLocation->landWaypoint();
	takeoffWaypoint=requestedLocation->takeoffWaypoint();
	}

GPSNavigtor::~GPSNavigtor() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
