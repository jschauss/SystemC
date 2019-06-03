/*
 * producer_consumer.cpp
 *
 *  Created on: Sep 9, 2018
 *      Author: j_schauss18
 */

#include "producer_consumer.h"

void producer_consumer::producer_thread()
{
	std::cout << std::endl << "START OF NON-BLOCKING READ/WRITE" << std::endl;

	// non-blocking write of random numbers
	for (std::size_t i(0); i < 20; i++)
	{
		value_in = std::rand() % 100;

		std::cout << "[" << sc_time_stamp() << "] writing to FIFO value: " << value_in << ", number of data in FIFO: "
				<< myFifo.get_ndata() << std::endl;

		if(myFifo.write_nb(value_in))
		{
			std::cout << "[" << sc_time_stamp() << "] wrote to FIFO value: " << value_in << std::endl;
		}

		wait(1, SC_NS);
	}

	// resets the fifo

	myFifo.reset();

	std::cout << std::endl << "FIFO RESET" <<  std::endl;

	blocking = 1;

	std::cout << std::endl << "START OF BLOCKING READ/WRITE" << std::endl;

	// blocking write of random numbers
	for (std::size_t i(0); i < 20; i++)
	{
		value_in = std::rand() % 100;

		std::cout << "[" << sc_time_stamp() << "] writing to FIFO value: " << value_in << ", number of data in FIFO: "
				<< myFifo.get_ndata() << std::endl;

		myFifo.write_b(value_in);

		std::cout << "[" << sc_time_stamp() << "] wrote to FIFO value: " << value_in << std::endl;

		wait(1, SC_NS);
	}

	wait(finished);
}

void producer_consumer::consumer_thread()
{
	// non-blocking read
	while(blocking == 0)
	{
		wait(4, SC_NS);

		if(myFifo.read_nb(value_out))
		{
			std::cout << "[" << sc_time_stamp() << "] read from FIFO value: " << value_out << std::endl;
		}
	}

	// blocking read
	while(myFifo.get_ndata() != 0)
	{
		wait(4, SC_NS);

		myFifo.read_b(value_out);

		std::cout << "[" << sc_time_stamp() << "] read from FIFO value: " << value_out << std::endl;
	}

	finished.notify();
}

