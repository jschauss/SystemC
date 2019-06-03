/*
 * tlm_target.h
 *
 *  Created on: Sep 10, 2018
 *      Author: j_schauss18
 */

#ifndef TLM_TARGET_H_
#define TLM_TARGET_H_

#include <fstream>
#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>

#include "register_map.h"
#include "logger.h"

SC_MODULE(Target)
{
private:
	static const int REG_SIZE = 0x54;

	uint8_t reg[REG_SIZE];

	logger* p_logger;

public:

	tlm_utils::simple_target_socket<Target> socket;

	SC_CTOR(Target):
		socket("target_socket")
	{
		socket.register_b_transport(this, &Target::b_transport);

		start_configuration();
	}

	void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay)
	{
		tlm::tlm_command 	cmd 		= trans.get_command();
		sc_dt::uint64 		addr		= trans.get_address();
		unsigned char* 		data_ptr	= trans.get_data_ptr();
		unsigned int 		length		= trans.get_data_length();
		unsigned char* 		byte_en_ptr	= trans.get_byte_enable_ptr();
		unsigned int 		width		= trans.get_streaming_width();

		if(addr < PID_BASE_ADDRESS || addr > PID_CGR3)
		{
			SC_REPORT_ERROR("TLM-2", "Address out of range");
			trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
		}
		else if(length > 4 || length == 0)
		{
			SC_REPORT_ERROR("TLM-2", "Invalid payload length");
		}
		else
		{
			if(cmd == tlm::TLM_READ_COMMAND)
			{
				SC_REPORT_INFO("TLM-2", "Read command received");

				uint8_t addr_offset = addr & 0xFF;

				switch(addr)
				{
				case PID_CHSR:
					memcpy(data_ptr, &reg[addr_offset], length);
					SC_REPORT_INFO("TLM-2", "Target send PID_CHSR");
					trans.set_response_status(tlm::TLM_OK_RESPONSE);
					break;

				case PID_CGR1:
					memcpy(data_ptr, &reg[addr_offset], length);
					SC_REPORT_INFO("TLM-2", "Target send PID_CGR1");
					trans.set_response_status(tlm::TLM_OK_RESPONSE);
					break;

				case PID_CGR2:
					memcpy(data_ptr, &reg[addr_offset], length);
					SC_REPORT_INFO("TLM-2", "Target send PID_CGR2");
					trans.set_response_status(tlm::TLM_OK_RESPONSE);
					break;

				case PID_CGR3:
					memcpy(data_ptr, &reg[addr_offset], length);
					SC_REPORT_INFO("TLM-2", "Target send PID_CGR3");
					trans.set_response_status(tlm::TLM_OK_RESPONSE);
					break;

				default:
					SC_REPORT_ERROR("TLM-2", "Cannot read write-only register");
					trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
					break;
				}
			}
			else if(cmd == tlm::TLM_WRITE_COMMAND)
			{
				SC_REPORT_INFO("TLM-2", "Write command received");

				uint8_t addr_offset = addr & 0xFF;

				switch(addr)
				{
				case PID_CR:
					memcpy(&reg[addr_offset], data_ptr, length);
					SC_REPORT_INFO("TLM-2", "PID_CR write completed");
					trans.set_response_status(tlm::TLM_OK_RESPONSE);
					break;

				case PID_CHER:
					memcpy(&reg[addr_offset], data_ptr, length);
					SC_REPORT_INFO("TLM-2", "PID_CHER write completed");
					trans.set_response_status(tlm::TLM_OK_RESPONSE);
					break;

				case PID_CHDR:
					memcpy(&reg[addr_offset], data_ptr, length);
					SC_REPORT_INFO("TLM-2", "PID_CHDR write completed");
					trans.set_response_status(tlm::TLM_OK_RESPONSE);
					break;

				case PID_CGR1:
					memcpy(&reg[addr_offset], data_ptr, length);
					SC_REPORT_INFO("TLM-2", "PID_CHGR1 write completed");
					trans.set_response_status(tlm::TLM_OK_RESPONSE);
					break;

				case PID_CGR2:
					memcpy(&reg[addr_offset], data_ptr, length);
					SC_REPORT_INFO("TLM-2", "PID_CGR2 write completed");
					trans.set_response_status(tlm::TLM_OK_RESPONSE);
					break;

				case PID_CGR3:
					memcpy(&reg[addr_offset], data_ptr, length);
					SC_REPORT_INFO("TLM-2", "PID_CGR3 write completed");
					trans.set_response_status(tlm::TLM_OK_RESPONSE);
					break;

				default:
					SC_REPORT_ERROR("TLM-2", "Cannot write read-only register");
					trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
					break;
				}

				set_status_register();

				if((reg[0] & 0x01) == 1)
				{
					software_reset();
				}
				else if( ( (reg[0] >> 1) & 0x01) == 1 )
				{
					start_configuration();
				}

				print_memory();
			}

			switch(cmd)
			{

			case tlm::TLM_READ_COMMAND:
				delay += sc_time(5, SC_US);
				break;
			case tlm::TLM_WRITE_COMMAND:
				delay += sc_time(5, SC_US);
				break;
			case tlm::TLM_IGNORE_COMMAND:
				delay += SC_ZERO_TIME;
				break;
			}
		}
	}

	void print_memory()
	{
		std::stringstream ss;

		ss << "Register map updated @ " << sc_time_stamp() << ": \n";

	    ss << " +----+----+----+----+ \n" ;
	    for (int i = REG_SIZE - 1; i > (PID_CGR1 & 0xFF);)
	    {
	        for (int j = 0; j < 4; j++)
	        {
	        	ss << " | " << std::setw(2) << std::setfill('0') << std::hex << std::uppercase ;
	            ss << (uint32_t)(reg[i--]);
	        }
	        ss << " | 0x" << std::setw(8) << std::setfill('0') << std::hex << std::uppercase ;
	        ss << ((uint32_t)(i+1) | PID_BASE_ADDRESS) << "\n" ;
	        ss << " +----+----+----+----+ \n";
	    }

	    ss << " :    :    :    :    : \n";

	    ss << " +----+----+----+----+ \n";
	    for (int i = (PID_CHSR & 0xFF) + 3; i > (PID_CHDR & 0xFF);)
	    {
	        for (int j = 0; j < 4; j++)
	        {
	        	ss << " | " << std::setw(2) << std::setfill('0') << std::hex << std::uppercase ;
	            ss << (uint32_t)(reg[i--]);
	        }
	        ss << " | 0x" << std::setw(8) << std::setfill('0') << std::hex << std::uppercase ;
	        ss << ((uint32_t)(i+1) | PID_BASE_ADDRESS) << "\n" ;
	        ss << " +----+----+----+----+ \n";
	    }

	    ss << " :    :    :    :    : \n";

	    ss << " +----+----+----+----+ \n";
	    for (int i = (PID_CHER & 0xFF) + 3; i > 0;)
	    {
	        for (int j = 0; j < 4; j++)
	        {
	        	ss << " | " << std::setw(2) << std::setfill('0') << std::hex << std::uppercase ;
	            ss << (uint32_t)(reg[i--]);
	        }
	        ss << " | 0x" << std::setw(8) << std::setfill('0') << std::hex << std::uppercase ;
	        ss << ((uint32_t)(i+1) | PID_BASE_ADDRESS) << "\n";
	        ss << " +----+----+----+----+ \n";
	    }

	    ss << "\n\n";

	    p_logger->log_to_file(ss);
	}

	void set_status_register()
	{
		uint32_t status_reg = 0;
		uint32_t enable_reg;
		uint32_t disale_reg;

		memcpy(reinterpret_cast<uint8_t*> (&enable_reg), &reg[PID_CHER & 0xFF], 4);
		memcpy(reinterpret_cast<uint8_t*> (&disale_reg), &reg[PID_CHDR & 0xFF], 4);

		if((enable_reg & 0x01) == 1 && (disale_reg & 0x01) == 0)
		{
			status_reg += 1;
		}

		if( ( (enable_reg >> 1) & 0x01) == 1 &&
				( (disale_reg >> 1) & 0x01) == 0)
		{
			status_reg += 2;
		}

		if( ( (enable_reg >> 2) & 0x01) == 1 &&
				( (disale_reg >> 2) & 0x01) == 0)
		{
			status_reg += 4;
		}

		memcpy(&reg[PID_CHSR & 0xFF], reinterpret_cast<uint8_t*>(&status_reg), 4);
	}

	void start_configuration()
	{
		uint8_t control_reg = 0x00;
		memcpy(&reg[PID_CR & 0xFF], &control_reg, 1);

		uint32_t status_reg = 0x00000007;
		memcpy(&reg[PID_CHSR & 0xFF], reinterpret_cast<uint8_t*> (&status_reg), 4);

		uint32_t enable_reg = 0x00000007;
		memcpy(&reg[PID_CHER & 0xFF], reinterpret_cast<uint8_t*> (&enable_reg), 4);

		uint32_t disale_reg = 0x00000000;
		memcpy(&reg[PID_CHDR & 0xFF], reinterpret_cast<uint8_t*> (&disale_reg), 4);

		uint32_t gain1_reg 	= 0x00000000;
		memcpy(&reg[PID_CGR1 & 0xFF], reinterpret_cast<uint8_t*> (&gain1_reg), 4);

		uint32_t gain2_reg 	= 0x0000000C;
		memcpy(&reg[PID_CGR2 & 0xFF], reinterpret_cast<uint8_t*> (&gain2_reg), 4);

		uint32_t gain3_reg 	= 0x00000001;
		memcpy(&reg[PID_CGR3 & 0xFF], reinterpret_cast<uint8_t*> (&gain3_reg), 4);
	}

	void software_reset()
	{
		uint32_t gain1_reg 	= 0x00000000;
		memcpy(&reg[PID_CGR1 & 0xFF], reinterpret_cast<uint8_t*> (&gain1_reg), 4);

		uint32_t gain2_reg 	= 0x00000000;
		memcpy(&reg[PID_CGR2 & 0xFF], reinterpret_cast<uint8_t*> (&gain2_reg), 4);

		uint32_t gain3_reg 	= 0x00000000;
		memcpy(&reg[PID_CGR3 & 0xFF], reinterpret_cast<uint8_t*> (&gain3_reg), 4);
	}

	uint32_t controller_read(uint32_t address, uint32_t length)
	{
		uint32_t data;

		memcpy(reinterpret_cast<uint8_t*>(&data), &reg[address], length);

		return data;
	}

	void set_logger(logger& log)
	{
		p_logger = &log;
	}
};



#endif /* TLM_TARGET_H_ */
