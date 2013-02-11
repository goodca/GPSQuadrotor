/*
 * PID.cpp
 *
 *  Created on: Dec 20, 2012
 *      Author: cooperdl
 */
#include <stdio.h>
#include "PID.h"
#include <sys/time.h>

namespace std{
PID::PID(double setPoint0, double actualValue0, double previousError0,
		double integral0, double output0, timeval timestart0,double Kp, double Ki, double Kd) {

	this->setPoint = setPoint0;
	this->actualValue = actualValue0;
	this->previousError = previousError0;
	this->integral = integral0;
	this->output = output0;
	this->timestart = timestart0;
	this->Kp=Kp;
	this->Ki=Ki;
	this->Kd=Kd;

}

void PID::ChangePID(double Kp, double Ki, double Kd){
		this->Kp=Kp;
		this->Ki=Ki;
		this->Kd=Kd;
}

double PID::UpdateOutput() {

	double error = setPoint - actualValue; //sets error
	timeval end;
	gettimeofday(&end, NULL);
	double timechange = (1000000*end.tv_sec+end.tv_usec)-(1000000*timestart.tv_sec+timestart.tv_usec); //calculates the time interval
	timestart.tv_sec = end.tv_sec;
	timestart.tv_usec = end.tv_usec;//sets the start time for the next cycle to the end time of this cycle
	integral = integral + error * timechange; //calculates the integral amount
	if(Ki * integral>20){
		integral=20/Ki;
	}else if(Ki * integral<-20){
		integral=-20/Ki;
	}
	double derivitive = (error - previousError) / timechange; //calculates the derivative
	output = Kp * error + Ki * integral + Kd * derivitive; //adds up everything to create the output
	previousError = error; //sets the error for the next cycle
	return output;

}

void PID::UpdateActualValue(double actualValue0) {
	this->actualValue = actualValue0;//used for feed back

}

void PID::UpdateSetPoint(double setPoint0) {
	this->setPoint = setPoint0;//value you need to reach

}

PID::~PID() {



}
}
