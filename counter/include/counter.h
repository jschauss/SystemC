/*
 * design.h
 *
 *  Created on: May 17, 2018
 *      Author: j_schauss18
 */

#ifndef SRC_COUNTER_H_
#define SRC_COUNTER_H_

#include <systemc.h>

SC_MODULE (counter) {
	sc_in<bool> clock;     			// Clock input of the design
	sc_in<sc_logic> reset;				// Active high, synchronous Reset input
	sc_in<sc_logic> count_en;    		// Active high enable signal for counter
	sc_in<sc_logic> ud_ctrl;			// Up-Down controller
	sc_out<bool> ovf_intr;			// Overflow interrupt
	sc_out<bool> unf_intr;			// Underflow interrupt
	sc_out<sc_bv<17> > cnt_out; 	// 17 bit vector output of the counter

	sc_uint<17> count;

	void do_count();

	SC_CTOR(counter) {
		SC_METHOD(do_count);
		sensitive << reset;
		sensitive << clock.pos();
	}

};

#endif /* SRC_COUNTER_H_ */
