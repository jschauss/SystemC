/*
 * testbench.h
 *
 *  Created on: Jun 4, 2018
 *      Author: j_schauss18
 */

#ifndef SRC_TESTBENCH_H_
#define SRC_TESTBENCH_H_

#include <systemc.h>
#include "alu.h"

SC_MODULE(testbench){
	sc_in<bool> clk;
	sc_out<sc_logic> reset;
	sc_out<sc_uint<3> > op_sel;
	sc_out<sc_int<32> > data1;
	sc_out<sc_int<32> > data2;
	sc_in<sc_int<32> > acc;
	sc_in<sc_bv<8> > stat;

	void alu_test();
	void print_to_console(sc_uint<3> opcode);
	std::string to_String(sc_uint<3> opcode);

	sc_int<32> temp;
	bool type;

	SC_HAS_PROCESS(testbench);

	testbench(sc_module_name name_, bool type_) :
		sc_module(name_), type(type_)
	{
		SC_THREAD(alu_test);
	}
};



#endif /* SRC_TESTBENCH_H_ */
