/*
 * GPSWaypoints.h
 *
 *  Created on: Jan 29, 2013
 *      Author: chris
 */

#ifndef GPSWAYPOINTS_H_
#define GPSWAYPOINTS_H_

#include "Waypoint.h"


namespace std {

class GPSWaypoints {
public:
	GPSWaypoints();
	virtual ~GPSWaypoints();
	Waypoint* getNextWaypoint();
};

} /* namespace std */
#endif /* GPSWAYPOINTS_H_ */
