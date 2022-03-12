//#include <iostream>

#define INT_MIN     (-2147483647 - 1)
#define INT_MAX       2147483647

using Byte = unsigned char;
using Word = unsigned short;
using sByte = signed char;
using sWord = signed short;

bool running = true;

using u32 = unsigned int;

Word CombineBytes(Byte highByte, Byte lowByte)
{
	return (highByte << 8) | lowByte;
}

int UnsignedToSigned(Byte x)
{
	if (x <= INT_MAX)
		return static_cast<sByte>(x);

	if (x >= INT_MIN)
		return static_cast<sByte>(x - INT_MIN) + INT_MIN;
}

struct Memory
{
	static constexpr u32 memorySize = 1024 * 64;
	Byte data[memorySize];

	void SetByte(Word address, Byte value)
	{
		data[address] = value;
	}

	Byte LoadByte(Word address)
	{
		return data[address];
	}

	Byte LoadInstruction(Word& PC)
	{
		PC--;
		return data[PC + 1];
	}

	void Clear()
	{
		for (u32 i = 0; i < memorySize; i++) 
		{
			data[i] = 0;
		}
	}
	
};

struct CPU
{
	Word PC; // Program Counter
	Byte SP; // Stack Pointer

	Byte RA, RX, RY; // Registers

	// CPU Status
	Byte C : 1; // Carry Flag
	Byte Z : 1; // Zero Flag
	Byte I : 1; // Interrupt Disable
	Byte D : 1; // Decimal Mode
	Byte B : 1; // Break Command
	Byte O : 1; // Overflow Flag
	Byte N : 1; // Negative Flag

	// Instructions
	static constexpr Byte INST_LDA_INTERM = 0xA9; // Load A Intermediate
	static constexpr Byte INST_LDX_INTERM = 0xA2; // Load X Intermediate
	static constexpr Byte INST_LDY_INTERM = 0xA0; // Load Y Intermediate
	static constexpr Byte INST_LDA_ABS = 0xAD; // Load A Intermediate
	static constexpr Byte INST_LDX_ABS = 0xAE; // Load X Intermediate
	static constexpr Byte INST_LDY_ABS = 0xAC; // Load Y Intermediate
	static constexpr Byte INST_LDA_ZP = 0xA5; // Load A from Zero Page
	static constexpr Byte INST_LDX_ZP = 0xA6; // Load X from Zero Page
	static constexpr Byte INST_LDY_ZP = 0xA4; // Load Y from Zero Page
	static constexpr Byte INST_STA_ABS = 0x8D; // Store A Absolute
	static constexpr Byte INST_STX_ABS = 0x8E; // Store X Absolute
	static constexpr Byte INST_STY_ABS = 0x8C; // Store Y Absolute
	static constexpr Byte INST_STA_ZP = 0x85; // Store A into Zero Page
	static constexpr Byte INST_STX_ZP = 0x86; // Store X into Zero Page
	static constexpr Byte INST_STY_ZP = 0x84; // Store Y into Zero Page
	static constexpr Byte INST_JSR = 0x20; // Jump To Subroutine
	static constexpr Byte INST_RTS = 0x60; // Return from Subroutine
	static constexpr Byte INST_JMP = 0x4C; // Jump
	static constexpr Byte INST_ADD = 0x69; // Adds the Accumulator and a memory location
	static constexpr Byte INST_SUB = 0xE9; // Subtracts a memory location from the Accumulator
	static constexpr Byte INST_BEQ = 0xF0; // Branches if zero flag is set
	static constexpr Byte INST_BNE = 0xD0; // Branches if zero flag is clear

	void Run(Memory& mem)
	{
		Byte loaded = mem.LoadInstruction(PC);

		switch (loaded)
		{
		// Load Register Operations
		case INST_LDA_INTERM:
		{
			RA = mem.LoadByte(PC);
			PC--;

			if (RA == 0x00)
				Z = 1;

		}break;
		case INST_LDX_INTERM:
		{
			RX = mem.LoadByte(PC);
			PC--;

			if (RX == 0x00)
				Z = 1;
		}break;
		case INST_LDY_INTERM:
		{
			RY = mem.LoadByte(PC);
			PC--;

			if (RY == 0x00)
				Z = 1;
		}break;
		case INST_LDA_ABS:
		{
			Byte buffer[2];
			for (int i = 0; i < 2; i++) {
				buffer[i] = mem.LoadByte(PC);
				PC--;
			}
			RA = mem.LoadByte(CombineBytes(buffer[0], buffer[1]));
			PC--;

			if (RA == 0x00)
				Z = 1;

		}break;
		case INST_LDX_ABS:
		{
			Byte buffer[2];
			for (int i = 0; i < 2; i++) {
				buffer[i] = mem.LoadByte(PC);
				PC--;
			}
			RX = mem.LoadByte(CombineBytes(buffer[0], buffer[1]));
			PC--;

			if (RX == 0x00)
				Z = 1;
		}break;
		case INST_LDY_ABS:
		{
			Byte buffer[2];
			for (int i = 0; i < 2; i++) {
				buffer[i] = mem.LoadByte(PC);
				PC--;
			}
			RY = mem.LoadByte(CombineBytes(buffer[0], buffer[1]));
			PC--;

			if (RY == 0x00)
				Z = 1;
		}break;
		case INST_LDA_ZP:
		{
			RA = mem.LoadByte(CombineBytes(0x00, mem.LoadByte(PC)));
			PC--;

			if (RA == 0x00)
				Z = 1;

		}break;
		case INST_LDX_ZP:
		{
			RX = mem.LoadByte(CombineBytes(0x00, mem.LoadByte(PC)));
			PC--;

			if (RX == 0x00)
				Z = 1;
		}break;
		case INST_LDY_ZP:
		{
			RY = mem.LoadByte(CombineBytes(0x00, mem.LoadByte(PC)));
			PC--;

			if (RY == 0x00)
				Z = 1;
		}break;
		//Store Ragister Operations
		case INST_STA_ZP:
		{
			mem.SetByte(CombineBytes(0x00, mem.LoadByte(PC)), RA);
			PC--;
		}break;
		case INST_STX_ZP:
		{
			mem.SetByte(CombineBytes(0x00, mem.LoadByte(PC)), RX);
			PC--;
		}break;
		case INST_STY_ZP:
		{
			mem.SetByte(CombineBytes(0x00, mem.LoadByte(PC)), RY);
			PC--;
		}break;
		case INST_STA_ABS:
		{
			Byte buffer[2];
			for (int i = 0; i < 2; i++) {
				buffer[i] = mem.LoadByte(PC);
				PC--;
			}
			mem.SetByte(CombineBytes(buffer[0], buffer[1]), RA);
			PC--;
		}break;
		case INST_STX_ABS:
		{
			Byte buffer[2];
			for (int i = 0; i < 2; i++) {
				buffer[i] = mem.LoadByte(PC);
				PC--;
			}
			mem.SetByte(CombineBytes(buffer[0], buffer[1]), RX);
			PC--;
		}break;
		case INST_STY_ABS:
		{
			Byte buffer[2];
			for (int i = 0; i < 2; i++) {
				buffer[i] = mem.LoadByte(PC);
				PC--;
			}
			mem.SetByte(CombineBytes(buffer[0], buffer[1]), RY);
			PC--;
		}break;
		// Jumps
		case INST_JSR:
		{	
			Byte buffer[2];
			for (int i = 0; i < 2; i++) {
				buffer[i] = mem.LoadByte(PC);
				PC--;
			}
			Word currentAddress = PC;
			Word newAddress = CombineBytes(buffer[0], buffer[1]);

			Byte high = currentAddress >> 8;
			Byte low = (currentAddress << 8) >> 8;

			mem.SetByte(CombineBytes(0x01, SP), high);
			SP--;
			mem.SetByte(CombineBytes(0x01, SP), low);
			SP--;
			PC = newAddress;
		}break;
		case INST_RTS:
		{
			Byte buffer[2];
			for (int i = 0; i < 2; i++) {
				SP++;
				buffer[i] = mem.LoadByte(CombineBytes(0x01, SP));
			}
			
			Word newAddress = CombineBytes(buffer[1], buffer[0]);

			PC = newAddress;

		}break;
		case INST_JMP:
		{
			Byte buffer[2];
			for (int i = 0; i < 2; i++) {
				buffer[i] = mem.LoadByte(PC);
				PC--;
			}
			Word newAddress = CombineBytes(buffer[0], buffer[1]);

			PC = newAddress;
		}break;
		// Atrihmetic
		case INST_ADD:
		{
			Byte buffer[2];
			for (int i = 0; i < 2; i++) {
				buffer[i] = mem.LoadByte(PC);
				PC--;
			}
			Word location = CombineBytes(buffer[0], buffer[1]);

			RA = RA + mem.LoadByte(location);
			PC--;
		}break;
		case INST_SUB:
		{
			Byte buffer[2];
			for (int i = 0; i < 2; i++) {
				buffer[i] = mem.LoadByte(PC);
				PC--;
			}
			Word location = CombineBytes(buffer[0], buffer[1]);

			RA = RA - mem.LoadByte(location);
			PC--;
		}break;
		//Braches
		case INST_BEQ:
		{
			sByte newOffset = mem.LoadByte(PC);
			PC--;
			if (Z == 1)
				PC += newOffset;
		}break;
		case INST_BNE:
		{
			sByte newOffset = mem.LoadByte(PC);
			PC--;
			if (Z == 0)
				PC += newOffset;
		}break;

		default:
			running = false;
			break;
		}
	}

	void Reset(Memory& mem)
	{
		PC = 0xFFFC;
		SP = 0x01FF;

		RA = 0;
		RX = 0;
		RY = 0;

		C = 0;
		Z = 0;
		I = 0;
		D = 0;
		B = 0;
		O = 0;
		N = 0;

		// Clear memory
		mem.Clear();
	}
};

void InjectCode(Memory& mem)
{
	mem.SetByte(0xFFFC, CPU::INST_LDA_INTERM);
	mem.SetByte(0xFFFB, 0);
	mem.SetByte(0xFFFA, CPU::INST_BNE);
	mem.SetByte(0xFFF9, 0b10000011);
}

int main()
{
	CPU cpu;
	Memory mem;
	cpu.Reset(mem);
	InjectCode(mem);
	// Execute Instructions
	while (running)
		cpu.Run(mem);
	return 0;
}