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

namespace std {

class GPS {
public:
	GPS();
	virtual ~GPS();
	void init();
	void getGPSData();

private:
	int serial_file;
	void setMuxing();
	void getCalculateLine();
	typedef struct {
		double x;
		double y;
		double time;
		int valid;
	} dataGPS;
};

} /* namespace std */
#endif /* GPS_H_ */
