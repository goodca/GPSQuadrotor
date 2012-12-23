//============================================================================
// Name        : Quadrotor.cpp
// Author      : Chris Good and David Cooper
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include "Gyroscope.h"
#include "Accelerometer.h"
#include <math.h>

using namespace std;

int main() {
	cout << "Hello World" << endl; // prints
	Gyroscope *gyro = new Gyroscope;
	Accelerometer *acel = new Accelerometer;
	gyro->init();
	gyro->update();
	acel->init();
	acel->update();
	sleep(4);
	double xInt = 0;
	double yInt = 0;
	double zInt = 0;
	double xAcel;
	double yAcel;
	double zAcel;
	double magnitude;
	int uToWait = 100000;
	int clkDiv = 0;
	while (true) {
		clkDiv++;
		gyro->update();
		acel->update();
		xInt += gyro->getX() * uToWait / 1000000;
		yInt += gyro->getY() * uToWait / 1000000;
		zInt += gyro->getZ() * uToWait / 1000000;
		xAcel = acel->getX();
		yAcel = acel->getY();
		zAcel = acel->getZ();
		magnitude = sqrt(xAcel * xAcel + yAcel * yAcel + zAcel * zAcel);
		if (clkDiv > 10) {
			printf("\n");
//			printf("x; %f\n", xInt);
//			printf("y; %f\n", yInt);
//			printf("z; %f\n", zInt);

			if ((magnitude > 0.995) && (magnitude < 1.05)) {
				printf("x; %f\n", xAcel);
				printf("y; %f\n", yAcel);
				printf("z; %f\n", zAcel);
				printf("total magnitude: %f\n", magnitude);
				printf("Pitch: %f*\n", acel->getPitch());
				printf("Roll: %f*\n", acel->getRoll());
			}
			clkDiv += -3;
		}
		usleep(uToWait);
	}
	return 0;
}
