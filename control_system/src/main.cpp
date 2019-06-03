#include <systemc>
#include <systemc-ams>

#include "pid_controller.h"
#include "dc_motor.h"
#include "pwm_modulator.h"
#include "reference.h"

int sc_main(int argc, char* argv[])
{
 	sca_tdf::sca_signal<double> iref_sig;
 	sca_tdf::sca_signal<double> imeas_sig;
	sca_tdf::sca_signal<double> c_sig;
	sca_tdf::sca_signal<double> vrdv_sig;

	double k_d = 10.0;	// parameter K_d for PID controller

	reference* ref0;
 	ref0 = new reference("sin");
 	ref0->iref(iref_sig);

	pwm_modulator* pwm0;
	pwm0 = new pwm_modulator("PWM");
	pwm0->c(c_sig);
	pwm0->vrdv(vrdv_sig);

	pid_controller* pid0;
	pid0 = new pid_controller("PID", k_d);
	pid0->iref(iref_sig);
	pid0->imeas(imeas_sig);
	pid0->c(c_sig);

	dc_motor* dc_motor0;
	dc_motor0 = new dc_motor("dc_motor");
	dc_motor0->vrdv(vrdv_sig);
	dc_motor0->imeas(imeas_sig);

	sca_util::sca_trace_file* tf = sca_util::sca_create_vcd_trace_file("control_system");
	sca_trace(tf, iref_sig, "iref");
	sca_trace(tf, imeas_sig, "imeas");
	sca_trace(tf, c_sig, "c");
	sca_trace(tf, vrdv_sig, "vrdv");

	sc_start(60.0, sc_core::SC_MS);

	delete pwm0;
	sca_close_vcd_trace_file(tf);

	return 0;
}
