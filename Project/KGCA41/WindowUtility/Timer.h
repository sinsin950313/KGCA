#pragma once
#pragma comment (lib, "winmm.lib")

#include "Common.h"
#include <timeapi.h>

namespace SSB
{
	class Timer : public Common
	{
	public:
		Timer() { }

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
}
