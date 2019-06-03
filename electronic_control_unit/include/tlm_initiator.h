/*
 * tlm_initiator.h
 *
 *  Created on: Sep 4, 2018
 *      Author: j_schauss18
 */

#ifndef TLM_INITIATOR_H_
#define TLM_INITIATOR_H_

#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>

#include "register_map.h"
#include "logger.h"
#include "test_values.h"

SC_MODULE(Initiator)
{

private:

	tlm::tlm_generic_payload* trans;

	logger* p_log;

public:

	tlm_utils::simple_initiator_socket<Initiator> socket;

	SC_HAS_PROCESS(Initiator);

	Initiator(sc_module_name name, logger& log_)
	{
		p_log = &log_;
		trans = new tlm::tlm_generic_payload;

		SC_THREAD(program_main)
	}

	void communication
	(
		tlm::tlm_command cmd,
		uint32_t addr,
		unsigned int& data,
		unsigned int length
	)
	{
		sc_core::sc_time delay = sc_core::SC_ZERO_TIME;

		trans->set_command(cmd);
		trans->set_address(addr);
		trans->set_data_ptr(reinterpret_cast<uint8_t *> (&data));
		trans->set_data_length(length);
		trans->set_streaming_width(length);	// no streaming
		trans->set_byte_enable_ptr(0);
		trans->set_dmi_allowed(false);
		trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

		socket->b_transport(*trans, delay);

		wait(delay);

		if(trans->is_response_error())
		{
			SC_REPORT_ERROR("TLM-2", "Response Error");
			std::cout << trans->get_response_string() << std::endl;
		}
	}

	// Software functions

	void pid_configuration(unsigned int addr, unsigned int value)
	{
		unsigned int length;

		if(addr == PID_CR)
		{
			length = 1;
		}
		else
		{
			length = 4;
		}

		communication(tlm::TLM_WRITE_COMMAND, addr, value, length);
	}

	unsigned int pid_get_status(unsigned int addr)
	{
		unsigned int value;
		communication(tlm::TLM_READ_COMMAND, addr, value, 4);

		return value;
	}

	unsigned int pid_get_coefficients(unsigned int addr)
	{
		unsigned int value;
		communication(tlm::TLM_READ_COMMAND, addr, value, 4);

		value = value & 0x0FFF;

		return value;
	}

	void program_main()
	{
		std::stringstream logger;

		// PID Configuration

		logger << "Write 0x" << std::hex << std::setw(8)
			<< std::setfill('0') << std::uppercase << CHER << " -> @PID_CHER \n";
		p_log->log_to_file(logger);
		logger.str("");
		pid_configuration(PID_CHER, CHER);

		logger << "Write 0x" << std::hex << std::setw(8)
			<< std::setfill('0') << std::uppercase << CHDR << " -> @PID_CHDR \n";
		p_log->log_to_file(logger);
		logger.str("");
		pid_configuration(PID_CHDR, CHDR);

		logger << "Write 0x" << std::hex << std::setw(8)
			<< std::setfill('0') << std::uppercase << CGR1 << " -> @PID_CGR1 \n";
		p_log->log_to_file(logger);
		logger.str("");
		pid_configuration(PID_CGR1, CGR1);

		logger << "Write 0x" << std::hex << std::setw(8)
			<< std::setfill('0') << std::uppercase << CGR2 << " -> @PID_CGR2 \n";
		p_log->log_to_file(logger);
		logger.str("");
		pid_configuration(PID_CGR2, CGR2);

		logger << "Write 0x" << std::hex << std::setw(8)
			<< std::setfill('0') << std::uppercase << CGR3 << " -> @PID_CGR3 \n";
		p_log->log_to_file(logger);
		logger.str("");
		pid_configuration(PID_CGR3, CGR3);

		logger << "Write 0x" << std::hex << std::setw(8)
			<< std::setfill('0') << std::uppercase << CR << " -> @PID_CR \n";
		p_log->log_to_file(logger);
		logger.str("");
		pid_configuration(PID_CR, CR);

		wait(10, SC_MS);

		// Get current PID status configuration

		unsigned int status = pid_get_status(PID_CHSR);

		logger << "Read PID_CHSR @" << sc_time_stamp()<< "-> 0x" << std::hex << std::setw(8)
			<< std::setfill('0') << std::uppercase
			<< status << "\n";

		p_log->log_to_file(logger);
		logger.str("");

		// Get content of gain registers

		unsigned int k_p = pid_get_coefficients(PID_CGR1);

		logger << "Read PID_CGR1 @" << sc_time_stamp() << "-> 0x" << std::hex << std::setw(8)
			<< std::setfill('0') << std::uppercase
			<< k_p << "\n";

		unsigned int k_i = pid_get_coefficients(PID_CGR2);

		logger << "Read PID_CGR2 @" << sc_time_stamp()<< "-> 0x" << std::hex << std::setw(8)
			<< std::setfill('0') << std::uppercase
			<< k_i << "\n";

		unsigned int k_d = pid_get_coefficients(PID_CGR3);

		logger << "Read PID_CGR3 @" << sc_time_stamp()<< "-> 0x" << std::hex << std::setw(8)
			<< std::setfill('0') << std::uppercase
			<< pid_get_coefficients(PID_CGR3) << "\n";

		logger << "\n\n";

		// Additional Logging Informations

		if(status == 0)
		{
			logger << "Controller is not enabled" << "\n";
		}
		else
		{
			logger << "Controller is a ";
		}
		if((status & 0x01) == 1)
		{
			logger << "P";
		}

		if( ( (status >> 1) & 0x01) == 1)
		{
			logger << "I";
		}

		if( ( (status >> 2) & 0x01) == 1)
		{
			logger << "D";
		}

		logger << " controller with:" << std::dec << "\n";

		if((status & 0x01) == 1)
		{
			logger << "   k_p = " << k_p << "\n";
		}

		if( ( (status >> 1) & 0x01) == 1)
		{
			logger << "   k_i = " << k_i << "\n";
		}

		if( ( (status >> 2) & 0x01) == 1)
		{
			logger << "   k_d = " << k_d << std::endl << std::endl;
		}

		p_log->log_to_file(logger);
	}
};

#endif /* TLM_INITIATOR_H_ */
