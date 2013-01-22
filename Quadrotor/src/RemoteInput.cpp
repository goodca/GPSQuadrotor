/*
 * RemoteInput.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: cooperdl
 */

#include "RemoteInput.h"

namespace std {

RemoteInput::RemoteInput(int remoteChannel, int gpio) {
	channel = remoteChannel;
	if (remoteChannel == 1) {
		set_mux_value("gpmc_ad6", 7);
		export_gpio();
		gpio = 38;
	}

	set_gpio_edge("both");
	pollInputThread();

}

void RemoteInput::pollInputThread() {
	timeout = TIMEOUT;
	struct pollfd fdset[2];
	int nfds = 2;
	int gpio_fd, timeout, rc;
	char buf[MAX_BUF];
	int len;

	while (1) {
			memset((void*)fdset, 0, sizeof(fdset));

			fdset[0].fd = STDIN_FILENO;
			fdset[0].events = POLLIN;

			fdset[1].fd = gpio_fd;
			fdset[1].events = POLLPRI;

			rc = poll(fdset, nfds, timeout);

			if (rc < 0) {
				printf("\npoldirectionl() failed!\n");
				return;
			}

			if (rc == 0) {
				printf(".");
			}

			if (fdset[1].revents & POLLPRI) {
				lseek(fdset[1].fd, 0, SEEK_SET);  // Read from the start of the file
				len = read(fdset[1].fd, buf, MAX_BUF);
				printf("\npoll() GPIO %d interrupt occurred, value=%c, len=%d\n",
					 gpio, buf[0], len);
			}

			if (fdset[0].revents & POLLIN) {
				(void)read(fdset[0].fd, buf, 1);
				printf("\npoll() stdin read 0x%2.2X\n", (unsigned int) buf[0]);
			}

			fflush(stdout);
		}


	return;
}

void RemoteInput::set_gpio_edge(char* edge) {
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
	return;
}

int RemoteInput::set_gpio_direction(char* direction) {
	FILE *fp;
	char path[MAX_BUF];

//create path using specified gpio
	snprintf(path, sizeof path, "/sys/class/gpio/gpio%d/direction", gpio);
//open direction file
	if ((fp = fopen(path, "w")) == NULL) {
		printf("Cannot open specified direction file. Is gpio%d exported?\n",
				gpio);
		return 1;
	}

//write "in" or "out" to direction file
	rewind(fp);
	fprintf(fp, "%s\n", direction);
	fflush(fp);
	fclose(fp);
}

void RemoteInput::export_gpio() {
	FILE *fp;

//open the export file
	if ((fp = fopen("/sys/class/gpio/export", "ab")) == NULL) {
		printf("Cannot open export file. \n");
		return;
	}

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
