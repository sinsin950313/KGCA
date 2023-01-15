#include "CommonSocket.h"
#include <iostream>

namespace SSB
{
	void ConsoleDefaultAction::operator()()
	{
		std::cout << "Action Called" << std::endl;
	}
}
