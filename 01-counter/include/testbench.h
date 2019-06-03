/*
 * testbench.h
 *
 *  Created on: May 17, 2018
 *      Author: j_schauss18
 */

#ifndef SRC_TESTBENCH_H_
#define SRC_TESTBENCH_H_

#include <systemc.h>

SC_MODULE(testbench){
	sc_in<bool> clock;
	sc_out<sc_logic> reset;
	sc_out<sc_logic> count_en;
	sc_out<sc_logic> ud_ctrl;
	sc_in<bool> ovf_intr;
	sc_in<bool> unf_intr;
	sc_in<sc_bv<17> > cnt_out;

	void counter_tb();
	void print_to_console();

	SC_CTOR(testbench) {
		SC_THREAD(counter_tb);
		sensitive << clock.pos();
	}
};



#endif /* SRC_TESTBENCH_H_ */
