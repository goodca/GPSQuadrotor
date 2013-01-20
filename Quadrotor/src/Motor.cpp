/*
 * Motor.cpp
 *
 *  Created on: Dec 16, 2012
 *      Author: cooperdl
 */

#include "Motor.h"

Motor::Motor() {

}
void Motor::init(int motorNumber){
	motorNum = motorNumber;
		if (motorNumber == 1) {
			//GPIO2_6 mode3 lcd_data0 = ehrpwm.2:0
			set_mux_value("lcd_data0", 3);
			motorName = "ehrpwm.2:0";


		} else if (motorNumber == 2) {
			//GPIO2_7 mode3 lcd_data1 = ehrpwm.2:1
			set_mux_value("lcd_data1", 3);
			motorName = "ehrpwm.2:1";

		} else if (motorNumber == 3) {
			//EHRPWM1A mode6 gpmc_a2 = ehrpwm.1:0
			set_mux_value("gpmc_a2", 6);
			motorName = "ehrpwm.1:0";

		} else if (motorNumber == 4) {
			//EHRPWM1B mode6 gpmc_a3 = ehrpwm.1.1
			set_mux_value("gpmc_a3", 6);
			motorName = "ehrpwm.1.1";

		} else {
			printf("Motor number must be an integer 1, 2, 3, or 4");
			return;
		}
	//	sprintf(filename, "/dev/i2c-%d", i2cbus);
	//	open(filename, O_RDWR);
}

void Motor::setPower(double newPower) {
	power = newPower;
	if(power > 100){
		power = 100;
	}else if(power < 0){
		power = 0;
	}
	double duty;
	duty = (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE) * power + MIN_DUTY_CYCLE;
	set_pwm(duty);
}

int Motor::set_pwm(double duty_percent) {
	FILE *fp;
	char path[MAX_BUF];

	snprintf(path, sizeof path, "/sys/class/pwm/%s/run", motorName);

	if ((fp = fopen(path, "w")) == NULL) {
		printf("Cannot open pwm run file, %s\n", path);
		return 1;
	}

	rewind(fp);
	fprintf(fp, "1\n");
	fflush(fp);
	fclose(fp);

	snprintf(path, sizeof path, "/sys/class/pwm/%s/duty_ns", motorName);

	if ((fp = fopen(path, "w")) == NULL) {
		printf("Cannot open pwm duty_ns file, %s\n", path);
	}

	rewind(fp);
	fprintf(fp, "0\n");
	fflush(fp);
	fclose(fp);

	snprintf(path, sizeof path, "/sys/class/pwm/%s/period_freq", motorName);

	if ((fp = fopen(path, "w")) == NULL) {
		printf("Cannot open pwm period_freq file, %s\n", path);
	}

	rewind(fp);
	fprintf(fp, "%d\n", FREQUENCY);
	fflush(fp);
	fclose(fp);

	snprintf(path, sizeof path, "/sys/class/pwm/%s/duty_percent", motorName);

	if ((fp = fopen(path, "w")) == NULL) {
		printf("Cannot open duty_percent file, %s\n", path);
	}

	rewind(fp);
	fprintf(fp, "%f\n", duty_percent);
	fflush(fp);
	fclose(fp);
	return 0;
}

int Motor::set_mux_value(char* mux, int value) {
	FILE *fp;
	char path[MAX_BUF];

	snprintf(path, sizeof path, "/sys/kernel/debug/omap_mux/%s", mux);

	if ((fp = fopen(path, "w")) == NULL) {
		printf("Cannot open specified mux, %s\n", mux);
		return 1;
	}

	rewind(fp);
	fprintf(fp, "%d\n", value);
	fflush(fp);
	fclose(fp);
	return 0;

}

//void Motor::changePWM(){
//	return;
//}

Motor::~Motor() {
	set_pwm(0);
}
