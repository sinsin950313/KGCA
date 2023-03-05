#pragma once

#include <string>

namespace SSB
{
	class ObjectScriptIO
	{
	public:
		std::string Read(std::string fileName);
		void Write(std::string fileName, std::string str);
	};
}
