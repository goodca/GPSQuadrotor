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
#include "Sensors.h"

using namespace std;

int main() {
	cout << "Hello World" << endl; // prints
	Sensors *sense = new Sensors;
	sense->runTest();

	return 0;
}
