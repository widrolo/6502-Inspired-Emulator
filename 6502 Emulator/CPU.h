#pragma once

#include "Memory.h"
#include "Operations.h"
#include "CPU Operations.h"
#include "CPU Instructions.h"
#include <iostream>

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

	Byte statusArray[7];

	// Instructions


	void Run(Memory& mem, bool& running)
	{

		Byte loaded = mem.LoadInstruction(PC);
		std::cout << "loaded instruction: " << (int)loaded << std::endl;

		switch (loaded)
		{
			// Load Register Operations
		case INST_LDA_INTERM:
		{
			RegisterLoad(RA, PC, mem, statusArray, 0);
			UpdateStatuses();
		}break;
		case INST_LDX_INTERM:
		{
			RegisterLoad(RX, PC, mem, statusArray, 0);
			UpdateStatuses();
		}break;
		case INST_LDY_INTERM:
		{
			RegisterLoad(RY, PC, mem, statusArray, 0);
			UpdateStatuses();
		}break;
		case INST_LDA_ABS:
		{
			RegisterLoad(RA, PC, mem, statusArray, 2);
			UpdateStatuses();
		}break;
		case INST_LDX_ABS:
		{
			RegisterLoad(RX, PC, mem, statusArray, 2);
			UpdateStatuses();
		}break;
		case INST_LDY_ABS:
		{
			RegisterLoad(RY, PC, mem, statusArray, 2);
			UpdateStatuses();
		}break;
		case INST_LDA_ZP:
		{
			RegisterLoad(RA, PC, mem, statusArray, 1);
			UpdateStatuses();
		}break;
		case INST_LDX_ZP:
		{
			RegisterLoad(RX, PC, mem, statusArray, 1);
			UpdateStatuses();
		}break;
		case INST_LDY_ZP:
		{
			RegisterLoad(RY, PC, mem, statusArray, 1);
			UpdateStatuses();
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
			mem.SetByte(MakeWord(PC, mem), RA);
			PC--;
		}break;
		case INST_STX_ABS:
		{
			mem.SetByte(MakeWord(PC, mem), RX);
			PC--;
		}break;
		case INST_STY_ABS:
		{
			mem.SetByte(MakeWord(PC, mem), RY);
			PC--;
		}break;
		// Jumps
		case INST_JSR:
		{
			Word currentAddress = PC;
			Word newAddress = MakeWord(PC, mem);

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
			Word newAddress = MakeWord(PC, mem);

			PC = newAddress;
		}break;
		// Atrihmetic
		case INST_ADD:
		{
			Word location = MakeWord(PC, mem);

			RA = RA + mem.LoadByte(location);
			PC--;
		}break;
		case INST_SUB:
		{
			Word location = MakeWord(PC, mem);

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

		statusArray[0] = C;
		statusArray[1] = Z;
		statusArray[2] = I;
		statusArray[3] = D;
		statusArray[4] = B;
		statusArray[5] = O;
		statusArray[6] = N;

		// Clear memory
		mem.Clear();
	}

	void UpdateStatuses()
	{
		C = statusArray[0];
		Z = statusArray[1];
		I = statusArray[2];
		D = statusArray[3];
		B = statusArray[4];
		O = statusArray[5];
		N = statusArray[6];
	}
};