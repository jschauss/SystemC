#include "alu.h"

void alu::alu_main()
{
	if(reset.read() == SC_LOGIC_0)
	{
		initialize();
	}else
	{
		alu_func(op_sel);
	}
}

void alu::initialize()
{
	acc.write(0);
	stat.write(0);
	accu = 0;
	d1 = 0;
	d2 = 0;
	d1_temp = 0;
}

void alu::alu_func(sc_uint<3> opcode)
{
	switch (opcode)
	{
	case AND:
		d1 = data1.read();
		d2 = data2.read();
		accu = d1 & d2;
		acc.write(accu);
		break;
	case OR:
		d1 = data1.read();
		d2 = data2.read();
		accu = d1 | d2;
		acc.write(accu);
		break;
	case XOR:
		d1 = data1.read();
		d2 = data2.read();
		accu = d1 ^ d2;
		acc.write(accu);
		break;
	case ROR:
		d1_temp = data1.read();
		d1_temp.rrotate(1);
		acc.write(d1_temp);
		break;
	case ROL:
		d1_temp = data1.read();
		d1_temp.lrotate(1);
		acc.write(d1_temp);
		break;
	case ADD:
		d1 = data1.read();
		d2 = data2.read();
		accu = d1 + d2;
		acc.write(accu);
		break;
	case MUL:
		d1 = data1.read();
		d2 = data2.read();
		accu = d1 * d2;
		acc.write(accu);
		break;
	case DIV:
		d1 = data1.read();
		d2 = data2.read();
		if (d2 != 0)
		{
			accu = d1 / d2;
			acc.write(accu);
		}else
			cout << "Illegal instruction: divided by zero!!" << endl;
		break;
	default:
		break;
	}
	set_stat(opcode);
}

void alu::set_stat(sc_uint<3> opsel)
{
	sc_bv<8> status;

	switch (opsel)
	{
	case AND:
		status[0] = set_z_flag();
		status[1] = SC_LOGIC_0;
		status[2] = Sign(accu);
		status[3] = SC_LOGIC_0;
		status[4] = SC_LOGIC_0;
		status[5] = SC_LOGIC_0;
		status[6] = SC_LOGIC_0;
		status[7] = SC_LOGIC_0;
		stat = status;
		break;
	case OR:
		status[0] = set_z_flag();
		status[1] = SC_LOGIC_0;
		status[2] = Sign(accu);
		status[3] = SC_LOGIC_0;
		status[4] = SC_LOGIC_0;
		status[5] = SC_LOGIC_0;
		status[6] = SC_LOGIC_0;
		status[7] = SC_LOGIC_0;
		stat = status;
		break;
	case XOR:
		status[0] = set_z_flag();
		status[1] = SC_LOGIC_0;
		status[2] = Sign(accu);;
		status[3] = SC_LOGIC_0;
		status[4] = SC_LOGIC_0;
		status[5] = SC_LOGIC_0;
		status[6] = SC_LOGIC_0;
		status[7] = SC_LOGIC_0;
		stat = status;
		break;
	case ROR:
		status[0] = set_z_flag();
		status[1] = SC_LOGIC_0;
		status[2] = Sign(accu);;
		status[3] = SC_LOGIC_0;
		status[4] = SC_LOGIC_0;
		status[5] = SC_LOGIC_0;
		status[6] = SC_LOGIC_0;
		status[7] = SC_LOGIC_0;
		stat = status;
		break;
	case ROL:
		status[0] = set_z_flag();
		status[1] = SC_LOGIC_0;
		status[2] = Sign(accu);;
		status[3] = SC_LOGIC_0;
		status[4] = SC_LOGIC_0;
		status[5] = SC_LOGIC_0;
		status[6] = SC_LOGIC_0;
		status[7] = SC_LOGIC_0;
		stat = status;
		break;
	case ADD:
		status[0] = set_z_flag();
		status[1] = set_c_flag();
		status[2] = Sign(accu);;
		status[3] = overflow(opsel);
		status[4] = underflow(opsel);
		status[5] = SC_LOGIC_0;
		status[6] = SC_LOGIC_0;
		status[7] = SC_LOGIC_0;
		stat = status;
		break;
	case MUL:
		status[0] = set_z_flag();
		status[1] = SC_LOGIC_0;
		status[2] = Sign(accu);
		status[3] = overflow(opsel);
		status[4] = underflow(opsel);
		status[5] = SC_LOGIC_0;
		status[6] = SC_LOGIC_0;
		status[7] = SC_LOGIC_0;
		stat = status;
		break;
	case DIV:
		status[0] = set_z_flag();
		status[1] = SC_LOGIC_0;
		status[2] = Sign(accu);
		status[3] = SC_LOGIC_0;
		status[4] = SC_LOGIC_0;
		status[5] = SC_LOGIC_0;
		status[6] = SC_LOGIC_0;
		status[7] = SC_LOGIC_0;
		stat = status;
		break;
	default:
		break;
	}

}

sc_logic alu::underflow(sc_uint<3> opsel)
{
	sc_logic ret = SC_LOGIC_0;

	switch (opsel) {
	case (ADD):
		if((Sign(d1) == NEG) & (Sign(d2) == NEG) & (Sign(accu) == POS))
		{
			ret = SC_LOGIC_1;
		}else
		{
			ret = SC_LOGIC_0;
		}
		break;
	case (MUL):
		if (((Sign(d1) == POS) & (Sign(d2) == NEG) & (Sign(accu) == POS))
				| ((Sign(d1) == NEG) & (Sign(d2) == POS) & (Sign(accu) == POS)))
		{
			ret = SC_LOGIC_1;
		}else
		{
			ret = SC_LOGIC_0;
		}
		break;
	default:
		break;

	}
	return ret;
}

sc_logic alu::overflow(sc_uint<3> opsel)
{
	sc_logic ret = SC_LOGIC_0;

	switch (opsel)
	{
	case (ADD):
		if((Sign(d1) == POS) & (Sign(d2) == POS) & (Sign(accu) == NEG))
		{
			ret = SC_LOGIC_1;
		}else
		{
			ret = SC_LOGIC_0;
		}
	case (MUL):
		if(((Sign(d1) == POS) & (Sign(d2) == POS) & (Sign(accu) == NEG))
				| ((Sign(d1) == NEG) & (Sign(d2) == NEG) & (Sign(accu) == NEG)))
		{
			ret = SC_LOGIC_1;
		}else
		{
			ret = SC_LOGIC_0;
		}
	default:
		break;

	}
	return ret;
}

sc_logic alu::set_z_flag(void)
{
	return ((accu == 0) ? SC_LOGIC_1 : SC_LOGIC_0);
}

sc_logic alu::set_c_flag()
{
	sc_logic ret = SC_LOGIC_0;

	if (((Sign(d1) == POS) & (Sign(d2) == POS) & (Sign(accu) == NEG))
			| ((Sign(d1) == NEG) & (Sign(d2) == NEG) & (Sign(accu) == POS)))
	{
		ret = SC_LOGIC_1;
	}

	return ret;
}

sc_logic alu::Sign(sc_int<32> var)
{
	return (((sc_bv<32>)var[31]).to_uint() ? NEG : POS);
}

