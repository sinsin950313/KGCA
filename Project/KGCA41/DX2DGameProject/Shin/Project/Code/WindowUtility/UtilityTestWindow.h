#pragma once

#include "BasicWindow.h"
#include "Timer.h"
#include "Sound.h"

namespace SSB
{
	class UtilityTestWindow : public BasicWindow
	{
	private:
		Timer _timer;
		Sound* _sound;

	public:
		UtilityTestWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : BasicWindow(name, hInstance, nCmdShow) { }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
