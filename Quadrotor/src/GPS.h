/*
 * GPS.h
 *
 *  Created on: Dec 24, 2012
 *      Author: chris
 */

#ifndef GPS_H_
#define GPS_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>      /*Enables use of flags to modify open(), read(), write() functions*/
#include <unistd.h>     /*Enables use of open(), read(), write()*/
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

namespace std {

class GPS {
public:
	GPS();
	virtual ~GPS();
	void init();

	void startGPSThread();
	int getThreadRunning();
	void stopThread();
	void update();
	double getLatitude();			//in degrees
	double getLongtitude();			//in degrees
	double getHeight();				//in meters from sea level
	double getSpeed();				//in meters per second
	double getDirectionHeading();	//degrees from north

private:
	void getGPSData();
	int serial_file;
	void setMuxing();
	void getCalculateLine();
	typedef struct {
		double x;
		double y;
		double time;
		int valid;
	} dataGPS;

	double time;
	double speedKnots;
	double courseOverGround;
	int date;
	char latpos;
	char longpos;
	char isValid;
	double latitude;
	double longtitude;

	int threadRunning;
	pthread_t gpsThread_t;
	void gpsThread(void *obj);
	static void * start_thread(void *obj) {
		reinterpret_cast<GPS *>(obj)->gpsThread(obj);
		return 0;
	}
};

#define KNOTS_TO_METERS 0;

} /* namespace std */
#endif /* GPS_H_ */
