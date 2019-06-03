/*
 * pwm.cpp
 *
 *  Created on: Aug 31, 2018
 *      Author: j_schauss18
 */
#include "pwm_modulator.h"


void pwm_modulator::set_attributes()
{
	set_timestep(t_step);
}

void pwm_modulator::processing()
{
	double t = get_time().to_seconds(); // current time
	double t_pos = std::fmod(t, t_period); // time position inside pulse period

	// calculate and clamp duty time
	if(t_pos < t_ramp)
	{
		t_duty = c.read() * t_duty_max;

		if(t_duty < 0.0)
		{
			t_duty = 0.0;
		}
		if(t_duty > t_duty_max)
		{
			t_duty = t_duty_max;
		}
	}
	double val = v0; // initial value

	if(t_pos < t_ramp) // rising edge
	{
		val = ( (v1 - v0) / t_ramp ) * t_pos + v0;
	}
	else if(t_pos < t_ramp + t_duty) // plateau
	{
		val = v1;
	}
	else if(t_pos < t_ramp + t_duty + t_ramp) // falling edge
	{
		val = ( (v0 - v1) / t_ramp ) * ( t_pos - t_ramp - t_duty ) + v1;
	}
	// else return to initial value

	vrdv.write(val);
}

