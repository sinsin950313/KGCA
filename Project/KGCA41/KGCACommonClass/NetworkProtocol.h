#pragma once

namespace SSB
{
	typedef unsigned int ProtocolType;
	typedef char Byte;

	struct HeaderStructure
	{
		ProtocolType Type;
		unsigned int Length;
	};

#define HeaderSize sizeof(HeaderStructure);
}
