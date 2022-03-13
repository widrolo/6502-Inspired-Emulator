#pragma once

using Byte = unsigned char;
using Word = unsigned short;
using sByte = signed char;
using sWord = signed short;

#define INT_MIN     (-2147483647 - 1)
#define INT_MAX       2147483647

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