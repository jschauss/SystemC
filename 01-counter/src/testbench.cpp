/*
 * testbench.cpp
 *
 *  Created on: May 17, 2018
 *      Author: j_schauss18
 */

#include "testbench.h"

void testbench::counter_tb() {
	uint it;

	reset.write(SC_LOGIC_1);
	count_en.write(SC_LOGIC_0);
	ud_ctrl.write(SC_LOGIC_0);
	print_to_console();

	wait(10, sc_core::SC_NS);

	reset.write(SC_LOGIC_0);
	count_en.write(SC_LOGIC_1);
	ud_ctrl.write(SC_LOGIC_1);

	for (it = 0; it < 10; it++) {
		print_to_console();
		wait();
	}

	count_en.write(SC_LOGIC_0);

	for (it = 0; it < 5; it++) {
		print_to_console();
		wait();
	}

	reset.write(SC_LOGIC_1);
	count_en.write(SC_LOGIC_1);

	wait();

	reset.write(SC_LOGIC_0);
	ud_ctrl.write(SC_LOGIC_0);

	for (it = 0; it < 5; it++) {
		print_to_console();
		wait();
	}

	ud_ctrl.write(SC_LOGIC_1);

	for (it = 0; it < 10; it++) {
		print_to_console();
		wait();
	}

	sc_stop();
}

void testbench::print_to_console() {
		cout << "@" << sc_time_stamp() << " :: Counter " << cnt_out.read();

		if (ovf_intr.read() == 1){
			cout << "\tOverflow Interrupt";
		}

		if (unf_intr.read() == 1){
			cout << "\tUnderflow Interrupt";
		}
		cout << endl;
}
