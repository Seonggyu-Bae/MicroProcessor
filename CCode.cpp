#include "CCode.h"
#include <iostream>
#include <fstream>

using namespace std;

CFlash1KWord::CFlash1KWord(char* filename, int line) {
	
	m_filename = filename;
	m_line = line;
	ifstream infile;
	infile.open(filename, ios::in);

	int addr=0;
	char bit;
	while (addr < line) {
		for(int i=0; i<16; i++) {
			infile >> bit;
			m_code[addr] = m_code[addr] + bit;
		}
		addr++;
	}
	infile.close();
}
CFlash1KWord::~CFlash1KWord() {}

string& CFlash1KWord::code_at(int addr){
	return m_code[addr];
}
