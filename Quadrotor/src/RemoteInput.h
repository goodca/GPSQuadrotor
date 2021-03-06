/*
 * RemoteInput.h
 *
 *  Created on: Jan 21, 2013
 *      Author: cooperdl
 */

#ifndef REMOTEINPUT_H_
#define REMOTEINPUT_H_

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

class RemoteInput {
public:
	RemoteInput();
	void start(int remoteChannel);
	virtual ~RemoteInput();
	double get_percent_amount();
private:
	int timesBeforeReliable;
	FILE *valuefp;
	double minTime;
	double maxTime;
	double averagedPeriod;
	double fastAveragedPeriod;
	pthread_t remoteThread_t;

	int channel;
	int gpio;
	int timeout;
	timeval starttime;
	timeval endtime;
	double PercentAmount;
	void update();
	void export_gpio();
	int set_mux_value(char* mux, int value);
	int set_gpio_direction(int direction); //0 means in, 1 means out
	void set_gpio_edge(char* edge);
	int gpio_fd_open();
	void remoteThread(void *obj);
	void calculateTimeSincePulseStart();
	static void * start_thread(void *obj) {
		reinterpret_cast<RemoteInput *>(obj)->remoteThread(obj);
		return 0;
	}
};

#define MAX_BUF 127
#define TIMEOUT 5000
#define MIN_LEGIT_PERIOD_US 900
#define MAX_LEGIT_PERIOD_US 2100
#define MIDDLE_PERIOD_US 1500
#define FRAC_SAMPLE_TO_AVERAGE 25
#define SMALL_FRAC_SAMPLE_TO_AVERAGE 5
#define GPIO1 38
#define GPIO2 39
#define GPIO3 34
#define GPIO4 67

} /* namespace std */
#endif /* REMOTEINPUT_H_ */
