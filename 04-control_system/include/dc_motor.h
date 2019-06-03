#include <systemc>
#include <systemc-ams>

#include "parameter_values.h"

SCA_TDF_MODULE(dc_motor)
{
 	sca_tdf::sca_in<double> vrdv;
 	sca_tdf::sca_out<double> imeas;

  	void set_attributes();

  	void initialize();

  	void processing();

  	SCA_CTOR(dc_motor):
  		vrdv("vrdv"),
		imeas("imeas"),
		h_0(H_0),
		w_0(W_0),
		t_step(T_STEP)
  	{}

private:
  	// parameters of DC motor
  	double h_0;
  	double w_0;

	sca_tdf::sca_ltf_nd transfer_func;					// transfer function of dc motor

	// numerators and denumerators of transfer functions
	sca_util::sca_vector<double> transfer_func_num;
	sca_util::sca_vector<double> transfer_func_den;

	sca_core::sca_time t_step;							// time step Ts
};
