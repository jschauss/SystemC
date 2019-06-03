#ifndef SRC_COUNTER_H_
#define SRC_COUNTER_H_

#include <systemc.h>

enum operation {AND, OR, XOR, ROR, ROL, ADD, MUL, DIV};
const sc_logic NEG = SC_LOGIC_1;
const sc_logic POS = SC_LOGIC_0;

SC_MODULE (alu) {
	sc_in<bool> clk;
	sc_in<sc_logic> reset;
	sc_in<sc_uint<3> > op_sel;
	sc_in<sc_int<32> > data1;
	sc_in<sc_int<32> > data2;
	sc_out<sc_int<32> > acc;
	sc_out<sc_bv<8> > stat;

	sc_int<32> accu;
	sc_int<32> d1;
	sc_int<32> d2;
	sc_bv<32> d1_temp;

	void alu_main();
	void initialize();
	void alu_func(sc_uint<3> opcode);
	void set_stat(sc_uint<3> opsel);
	sc_logic underflow(sc_uint<3> opsel);
	sc_logic overflow(sc_uint<3> opsel);
	sc_logic set_z_flag(void);
	sc_logic set_c_flag();
	sc_logic Sign(sc_int<32> var);

	SC_CTOR(alu) {
		SC_METHOD(alu_main);
		sensitive << reset;
		sensitive << clk.pos();
	}

};

#endif /* SRC_COUNTER_H_ */
