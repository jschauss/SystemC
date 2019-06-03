/*
 * dc_motor.cpp
 *
 *  Created on: Sep 3, 2018
 *      Author: j_schauss18
 */

#include "dc_motor.h"

void dc_motor::set_attributes()
{
	set_timestep(t_step);
	imeas.set_delay(1);
}

void dc_motor::initialize()
{
	transfer_func_num(0) = h_0;
	transfer_func_den(0) = 1.0;
	transfer_func_den(1) = 1 / w_0;
}

void dc_motor::processing()
{
	imeas.write(transfer_func(transfer_func_num, transfer_func_den, vrdv.read()));
}


