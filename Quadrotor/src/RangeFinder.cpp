/*
 * RangeFinder.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: chris
 */

#include "RangeFinder.h"

namespace std {

RangeFinder::RangeFinder() {
	// TODO Auto-generated constructor stub

}

void RangeFinder::start() {
	nfds = 2;

	// Set the signal callback for Ctrl-C
	//		signal(SIGINT, signal_handler);

	//		gpio = atoi(argv[1]);

	export_gpio();
	set_gpio_direction(0);
	set_gpio_edge("both"); // Can be rising, falling or both
	gpio_fd = gpio_fd_open();

	threadRunning = 1;
	pthread_create(&rangeFinderThread_t, 0, &RangeFinder::start_thread, this);
}

void RangeFinder::rangeFinderThread(void *obj) {
	RangeFinder *range = (RangeFinder*) (obj);
	while (threadRunning) {
		range->update(); //polling so no sleep needed
	}
}

void RangeFinder::update() {

	memset((void*) fdset, 0, sizeof(fdset));

	fdset[0].fd = STDIN_FILENO;
	fdset[0].events = POLLIN;

	fdset[1].fd = gpio_fd;
	fdset[1].events = POLLPRI;

	rc = poll(fdset, nfds, TIMEOUT);

	if (rc < 0) {
		printf("\npoll() failed!\n");
		return;
	}

	if (rc == 0) {
		printf(".");
	}

	if (fdset[1].revents & POLLPRI) {
		lseek(fdset[1].fd, 0, SEEK_SET); // Read from the start of the file
		len = read(fdset[1].fd, buf, MAX_BUF);
		//			printf("\npoll() GPIO %d interrupt occurred, value=%c, len=%d\n", gpio, buf[0], len);
		//			printf("the read gives: %c\n", buf[0]);

		char buf2[MAX_BUF];
		char buf3[MAX_BUF];
		buf2[0] = '0';
		buf3[0] = '1';
		//				char value = *buf[0];

		if (buf[0] == '1') {
			calculateTimeSincePulseStart();

		} else if (buf[0] == '0') {
			gettimeofday(&this->starttime, NULL);
			//				printf("high\n");
		} else {
			//				printf("Invalid result, but we got: %c\n", buf[0]);
		}

	}

	if (fdset[0].revents & POLLIN) {
		(void) read(fdset[0].fd, buf, 1);
		printf("\npoll() stdin read 0x%2.2s\n", buf[0]);
	}

	return;
}

void RangeFinder::calculateTimeSincePulseStart() {

	gettimeofday(&this->endtime, NULL);
	double timechange = (1000000 * this->endtime.tv_sec + this->endtime.tv_usec)
			- (1000000 * this->starttime.tv_sec + this->starttime.tv_usec);

}
int RangeFinder::gpio_fd_open() {
	printf("Gpio = %d gpio_fd_open\n", GPIO);
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", GPIO);

	fd = open(buf, O_RDONLY | O_NONBLOCK);
	if (fd < 0) {
		perror("gpio/fd_open");
	}
	printf("Gpio = %d gpio_fd_open\n", GPIO);
	return fd;
}

void RangeFinder::set_gpio_edge(char* edge) {
	printf("Gpio = %d set gpio edge\n", GPIO);
	FILE *fp;
	char path[MAX_BUF];

//create path using specified gpio
	snprintf(path, sizeof path, "/sys/class/gpio/gpio%d/edge", GPIO);
//open edge file
	if ((fp = fopen(path, "w")) == NULL) {
		printf("Cannot open specified edge file. Is gpio%d exported?\n", GPIO);
		return;
	}

	//write "rising", "falling", or "both" to edge file
	rewind(fp);
	fprintf(fp, "%s\n", edge);
	fflush(fp);
	fclose(fp);
	printf("Gpio = %d set gpio edge\n", GPIO);
	return;
}
int RangeFinder::set_gpio_direction(int direction) {
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", GPIO);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/direction");
		return fd;
	}

	if (direction)
		write(fd, "out", 4);
	else
		write(fd, "in", 3);

	close(fd);
	return 0;
}

void RangeFinder::export_gpio() {
	FILE *fp;

//open the export file
	if ((fp = fopen("/sys/class/gpio/export", "ab")) == NULL) {
		printf("Cannot open export file. \n");
		return;
	}
	printf("Exporting gpio %d\n", GPIO);
//write specified gpio to export file
	fprintf(fp, "%d\n", GPIO);
	fflush(fp);
	fclose(fp);

//return 0 if everything runs correctly
	return;
}

RangeFinder::~RangeFinder() {
	close(gpio_fd);
}

} /* namespace std */
