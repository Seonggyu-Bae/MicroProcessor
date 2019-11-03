#include "CDecode.h"

bool CT1DecodeDirectFetch::do_fetch_from(int PC) {
	if(PC >= 0 && PC < m_code_memory.code_memory_size() ) {
		m_inst_buffer = m_code_memory.code_at(PC);
//        cout << "Fetching from code memory at " << PC << endl;
		return true;
	}
	else
		return false;
}

bool CT1DecodeDirectFetch::do_decode() {

	int decoded = 0;

	/// Decoding OPCODE
	if(m_inst_buffer[0] == '1')
		decoded |=8; //b 1000

	if(m_inst_buffer[1] == '1')
		decoded |=4; //b 0100

	if(m_inst_buffer[2] == '1')
		decoded |=2; //b 0010

	if(m_inst_buffer[3] == '1')
		decoded |=1; //b 0001

	m_instruction.OPCODE = decoded;

	decoded = 0;
	// Decoding OP1	
	if(m_inst_buffer[4] == '1')
		decoded |=8; //b 1000
	if(m_inst_buffer[5] == '1')
		decoded |=4; //b 0100
	if(m_inst_buffer[6] == '1')
		decoded |=2; //b 0010
	if(m_inst_buffer[7] == '1')
		decoded |=1; //b 0001

	m_instruction.OP1 = decoded;


	decoded = 0;
	//Decoding OP2

	if(m_inst_buffer[8] == '1')
		decoded |=128; //b 1000 0000
	if(m_inst_buffer[9] == '1')
		decoded |=64; //b 0100 0000
	if(m_inst_buffer[10] == '1')
		decoded |=32; //b 0010 0000
	if(m_inst_buffer[11] == '1')
		decoded |=16; //b 0001 0000
	if(m_inst_buffer[12] == '1')
		decoded |=8; //b 0000 1000
	if(m_inst_buffer[13] == '1')
		decoded |=4; //b 0000 0100
	if(m_inst_buffer[14] == '1')
		decoded |=2; //b 0000 0010
	if(m_inst_buffer[15] == '1')
		decoded |=1; //b 0000 0001

	m_instruction.OP2 = decoded;

	return true;
}

void
CT1DecodeDirectFetch::show_instruction(){
	if(m_instruction.OPCODE == MOV3) {
		cout << "MOV3 " << "R" << m_instruction.OP1 << ", #" << m_instruction.OP2 << endl;
	} else if(m_instruction.OPCODE == ADD) {
		unsigned int op2 = (m_instruction.OP2>> 4) & 0xF; 
		cout << "ADD " << "R" << m_instruction.OP1 << ", R" << op2 << endl;
	} else if(m_instruction.OPCODE == SUB) {
		unsigned int op2 = (m_instruction.OP2 >> 4) & 0xF; 
		cout << "SUB " << "R" << m_instruction.OP1 << ", R" << op2 << endl;
	} else if(m_instruction.OPCODE == MOV0){
		unsigned int op2 = m_instruction.OP2 & 0xFF; // only lower 8bit
		cout <<"MOV0 R" << m_instruction.OP1 << ", [" << op2 << "]" << endl;
	} else if(m_instruction.OPCODE == MOV1){
		unsigned int op2 = m_instruction.OP2 & 0xFF;
		cout << "MOV1 [" << op2 << "], R" << m_instruction.OP1 << endl;
	} else if(m_instruction.OPCODE == MUL){
		unsigned int op2 = (m_instruction.OP2 >> 4) & 0xF;
		cout << "MUL " << "R" << m_instruction.OP1 << ", R" << op2 << endl;
	} else if(m_instruction.OPCODE == JZ){
		cout << "JZ " << "R" << m_instruction.OP1 << ", " << m_instruction.OP2 << endl;
	} else if(m_instruction.OPCODE == MOV2){
		unsigned int op2 = (m_instruction.OP2) & 0xF;
		cout << "MOV2 " << "[R" << m_instruction.OP1 << "], R" << op2 << endl;
	} else if(m_instruction.OPCODE == MOV4){
		unsigned int op2 = (m_instruction.OP2 >> 4) & 0xF;
		cout << "MOV4 " << "R" << m_instruction.OP1 << ", R" << op2 << endl;
	} else if(m_instruction.OPCODE == MOV5){
		unsigned int op2 =(m_instruction.OP2) & 0xF;
		cout << "MOV5 " << "R" << m_instruction.OP1 << ",[R" << op2 <<"]" << endl;
	} else {
		cout << "Not supported instruction" << endl;
	}
	
}
