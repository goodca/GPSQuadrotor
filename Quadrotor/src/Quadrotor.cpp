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

#include "quadthread.h"
#include "Control.h"
#include <pthread.h>
#include "Motor.h"
#include "Remotehandler.h"

using namespace std;

pthread_t cppThread;

int main() {
	//cout << "Hello World" << endl; // prints
	Sensors *sense = new Sensors;
	Control *controller = new Control();
	puts("In main"); /* prints Broked */
//	sense->startSensorsThreads();
//
//	Motor *motor1 = new Motor();
//	Motor *motor2 = new Motor();
//	Motor *motor3 = new Motor();
//	Motor *motor4 = new Motor();
//
//	motor1->init(1);
//	motor2->init(2);
//	motor3->init(3);
//	motor4->init(4);
//	sleep(5);
//	int i;
//	for (i = 0; i < 30; i++) {
//		printf("iteration: %d\n", i);
//		motor1->setPower(i);
//		//motor2->setPower(i);
//		//motor3->setPower(i);
//		//motor4->setPower(i);
//		usleep(50000);
//	}
//	motor1->setPower(0);
//	for (i = 0; i < 30; i++) {
//		printf("iteration: %d\n", i);
//		motor2->setPower(i);
//		usleep(50000);
//	}
//	motor2->setPower(0);
//	for (i = 0; i < 30; i++) {
//		printf("iteration: %d\n", i);
//		motor3->setPower(i);
//		usleep(50000);
//	}
//	motor3->setPower(0);
//	for (i = 0; i < 30; i++) {
//		printf("iteration: %d\n", i);
//		motor4->setPower(i);
//		usleep(50000);
//	}
//	motor4->setPower(0);
//	motor1->setPower(0);
//	motor2->setPower(0);
//	motor3->setPower(0);
//	motor4->setPower(0);

//	sense->stopThread();

//	Remotehandler *remote = new Remotehandler();
	sense->startSensorsThreads();
	usleep(500000);
	controller->controlRun(sense);

//	while (1) {
////		printf("1: %f 2: %f 3: %f 4: %f\n", remote->getch1(),
////				remote->getch2(), remote->getch3(), remote->getch4());
//		printf("angle x: %f y: %f z: %f\nanglespeed x: %f y: %f z: %f\n",
//				sense->getXAngle(), sense->getYAngle(), sense->getZAngle(),
//				sense->getXAngleSpeed(), sense->getYAngleSpeed(),
//				sense->getZAngleSpeed());
//		usleep(500000);
//	}

	sleep(40);
	return 0;
}
