#include <systemc.h>
#include "counter.h"
#include "testbench.h"

SC_MODULE(SYSTEM) {
	testbench *testbench0;
	counter *counter0;
	sc_trace_file *tf = sc_create_vcd_trace_file("counter_wave");

	sc_signal<sc_logic> reset_sig;
	sc_signal<sc_logic> count_en_sig;
	sc_signal<sc_logic> ud_ctrl_sig;
	sc_signal<bool> ovf_intr_sig;
	sc_signal<bool> unf_intr_sig;
	sc_signal<sc_bv<17> > cnt_out_sig;

	sc_clock clock_sig;

	SC_CTOR(SYSTEM) :
			clock_sig("clk_sig", 10, SC_NS) {
		testbench0 = new testbench("tb0");
		testbench0->clock(clock_sig);
		testbench0->reset(reset_sig);
		testbench0->count_en(count_en_sig);
		testbench0->ud_ctrl(ud_ctrl_sig);
		testbench0->ovf_intr(ovf_intr_sig);
		testbench0->unf_intr(unf_intr_sig);
		testbench0->cnt_out(cnt_out_sig);

		counter0 = new counter("counter");
		counter0->clock(clock_sig);
		counter0->reset(reset_sig);
		counter0->count_en(count_en_sig);
		counter0->ud_ctrl(ud_ctrl_sig);
		counter0->ovf_intr(ovf_intr_sig);
		counter0->unf_intr(unf_intr_sig);
		counter0->cnt_out(cnt_out_sig);

		sc_trace(tf, clock_sig, "clock");
		sc_trace(tf, reset_sig, "reset");
		sc_trace(tf, count_en_sig, "count_en");
		sc_trace(tf, ud_ctrl_sig, "ud_ctrl");
		sc_trace(tf, ovf_intr_sig, "ovf_intr");
		sc_trace(tf, unf_intr_sig, "unf_intr");
		sc_trace(tf, cnt_out_sig, "cnt_out");
	}

	~SYSTEM() {
		delete testbench0;
		delete counter0;
		sc_close_vcd_trace_file(tf);
	}

};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]) {

	top = new SYSTEM("top");
	sc_start();
	return 0;
}
