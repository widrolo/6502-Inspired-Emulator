//#include <iostream>
#include "CPU.h"


void InjectCode(Memory& mem)
{
	mem.SetByte(0xFFFC, INST_JMP);
	mem.SetByte(0xFFFD, 0xA2);
	mem.SetByte(0xFFFE, 0xC1);
	mem.SetByte(0xC1A2, INST_LDA_INTERM);
	mem.SetByte(0xC1A3, 65);
	mem.SetByte(0xC1A4, INST_STA_ZP);
	mem.SetByte(0xC1A5, 0x00);
	mem.SetByte(0xC1A6, INST_LDX_ZP);
	mem.SetByte(0xC1A7, 0x00);
	mem.SetByte(0xFFFC, INST_BNE);
	mem.SetByte(0xFFFD, 0xB2);
	mem.SetByte(0xFFFE, 0xC1);
}

void DumpCPU(CPU& cpu)
{
	std::cout << "\nCPU Dump:\n" << std::endl;
	std::cout << "Stack Pointer: " << cpu.SP << "\t  0x" << std::hex << cpu.SP << std::endl;
	std::cout << "Program Counter: " << std::dec << cpu.PC << "\t  0x" << std::hex << cpu.PC << std::endl;
	std::cout << "Register A: " << std::dec << cpu.RA << std::endl;
	std::cout << "Register X: " << std::dec << cpu.RX << std::endl;
	std::cout << "Register Y: " << std::dec << cpu.RY << std::endl;
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

	//Dumping CPU for analysis
	DumpCPU(cpu);
	return 0;
}