/*
 * PID.h
 *
 *  Created on: Jul 9, 2018
 *      Author: j_schauss18
 */

#ifndef SRC_PID_H_
#define SRC_PID_H_

#include <systemc-ams>
#include <systemc>

#include "parameter_values.h"

SCA_TDF_MODULE(pid_controller)
{
	sca_tdf::sca_in<double> iref;
	sca_tdf::sca_in<double> imeas;
	sca_tdf::sca_out<double> c;

	void initialize();

	void set_attributes();

	void processing();

	pid_controller(sc_core::sc_module_name nm, double k_d_):
		iref("iref"),
		imeas("imeas"),
		k_p(K_P),
		k_i(K_I),
		k_d(k_d_),
		t_step(T_STEP)
	{}

private:
	// parameters of PID controller
	double k_p;
	double k_i;
	double k_d;

	sca_tdf::sca_ltf_nd prop;					// transfer function of P
	sca_tdf::sca_ltf_nd integ;					// transfer function of I
	sca_tdf::sca_ltf_nd deriv;					// transfer function of D

	// numerators and denumerators of transfer functions
	sca_util::sca_vector<double> prop_num;
	sca_util::sca_vector<double> integ_num;
	sca_util::sca_vector<double> deriv_num;
	sca_util::sca_vector<double> prop_den;
	sca_util::sca_vector<double> integ_den;
	sca_util::sca_vector<double> deriv_den;

	sca_core::sca_time t_step;					// time step Ts
};



#endif /* SRC_PID_H_ */
