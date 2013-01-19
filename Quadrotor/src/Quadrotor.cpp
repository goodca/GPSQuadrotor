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
#include "IMU.h"
#include <math.h>
#include "Sensors.h"
extern "C" {
#include "quadthread.h"
#include "Control.h"
#include <pthread.h>
}

using namespace std;

pthread_t cppThread;

int main() {
	//cout << "Hello World" << endl; // prints
	Sensors *sense = new Sensors;
	Control *controller = new Control(sense);
	puts("In main"); /* prints Broked */
	sense->startSensorsThreads();




//	sense->stopThread();
	sleep(40);
	return 0;
}
