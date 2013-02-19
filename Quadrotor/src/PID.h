/*
 * PID.h
 *
 *  Created on: Dec 20, 2012
 *      Author: cooperdl
 */

#ifndef PID_H_
#define PID_H_
#include <sys/time.h>

namespace std{
class PID {
private:
	double setPoint;
	double actualValue;
	double previousError;
	double integral;
	double output;
	double Kp;
	double Ki;
	double Kd;
	timeval timestart;


public:
	PID(double setPoint0, double actualValue0, double previousError0,
			double integral0, double output0, timeval timestart, double Kp, double Ki, double Kd);

	double UpdateOutput();

	void UpdateActualValue(double actualValue0);

	void UpdateSetPoint(double setPoint0);

	void ChangePID(double Kp, double Ki, double Kd);

	double getIntegral();

	virtual ~PID();
};

}/* namespace std */
#endif /* PID_H_ */
