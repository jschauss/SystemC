/*
 * main.cpp
 *
 *  Created on: Sep 9, 2018
 *      Author: j_schauss18
 */

#include <systemc.h>

#include "fifo.h"
#include "producer_consumer.h"

int sc_main(int argc, char* argv[])
{
	producer_consumer* producer_consumer0 = new producer_consumer("producer_consumer");

	sc_start(200, SC_NS);

	delete producer_consumer0;

	return 0;
}
