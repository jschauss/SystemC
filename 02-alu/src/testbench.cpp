/*
 * testbench.cpp
 *
 *  Created on: May 17, 2018
 *      Author: j_schauss18
 */

#include "testbench.h"

void testbench::alu_test() {

	cout << endl << "*********************************************************" << endl << endl;


	// Reset
	reset.write(SC_LOGIC_0);

	wait(9.9, sc_core::SC_NS);

	reset.write(SC_LOGIC_1);

	// logic operations
	if(type == 0)
	{
		// AND underflow
		data1.write(357905130); //b'‭00010101010101010011001011101010‬
		data2.write(632085685); //b'‭00100101101011001101110010110101‬
		op_sel.write(AND);
		print_to_console(AND);

		wait(10, sc_core::SC_NS);

		// OR underflow
		data1.write(357905130);	//b'‭00010101010101010011001011101010
		data2.write(632085685);	//b'‭00100101101011001101110010110101
		op_sel.write(OR);
		print_to_console(OR);

		wait(10, sc_core::SC_NS);

		// XOR underflow
		data1.write(357905130);	//b'‭00010101010101010011001011101010
		data2.write(632085685);	//b'‭00100101101011001101110010110101
		op_sel.write(XOR);
		print_to_console(XOR);

		wait(10, sc_core::SC_NS);

		// ROR
		data1.write(357905130);
		temp = 357905130;
		op_sel.write(ROR);
		print_to_console(ROR);

		wait(10, sc_core::SC_NS);

		// ROL
		data1.write(357905130);
		temp = 357905130;
		op_sel.write(ROL);
		print_to_console(ROL);

		wait(10, sc_core::SC_NS);
	}
	// arithmetic operations
	else
	{
		// ADD normal
		op_sel.write(ADD);
		data1.write(1000);
		data2.write(500);
		print_to_console(ADD);

		wait(10, sc_core::SC_NS);

		// ADD Zero
		op_sel.write(ADD);
		data1.write(2);
		data2.write(-2);
		print_to_console(ADD);

		wait(10, sc_core::SC_NS);

		// ADD with overflow
		op_sel.write(ADD);
		data1.write(2000000000);
		data2.write(2000000000);
		print_to_console(ADD);

		wait(10, sc_core::SC_NS);

		// ADD with underflow
		op_sel.write(ADD);
		data1.write(-2000000000);
		data2.write(-2000000000);
		print_to_console(ADD);

		wait(10, sc_core::SC_NS);

		// MUL normal
		data1.write(2);
		data2.write(3);
		op_sel.write(MUL);
		print_to_console(MUL);

		wait(10, sc_core::SC_NS);

		// MUL overflow
		data1.write(1000000);
		data2.write(1000000);
		op_sel.write(MUL);
		print_to_console(MUL);

		wait(10, sc_core::SC_NS);

		// MUL underflow
		data1.write(1000000);
		data2.write(-1000000);
		op_sel.write(MUL);
		print_to_console(MUL);

		wait(10, sc_core::SC_NS);

		// DIV
		data1.write(512);
		data2.write(4);
		op_sel.write(DIV);
		print_to_console(DIV);

		wait(10, sc_core::SC_NS);
	}

	wait(10, sc_core::SC_NS);

	sc_stop();
}

void testbench::print_to_console(sc_uint<3> opcode){
	if (opcode == ADD | opcode == MUL | opcode == DIV)
		cout<<sc_time_stamp()<<"\t:"<<to_String(opcode)<<"("<<data1.read()<<","<<data2.read()<<")="<<acc.read()<<" ,STAT[X,X,X,UF,OF,S,C,Z] = "<<stat<<endl;
	else if(opcode == AND| opcode == OR | opcode == XOR)
		cout<<sc_time_stamp()<<"\t:"<<to_String(opcode)<<"("<<(sc_bv<32>)data1.read()<<","<<(sc_bv<32>)data2.read()<<")="<<(sc_bv<32>)acc.read()<<" ,STAT[X,X,X,UF,OF,S,C,Z] = "<<stat<<endl;
	else
		cout<<sc_time_stamp()<<"\t:"<<to_String(opcode)<<"("<<(sc_bv<32>)temp<<")"<<(sc_bv<32>)acc.read()<<" ,STAT[X,X,X,UF,OF,S,C,Z] = "<<stat<<endl;
}

std::string testbench::to_String(sc_uint<3> opcode){
	std::string ret;

	switch(opcode)
	{
	case AND:
		ret = "AND";
		break;
	case OR:
		ret = "OR";
		break;
	case XOR:
		ret = "XOR";
		break;
	case ROR:
		ret = "ROR";
		break;
	case ROL:
		ret = "ROL";
		break;
	case ADD:
		ret = "ADD";
		break;
	case MUL:
		ret = "MUL";
		break;
	case DIV:
		ret = "DIV";
		break;
	default:
		break;
	}

	return ret;
}

