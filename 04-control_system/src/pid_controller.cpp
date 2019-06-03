/*
 * PID.cpp
 *
 *  Created on: Jul 9, 2018
 *      Author: j_schauss18
 */

#include "pid_controller.h"

void pid_controller::set_attributes()
{
	set_timestep(t_step);
}

// initialize PID parameters
void pid_controller::initialize()
{
	deriv_num(0) = k_p;
	deriv_den(0) = 1;

	prop_num(0) = k_i;
	prop_den(0) = 0;
	prop_den(1) = 1;

	integ_num(0) = 0;
	integ_num(1) = k_d;
	integ_den(0) = 1;
}

void pid_controller::processing()
{
	c.write( prop(deriv_num, deriv_den, iref - imeas)
			+ integ(prop_num, prop_den, iref - imeas)
			+ deriv(deriv_num, deriv_den, iref - imeas) );
}


