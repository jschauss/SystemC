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
	deriv_num(0) = p_target->controller_read(PID_CGR1 & 0xFF, 4) & 0x0FFF;
	deriv_den(0) = 1;

	prop_num(0) = p_target->controller_read(PID_CGR2 & 0xFF, 4) & 0x0FFF;
	prop_den(0) = 0;
	prop_den(1) = 1;

	integ_num(0) = 0;
	integ_num(1) = p_target->controller_read(PID_CGR3 & 0xFF, 4) & 0x0FFF;
	integ_den(0) = 1;

	k_active = true;
	i_active = true;
	d_active = true;
}

void pid_controller::processing()
{
	set_controller();

	double transfer_func = 0;

	if(k_active == 0 && i_active == 0 && d_active == 0)
	{
		transfer_func = iref - imeas;
	}
	else
	{
		if(k_active)
		{
			transfer_func += prop(deriv_num, deriv_den, iref - imeas);
		}
		if(i_active)
		{
			transfer_func += integ(prop_num, prop_den, iref - imeas);
		}
		if(d_active)
		{
			transfer_func += deriv(deriv_num, deriv_den, iref - imeas);
		}
	}

	c.write(transfer_func);

}

void pid_controller::set_controller()
{

	k_p = p_target->controller_read(PID_CGR1 & 0xFF, 4) & 0x0FFF;

	k_i = p_target->controller_read(PID_CGR2 & 0xFF, 4) & 0x0FFF;

	k_d = p_target->controller_read(PID_CGR3 & 0xFF, 4) & 0x0FFF;

	deriv_num(0) = k_p;
	prop_num(0) = k_i;
	integ_num(1) = k_d;

	uint32_t status_reg = p_target->controller_read(PID_CHSR & 0xFF, 4);

	if((status_reg & 0x01) == 1)
	{
		k_active = true;
	}
	else
	{
		k_active = false;
	}

	if( ( (status_reg >> 1) & 0x01) == 1)
	{
		i_active = true;
	}
	else
	{
		i_active = false;
	}

	if( ( (status_reg >> 2) & 0x01) == 1)
	{
		d_active = true;
	}
	else
	{
		d_active = false;
	}
}
