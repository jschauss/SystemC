/*
 * pwm.h
 *
 *  Created on: Aug 31, 2018
 *      Author: j_schauss18
 */

#ifndef SRC_PWM_H_
#define SRC_PWM_H_

#include <cmath>
#include <systemc-ams>

#include "parameter_values.h"

SCA_TDF_MODULE(pwm_modulator)
{
 	sca_tdf::sca_in<double> c;
 	sca_tdf::sca_out<double> vrdv;

  	void set_attributes();

  	void processing();

  	SCA_CTOR(pwm_modulator):
  		c("c"),
		vrdv("vrdv"),
  		v0(0.0),
  		v1(1.0),
  		t_period(T_PERIOD.to_seconds()),
  		t_ramp(T_RAMP.to_seconds()),
  		t_duty_max(t_period - 2.0 * t_ramp),
  		t_duty(t_duty_max),
  		t_step(T_STEP)
  	{}

private:
 	double v0, v1; // initial and plateau values
 	double t_period, t_ramp; // pulse period and ramp time
 	double t_duty_max; // maximum duty time
 	double t_duty; // current duty time
 	sca_core::sca_time t_step; // module time step
};



#endif /* SRC_PWM_H_ */
