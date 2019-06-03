#include <systemc.h>
#include "alu.h"
#include "testbench.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<sc_logic> reset_sig;
	sc_signal<sc_uint<3> > op_sel_sig;
	sc_signal<sc_int<32> > data1_sig;
	sc_signal<sc_int<32> > data2_sig;
	sc_signal<sc_int<32> > acc_sig;
	sc_signal<sc_bv<8> > stat_sig;

	sc_clock clk_sig("clk", 10, sc_core::SC_NS);

	alu *alu0;
	alu0 = new alu("alu");
	alu0->clk(clk_sig);
	alu0->reset(reset_sig);
	alu0->op_sel(op_sel_sig);
	alu0->data1(data1_sig);
	alu0->data2(data2_sig);
	alu0->acc(acc_sig);
	alu0->stat(stat_sig);

	testbench *testbench0;
	testbench0 = new testbench("tb0", 0);
	testbench0->clk(clk_sig);
	testbench0->reset(reset_sig);
	testbench0->op_sel(op_sel_sig);
	testbench0->data1(data1_sig);
	testbench0->data2(data2_sig);
	testbench0->acc(acc_sig);
	testbench0->stat(stat_sig);

	sc_trace_file *tf0 = sc_create_vcd_trace_file("alu_wave");
	sc_trace(tf0, clk_sig, "clk");
	sc_trace(tf0, reset_sig, "reset");
	sc_trace(tf0, op_sel_sig, "op_sel");
	sc_trace(tf0, data1_sig, "data1");
	sc_trace(tf0, data2_sig, "data2");
	sc_trace(tf0, acc_sig, "acc");
	sc_trace(tf0, stat_sig, "stat");

	sc_start();

	sc_close_vcd_trace_file(tf0);
	delete testbench0;
	delete alu0;

	return 0;
}
