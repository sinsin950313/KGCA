#include "TTimer.h"

bool TTimer::Init()
{
	_startTime = _currentTime = timeGetTime();
	return true;
}

bool TTimer::Frame()
{
	_currentTime = timeGetTime();

	return true;
}

bool TTimer::Render()
{
	return true;
}

bool TTimer::Release()
{
	return true;
}
