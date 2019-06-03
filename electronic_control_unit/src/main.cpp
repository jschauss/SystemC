#include <systemc>
#include <systemc-ams>
#include <fstream>

#include "pid_controller.h"
#include "dc_motor.h"
#include "pwm_modulator.h"
#include "tlm_initiator.h"
#include "tlm_target.h"
#include "register_map.h"
#include "reference.h"
#include "logger.h"


int sc_main(int argc, char* argv[])
{
 	sca_tdf::sca_signal<double> iref_sig;
 	sca_tdf::sca_signal<double> imeas_sig;
	sca_tdf::sca_signal<double> c_sig;
	sca_tdf::sca_signal<double> vrdv_sig;

	logger log;

	Initiator* initiator0 = new Initiator("initiator", log);

	Target* target0 = new Target("target");
	target0->set_logger(log);

	initiator0->socket.bind(target0->socket);

	reference* ref0 = new reference("iref");
 	ref0->iref(iref_sig);

	pwm_modulator* pwm0 = new pwm_modulator("PWM");
	pwm0->c(c_sig);
	pwm0->vrdv(vrdv_sig);

	dc_motor* dc_motor0 = new dc_motor("dc_motor");
	dc_motor0->vrdv(vrdv_sig);
	dc_motor0->imeas(imeas_sig);

	pid_controller* pid0 = new pid_controller("PID", *target0);
	pid0->iref(iref_sig);
	pid0->imeas(imeas_sig);
	pid0->c(c_sig);

	sca_util::sca_trace_file* tf_vcd = sca_util::sca_create_vcd_trace_file("vcd_control_system");
	sca_trace(tf_vcd, iref_sig, "iref");
	sca_trace(tf_vcd, imeas_sig, "imeas");
	sca_trace(tf_vcd, c_sig, "c");
	sca_trace(tf_vcd, vrdv_sig, "vrdv");

	sca_util::sca_trace_file* tf_tabular = sca_util::sca_create_tabular_trace_file("tabular_control_system");
	sca_trace(tf_tabular, iref_sig, "iref");
	sca_trace(tf_tabular, imeas_sig, "imeas");
	sca_trace(tf_tabular, c_sig, "c");
	sca_trace(tf_tabular, vrdv_sig, "vrdv");

	sc_start(200.0, sc_core::SC_MS);

	delete pwm0;
	delete pid0;
	delete initiator0;
	delete target0;
	delete dc_motor0;
	delete ref0;

	sca_close_vcd_trace_file(tf_vcd);
	sca_close_vcd_trace_file(tf_tabular);

	return 0;
}


