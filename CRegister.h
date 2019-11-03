#include <iostream>
#pragma once
using namespace std;

class CRegister {
public:
	CRegister(){}
	virtual ~CRegister(){}
};

class C16RegisterFile : public CRegister {
public:
	C16RegisterFile() : m_PC(0) {}
	virtual ~C16RegisterFile(){}

	void write_on_reg(unsigned int index, int data) {m_regs[index] = data;}
	int read_from_reg(unsigned int index)			{return m_regs[index];}
	
	int get_PC() { return m_PC; }
	void set_PC(int pc) { m_PC = pc;}

	void show_regs();

private:	
	int m_regs[16];
	int m_PC;
};
