#pragma once
#pragma comment (lib, "winmm.lib")

#include "CommonClass.h"

class TTimer : public Common
{
public:
	TTimer() { }

private:
	DWORD _startTime;
	DWORD _currentTime;

public:
	void Start() { _startTime = _currentTime = timeGetTime(); }
	DWORD GetElapseTime() { return _currentTime - _startTime; }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
