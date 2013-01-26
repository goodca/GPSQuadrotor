/*
 * RemoteInput.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: cooperdl
 */

#include "RemoteInput.h"
#include <sys/time.h>

namespace std {

RemoteInput::RemoteInput() {

	return;
}

void RemoteInput::start(int remoteChannel) {
	timesBeforeReliable = 100;
	channel = remoteChannel;
	if (channel == 1) {
//		set_mux_value("gpmc_ad6", 7);
		char* name;
		name = "gpmc_ad6";
		;

		printf("Set gpio to %d\n", gpio);
	}



	pthread_create(&remoteThread_t, 0, &RemoteInput::start_thread, this);

	return;
}

double RemoteInput::get_percent_amount(){

	return this->PercentAmount;

}

void RemoteInput::remoteThread(void *obj) {
	RemoteInput *remote = (RemoteInput*) obj;
	remote->update();

}
void RemoteInput::update(){
	struct pollfd fdset[2];
		int nfds = 2;
		int gpio_fd, timeout, rc;
		char buf[MAX_BUF];
		unsigned int gpio;
		int len;

		// Set the signal callback for Ctrl-C
	//		signal(SIGINT, signal_handler);

	//		gpio = atoi(argv[1]);

		export_gpio();
		set_gpio_direction(0);
		set_gpio_edge("both"); // Can be rising, falling or both
		gpio_fd = gpio_fd_open();

		timeout = TIMEOUT;
		this->minTime = 1200;

		this->maxTime = 1750;
		averagedPeriod = minTime;

		while (1) {
			memset((void*) fdset, 0, sizeof(fdset));

			fdset[0].fd = STDIN_FILENO;
			fdset[0].events = POLLIN;

			fdset[1].fd = gpio_fd;
			fdset[1].events = POLLPRI;

			rc = poll(fdset, nfds, timeout);

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

					gettimeofday(&this->starttime, NULL);
	//				printf("high\n");

				} else if (buf[0] == '0') {
					if (timesBeforeReliable >= 0) {
						timesBeforeReliable--;
					}
					{
						gettimeofday(&this->endtime, NULL);
						double timechange = (1000000 * this->endtime.tv_sec
								+ this->endtime.tv_usec)
								- (1000000 * this->starttime.tv_sec
										+ this->starttime.tv_usec);


						if ((timechange > MIN_LEGIT_PERIOD_US)
								&& (timechange < MAX_LEGIT_PERIOD_US)) {
							averagedPeriod += (timechange - averagedPeriod)
									/ FRAC_SAMPLE_TO_AVERAGE;

							if (averagedPeriod > this->maxTime) {
								printf("timechange: %f maxtime was: %f\n",
										timechange, maxTime);
								this->maxTime = timechange;
								printf("timechange: %f maxtime is now: %f\n",
										timechange, maxTime);

							}
							if (averagedPeriod < this->minTime) {
								printf("timechange: %f mintime was: %f\n",
										timechange, minTime);
								if (timechange > 0) {
									this->minTime = timechange;
								}
								printf("timechange: %f mintime is now %f\n",
										timechange, minTime);
							}
							if (timechange > 1500) {
	//					printf("over 50%!\n");
							}
							this->PercentAmount = (timechange - minTime)
									/ ((maxTime - minTime) / 100);
						}
						printf("total time=%f percent=%f averagedTime = %f\nMin =%f Max = %f\n", timechange,
													this->PercentAmount, averagedPeriod, minTime, maxTime);
	//				printf("low\n total time=%f\n percent=%f\n", timechange,
	//						this->PercentAmount);
	//				printf("max is %f, min is %f\n", this->minTime, this->maxTime);

					}
				} else {
	//				printf("Invalid result, but we got: %c\n", buf[0]);
				}

			}

			if (fdset[0].revents & POLLIN) {
				(void) read(fdset[0].fd, buf, 1);
				printf("\npoll() stdin read 0x%2.2s\n", buf[0]);
			}

			fflush(stdout);
		}

		close(gpio_fd);
		return;
}
int RemoteInput::gpio_fd_open() {
	printf("Gpio = %d gpio_fd_open\n", gpio);
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);

	fd = open(buf, O_RDONLY | O_NONBLOCK);
	if (fd < 0) {
		perror("gpio/fd_open");
	}
	printf("Gpio = %d gpio_fd_open\n", gpio);
	return fd;
}

void RemoteInput::set_gpio_edge(char* edge) {
	printf("Gpio = %d set gpio edge\n", gpio);
	FILE *fp;
	char path[MAX_BUF];

//create path using specified gpio
	snprintf(path, sizeof path, "/sys/class/gpio/gpio%d/edge", gpio);
//open edge file
	if ((fp = fopen(path, "w")) == NULL) {
		printf("Cannot open specified edge file. Is gpio%d exported?\n", gpio);
		return;
	}

//write "rising", "falling", or "both" to edge file
	rewind(fp);
	fprintf(fp, "%s\n", edge);
	fflush(fp);
	fclose(fp);
	printf("Gpio = %d set gpio edge\n", gpio);
	return;
}

int RemoteInput::set_gpio_direction(int direction) {
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);

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

void RemoteInput::export_gpio() {
	FILE *fp;

//open the export file
	if ((fp = fopen("/sys/class/gpio/export", "ab")) == NULL) {
		printf("Cannot open export file. \n");
		return;
	}
	printf("Exporting gpio %d\n", gpio);
//write specified gpio to export file
	fprintf(fp, "%d\n", gpio);
	fflush(fp);
	fclose(fp);

//return 0 if everything runs correctly
	return;
}

int RemoteInput::set_mux_value(char* mux, int value) {
	FILE *fp;
	char path[MAX_BUF];

	snprintf(path, sizeof path, "/sys/kernel/debug/omap_mux/%s", mux);

	if ((fp = fopen(path, "w")) == NULL) {
		printf("Cannot open specified mux, %s\n", mux);
		return 1;
	}

	rewind(fp);
	fprintf(fp, "%d\n", value);
	fflush(fp);
	fclose(fp);
	return 0;

}

RemoteInput::~RemoteInput() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
