/*
 * Compass.h
 *
 *  Created on: Dec 26, 2012
 *      Author: chris
 */

#ifndef COMPASS_H_
#define COMPASS_H_

#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "i2c.h"
#include <math.h>
#include <pthread.h>

namespace std {

class Compass {
public:
	Compass();
	virtual ~Compass();


	double getX();
	double getY();
	double getZ();
	double tiltComponsation(double phi, double theta);
	void * compassRun(void *p);
	void startCompassThread();
	double getThreadRunning();
	void stopThread();
private:
	pthread_t compassThread_t;
	int threadRunning;

	int compassFile;
	i2c *compassInterface;
	int16_t x;
	int16_t y;
	int16_t z;
	double unWrap(double angle);
	void init();
	void update();
	void compassThread(void *obj);
	static void * start_thread(void *obj) {
		//All we do here is call the do_work() function
		reinterpret_cast<Compass *>(obj)->compassThread(obj);
		return 0;
	}


};
#define MAG_DECLINATION 0; //in radians
#define pi 3.14159
#define COMP_ADDR	0x1e
#define COMP_I2C_PORT	3
#define CONFIG_REG_A 0
#define CONFIG_REG_B 1
#define MODE_REG	2
#define X_MSB	3
#define X_LSB	4
#define Z_MSB	5
#define Z_LSB	6
#define Y_MSB	7
#define Y_LSB	8
#define STATUS_REG	9
#define	IDEN_REG_A	10
#define IDEN_REG_B	11
#define	IDEN_REG_C	12

} /* namespace std */
#endif /* COMPASS_H_ */
