#include "Timer.h"

namespace SSB
{
	bool Timer::Init()
	{
		Start();
		return true;
	}

	bool Timer::Frame()
	{
		_currentTime = timeGetTime();

		return true;
	}

	bool Timer::Render()
	{
		return true;
	}

	bool Timer::Release()
	{
		return true;
	}
}
