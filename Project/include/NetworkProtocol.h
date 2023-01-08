#pragma once

namespace SSB
{
	struct Header
	{
		unsigned int Type;
		unsigned int Length;
	};

#define HeaderSize sizeof(Header);
}
