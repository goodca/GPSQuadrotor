/*
 * GPSNavigtor.cpp
 *
 *  Created on: Jan 29, 2013
 *      Author: cooperdl
 */

#include "GPSNavigtor.h"
#include "GPSWaypoints.h"



namespace std {

GPSNavigtor::GPSNavigtor() {
	// TODO Auto-generated constructor stub

}

void GPSNavigtor::startUp() {

}

void GPSNavigtor::nextPoint() {

	reqestedVelocity = requestedLocation->getReqestedVelocity();
	requestedLatitude = requestedLocation->getRequestedLatitude();
	requestedLatitude = requestedLocation->getRequestedLatitude();
	requestedAbsoluteHeight = requestedLocation->getRequestedAbsoluteHeight();
	}

GPSNavigtor::~GPSNavigtor() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
