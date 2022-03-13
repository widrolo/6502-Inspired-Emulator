//#include <iostream>
#include "CPU.h"


void InjectCode(Memory& mem)
{
	mem.SetByte(0x0001, 0x0A);
	mem.SetByte(0xB100, 0x00);

	mem.SetByte(0xFFFC, INST_LDA_ZP);
	mem.SetByte(0xFFFB, 0x01);
	mem.SetByte(0xFFFA, INST_LDX_ABS);
	mem.SetByte(0xFFF9, 0xB1);
	mem.SetByte(0xFFF8, 0x00);
	mem.SetByte(0xFFF7, INST_LDY_INTERM);
	mem.SetByte(0xFFF6, 0x07);
}

int main()
{
	bool running = true;
	CPU cpu;
	Memory mem;
	cpu.Reset(mem);
	InjectCode(mem);
	// Execute Instructions
	while (running)
		cpu.Run(mem, running);
	return 0;
}