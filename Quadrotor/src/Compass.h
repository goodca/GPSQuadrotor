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

namespace std {

class Compass {
public:
	Compass();
	virtual ~Compass();
	void init();
	void update();
	double getX();
	double getY();
	double getZ();
	double tiltComponsation(double phi, double theta);
	void * compassRun(void *p);
private:

	int compassFile;
	i2c *compassInterface;
	int16_t x;
	int16_t y;
	int16_t z;
	double unWrap(double angle);

};
#define MAG_DECLINATION 0; //in radians
#define pi 3.14159
#define ADXL_ADDR	0x1e
#define I2C_PORT	3
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
