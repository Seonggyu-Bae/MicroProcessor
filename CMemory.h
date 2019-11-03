#include <iostream>

#pragma once

using namespace std;      //ostream                     std::cout<<

class CMemory{
		public:
				CMemory() {}
				virtual ~CMemory() {}
};

class CSRAM_256w : public CMemory {
		public:
				CSRAM_256w() {}
				virtual ~CSRAM_256w() {}

				void write_on_memory(unsigned int index, int data) {m_mems[index] = data; }
				int read_from_memory(unsigned int index) 		   {return m_mems[index];}

				void show_mems(unsigned int start_addr, unsigned int end_addr);

		protected:
				int m_mems[256];

};
