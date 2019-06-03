/*
 * producer_consumer.h
 *
 *  Created on: Sep 9, 2018
 *      Author: j_schauss18
 */

#include <systemc.h>

#include "fifo.h"

SC_MODULE(producer_consumer)
{
	fifo<sc_int<8> > myFifo;

	void producer_thread();	// producer writes value of fifo

	void consumer_thread();	// consumer reads value of fifo

	void trace();

	sc_int<8> value_in;		// fifo in value
	sc_int<8> value_out;	// fifo out value

	bool blocking;		// blocking / non-blocking fifo
	sc_event finished;	// simulation finished

	SC_CTOR(producer_consumer)
	{
		SC_THREAD(producer_thread);
		SC_THREAD(consumer_thread);

		blocking = 0;
	}
};
