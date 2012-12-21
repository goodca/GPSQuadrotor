//============================================================================
// Name        : Quadrotor.cpp
// Author      : Chris Good and David Cooper
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include "Gyroscope.h"

using namespace std;

int main() {
	cout << "Hello World" << endl; // prints
	Gyroscope *gyro = new Gyroscope;
	gyro->update();
	while (true) {
		gyro->update();
		printf("x; %f\n", gyro->getX());
		printf("y; %f\n", gyro->getY());
		printf("z; %f\n", gyro->getZ());

		sleep(1);
	}
	return 0;
}
