#include "CExecute.h"

int clks[10] = {8, 8, 12, 6, 4, 4, 12, 30, 2, 12};

int
CT1ExecuteTinyUnit::do_execute() {

	//ex MOV3 R1, #2         	// enum 3
	if(m_decode_unit.get_opcode() == MOV3 ) {
			unsigned int reg_index = m_decode_unit.get_op1();
					 int      data = m_decode_unit.get_op2();

			//write into register
			m_regs.write_on_reg(reg_index, data);
			
			// PC++
			m_regs.set_PC(m_regs.get_PC()+1);

			return clks[MOV3];
		
	//ex ADD R1, R2		---> R1= R1+R2
	} else if( m_decode_unit.get_opcode() ==ADD ) {
		unsigned int reg_n = m_decode_unit.get_op1();
		unsigned int reg_m = (m_decode_unit.get_op2() >> 4) & 0xF;
		
		// read from register
		int Rn = m_regs.read_from_reg(reg_n);
		int Rm = m_regs.read_from_reg(reg_m);

		Rn = Rn + Rm;
		m_regs.write_on_reg(reg_n, Rn);

		m_regs.set_PC(m_regs.get_PC()+1);

		return clks[ADD];

		//ex. SUB R0, R1 ---> R0 = R0 - R1 
	} else if(m_decode_unit.get_opcode() == SUB){
		unsigned int reg_n = m_decode_unit.get_op1();
		unsigned int reg_m = (m_decode_unit.get_op2() >>4) & 0xF;

		// read from register
		int Rn = m_regs.read_from_reg(reg_n);
		int Rm = m_regs.read_from_reg(reg_m);
		
		Rn = Rn - Rm;
		m_regs.write_on_reg(reg_n, Rn);

		m_regs.set_PC(m_regs.get_PC()+1);

		return clks[SUB];

		//ex. MUL RO, R1 ---> R0= R0 * R1
	} else if(m_decode_unit.get_opcode() == MUL){
		unsigned int reg_n = m_decode_unit.get_op1();
		unsigned int reg_m = (m_decode_unit.get_op2() >>4) & 0xF;

		int Rn = m_regs.read_from_reg(reg_n);
		int Rm = m_regs.read_from_reg(reg_m);
		
		Rn = Rn * Rm;
		m_regs.write_on_reg(reg_n, Rn);

		m_regs.set_PC(m_regs.get_PC()+1);

		return clks[MUL];

		// ex. MOV0 R1, [3] : R1 <.. M[3]
	}else if(m_decode_unit.get_opcode() == MOV0 ){
		unsigned int reg_index = m_decode_unit.get_op1();
		unsigned int mem_addr = m_decode_unit.get_op2() & 0xFF;
		
		//read from mem
		int memory_data = m_mems.read_from_memory(mem_addr);
		m_regs.write_on_reg(reg_index, memory_data);

		m_regs.set_PC(m_regs.get_PC()+1);

		return clks[MOV0];
	// ex. 	MOV1 [2], R1
	}else if(m_decode_unit.get_opcode() == MOV1 ){
			unsigned int reg_index = m_decode_unit.get_op1();
			unsigned int mem_addr = m_decode_unit.get_op2() & 0xFF;
			
			//read from register
			int Rn = m_regs.read_from_reg(reg_index);

			//write on mem
			m_mems.write_on_memory(mem_addr, Rn);

			m_regs.set_PC(m_regs.get_PC()+1);

			return clks[MOV1];

	}else if(m_decode_unit.get_opcode() == JZ ){
			unsigned int reg_n = m_decode_unit.get_op1();
					 int offset = m_decode_unit.get_op2();
			
			int Rn = m_regs.read_from_reg(reg_n);
			m_regs.set_PC(m_regs.get_PC()+1);
			
			if( Rn == 0) {
				int pc = m_regs.get_PC();
				m_regs.set_PC(pc+offset);
			}

			return clks[JZ];

			               //Mem{Rn}  <---  Rm
	}else if(m_decode_unit.get_opcode() == MOV2 ){
			unsigned int reg_n = m_decode_unit.get_op1();
			unsigned int reg_m = m_decode_unit.get_op2() & 0xF;
			
			//read from register
			int Rn = m_regs.read_from_reg(reg_n);
			int Rm = m_regs.read_from_reg(reg_m);
			if( Rn>255 ){
				cout << "Mem[" << Rn <<"]" << "is not exist" << endl;
				m_regs.set_PC(m_regs.get_PC()+1);
				return clks[MOV2];
				exit(-1);
			}else{
				//write on mem  Mem{Rn} <----Rm
				m_mems.write_on_memory(Rn, Rm);
				m_regs.set_PC(m_regs.get_PC()+1);
				return clks[MOV2];
			}
	} else if(m_decode_unit.get_opcode() == MOV4){
		unsigned int reg_n = m_decode_unit.get_op1();
		unsigned int reg_m = (m_decode_unit.get_op2() >>4) & 0xF;

		int Rn = m_regs.read_from_reg(reg_n);
		int Rm = m_regs.read_from_reg(reg_m);
		
		Rn = Rm;
		m_regs.write_on_reg(reg_n, Rn);

		m_regs.set_PC(m_regs.get_PC()+1);

		return clks[MOV4];
	}else if(m_decode_unit.get_opcode() == MOV5 ){
			unsigned int reg_n = m_decode_unit.get_op1();
			unsigned int reg_m = m_decode_unit.get_op2() & 0xF;
			
			int Rm = m_regs.read_from_reg(reg_m);
			if( Rm > 255 ){
				cout << "Mem[" << Rm <<"]" << "is not exist" << endl;
				m_regs.set_PC(m_regs.get_PC()+1);
				exit(-1);
			}else{
				int memory_data = m_mems.read_from_memory(Rm);
				//write on reg  Rn <----Mem[Rm]
				m_regs.write_on_reg(reg_n, memory_data);
				m_regs.set_PC(m_regs.get_PC()+1);
				return clks[MOV5];
			}
	}else {
		cout << "Not executable instruction, not yet implemented sorry!" << endl;
		return false;
	}
}
