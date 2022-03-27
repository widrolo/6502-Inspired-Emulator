#pragma once

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

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
		PC++;
		return data[PC - 1];
	}

	void Clear()
	{
		for (u32 i = 0; i < memorySize; i++)
		{
			data[i] = 0;
		}
	}

};