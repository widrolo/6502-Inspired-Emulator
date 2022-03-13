#pragma once



Word MakeWord(Word& PC, Memory& mem)
{
	Byte buffer[2];
	for (int i = 0; i < 2; i++) {
		buffer[i] = mem.LoadByte(PC);
		PC--;
	}

	return CombineBytes(buffer[0], buffer[1]);
}

/// <summary>
///		{0 : Intermediate}  
///		{1 : Zero Page}  
///		{2 : Absolute}  
/// </summary>
void RegisterLoad(Byte& reg, Word& PC, Memory& mem, Byte(&statuses)[7], Byte type)
{
	switch (type)
	{
	case 0:
		reg = mem.LoadByte(PC);
		break;
	case 1:
		reg = mem.LoadByte(CombineBytes(0x00, mem.LoadByte(PC)));
		break;
	case 2:
		reg = mem.LoadByte(MakeWord(PC, mem));
		break;
	default:
		reg = 0x00;
		break;
	}
	if (type != 2)
		PC--;

	if (reg == 0x00)
		statuses[1] = 1;
}
