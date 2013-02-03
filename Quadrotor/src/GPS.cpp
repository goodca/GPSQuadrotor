/*
 * GPS.cpp
 *
 *  Created on: Dec 24, 2012
 *      Author: chris
 */

#include "GPS.h"

namespace std {

GPS::GPS() {
	// TODO Auto-generated constructor stub

}

void GPS::startGPSThread() {
	threadRunning = 1;

	pthread_create(&gpsThread_t, 0, &GPS::start_thread, this);

	return;
}
void GPS::gpsThread(void *obj) {
	//cast to object in order to call original instance
	GPS *threadGPS = (GPS *) obj;
	threadGPS->init();

	while (threadGPS->getThreadRunning()) {
		printf("GPS looping\n");
		threadGPS->update();
//		update();

		usleep(500000);
	}
	return;
}

void GPS::update() {
	getGPSData();
	return;
}

int GPS::getThreadRunning() {
	return threadRunning;
}
void GPS::stopThread() {
	threadRunning = 0;
	return;
}

void GPS::setMuxing() {
	FILE* fp;
	//open the export file for rxd
	fp = fopen("/sys/kernel/debug/omap_mux/uart1_rxd", "ab");
	if (fp == 0) {
		printf("Cannot open export file. \n");
	}
	//write specified gpio to export file for txd
	fprintf(fp, "20\n");
	fflush(fp);
	fclose(fp);
	fp = fopen("/sys/kernel/debug/omap_mux/uart1_txd", "ab");
	if (fp == 0) {
		printf("Cannot open export file. \n");
	}
	//write specified gpio to export file for txd
	fprintf(fp, "0\n");
	fflush(fp);
	fclose(fp);
}

void GPS::init() {
	setMuxing();
	FILE *config_location;
	if ((config_location = fopen("/sys/kernel/debug/omap_mux/uart1_txd", "rb+"))
			== NULL)
		printf("Cannot set TX");
	char str[5] = { 0 };
	strcpy(str, "0");
	rewind(config_location);
	fwrite(&str, sizeof(char), strlen(str), config_location);
	fclose(config_location);
	if ((config_location = fopen("/sys/kernel/debug/omap_mux/uart1_rxd", "rb+"))
			== NULL)
		printf("Cannot set RX");
	strcpy(str, "20");
	rewind(config_location);
	fwrite(&str, sizeof(char), strlen(str), config_location);
	fclose(config_location);
	serial_file = open("/dev/ttyO1", O_RDWR);
	if (serial_file == -1)
		fprintf(stderr, "Failed to open UART1: %m\n");
	else

		return;
}

void GPS::getCalculateLine() {
	char data[100] = { 0 };

	if (!(read(serial_file, data, 100) > 0)) {
		//fprintf(stderr, "Failed to read GPS: %m\n");
		printf("Failed to read GPS\n");
	}
	double tempx, tempy;
	sscanf(data, ",%lf, %c, %lf, %c, %lf, %c, %lf, %lf, %d,", &time, &isValid,
			&tempy, &latpos, &tempx, &longpos, &speedKnots, &courseOverGround,
			&date);
	if (tempx == 0) {
		isValid = 0;
		printf("Data is not yet valid\n");
	} else {
		if (latpos == 'S')
			tempy = -tempy;
		if (longpos == 'W')
			tempx = -tempx;

		longtitude = (int) tempx / 100
				+ ((int) tempx % 100 + tempx - (int) tempx) / 60.0;
		latitude = (int) tempy / 100
				+ ((int) tempy % 100 + tempy - (int) tempy) / 60.0;

		printf(
				"CORRECTED FORM\nLatitude: %f, Longtitude: %f\nSpeed in knots: %f course: %f\nSpeed in mph: %f\n",
				latitude, longtitude, speedKnots, courseOverGround,
				speedKnots * 1.151);
	}
}

void GPS::getGPSData() {
	char character[1];
	char rightType[5] = { 'G', 'P', 'R', 'M', 'C' };
	int right = false;
	int i = 0;
	while (threadRunning) {
		if (!(read(serial_file, character, 1) > 0)) {
			printf("Failed to read GPS\n");
		}
		if (character[0] == '$') {

			right = true;
		} else {
			right = false;
		}
		if (right) {
			for (i = 0; i < 5; i++) {
				read(serial_file, character, 1);

				if (character[0] == rightType[i]) {
					//do nothing
					if (i == 4) { //getting here means we have gone all the way through the sequence
//							printf("correct sequence received!\n");
						getCalculateLine();

					}

				} else {
					break;
				}
			}

		}
//
//		if (!(read(serial_file, data, 100) > 0)) {
//			//fprintf(stderr, "Failed to read GPS: %m\n");
//			printf("Failed to read GPS\n");
//		}
//		//printf("The data recieved is: %s\n", data);
//
//		for (i = 0; i < 6; i++) {
//			type[i] = data[i];
//		}
//		//printf("The data type is: %s\n", type);
//
//		if (type == rightType) {
//			printf("We got the right type! <------------------\n");
//		} else {
//			printf("We didn't get the right type :/ \n");
//		}
//
//		if (!strncmp(data, "GPGLL", 6)) {
//			printf("the data didn't match\n");
//			if ((matches = sscanf(data, "%6s,%lf,%c,%lf,%c,%lf,%c", start,
//					&temp.y, &latpos, &temp.x, &longpos, &temp.time, &isValid))
//					== 0) {
//				printf("Yeah, that last thing was bogus");
//			}
//			break;
//		} else {
//			printf("the data didn't match\n");
//		}
//
	}
//	printf("The data recieved is: %s\n",data);
//	printf("Latitude: %f, Longtitude: %f\n", temp.y, temp.x);
//	if (temp.x == 0)
//		temp.valid = 0;
//	else {
//		if (latpos == 'S')
//			temp.y = -temp.y;
//		if (longpos == 'W')
//			temp.x = -temp.x;
//	}
//	temp.x = (int) temp.x / 100
//			+ ((int) temp.x % 100 + temp.x - (int) temp.x) / 60.0;
//	temp.y = (int) temp.y / 100
//			+ ((int) temp.y % 100 + temp.y - (int) temp.y) / 60.0;
//	temp.valid = 1;
//	printf("Latitude: %f, Longtitude: %f\n", temp.y, temp.x);
//	temp.x = -87.322740;
//	temp.y = 39.483990;
	return;
}
double GPS::getLatitude() {
	return latitude;
}
double GPS::getLongtitude() {
	return longtitude;
}
double GPS::getHeight() {
	return 0;
}
double GPS::getSpeed() {
	return speedKnots * KNOTS_TO_METERS;
}
double GPS::getDirectionHeading(){
	return courseOverGround;
}

GPS::~GPS() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
