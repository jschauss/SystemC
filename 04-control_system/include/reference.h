/*
 * reference.h
 *
 *  Created on: Sep 9, 2018
 *      Author: j_schauss18
 */

#ifndef REFERENCE_H_
#define REFERENCE_H_

#include <systemc-ams>
#include <systemc>

#include "parameter_values.h"

// iref step function
SCA_TDF_MODULE(reference)
{
	sca_tdf::sca_out<double> iref; // output port

	void set_attributes()
	{
		set_timestep(T_STEP);
	}

	void processing()
	{
		if(get_time().to_seconds() > 0.001)
		{
			iref.write(1.0);
		}
		else
		{
			iref.write(0.0);
		}
	}

	SCA_CTOR(reference)
	{}
};



#endif /* REFERENCE_H_ */
