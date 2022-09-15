#pragma once

#include "TBasicWindow.h"
#include "TTimer.h"
#include "Sound.h"

class UtilityTestWindow : public TBasicWindow
{
private:
	TTimer _timer;
	Sound* _sound;
	Sound* _sound1;

public:
	UtilityTestWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : TBasicWindow(name, hInstance, nCmdShow) { }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
