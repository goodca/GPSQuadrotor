/*
 * RangeFinder.h
 *
 *  Created on: Jan 31, 2013
 *      Author: chris
 */

#ifndef RANGEFINDER_H_
#define RANGEFINDER_H_

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/time.h>
#include <pthread.h>

namespace std {

class RangeFinder {
public:
	RangeFinder();
	void start();
	double getDistance(); //returns distance from ground in meters
	virtual ~RangeFinder();

private:
	pthread_t rangeFinderThread_t;
	struct pollfd fdset[2];
	timeval starttime;
	timeval endtime;


	int nfds, rc, gpio_fd, len, threadRunning;
	double meters, inches;
	char buf[127];

	void rangeFinderThread(void *obj);
	void update();
	void export_gpio();
	int set_gpio_direction(int direction); //0 means in, 1 means out
	void set_gpio_edge(char* edge);
	int gpio_fd_open();
	void calculateTimeSincePulseStart();
	static void * start_thread(void *obj) {
		reinterpret_cast<RangeFinder *>(obj)->rangeFinderThread(obj);
		return 0;
	}
};

#define MAX_BUF 127
#define TIMEOUT 5000
#define GPIO 66
#define US_PER_INCH 147

} /* namespace std */
#endif /* RANGEFINDER_H_ */
