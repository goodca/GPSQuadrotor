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
#include "Motor.h"
}

using namespace std;

pthread_t cppThread;

int main() {
	//cout << "Hello World" << endl; // prints
	Sensors *sense = new Sensors;
	Control *controller = new Control(sense);
	puts("In main"); /* prints Broked */
//	sense->startSensorsThreads();
	Motor *motor1 = new Motor();
	Motor *motor2 = new Motor();
	Motor *motor3 = new Motor();
	Motor *motor4 = new Motor();

	motor1->init(1);
	motor2->init(2);
	motor3->init(3);
	motor4->init(4);
	int i;
	for(i=0; i < 100; i++){
		printf("iteration: %d\n", i);
		motor1->setPower(i);
//		motor2->setPower(i);
//		motor3->setPower(i);
//		motor4->setPower(i);
		usleep(100000);
	}




//	sense->stopThread();
	sleep(40);
	return 0;
}
