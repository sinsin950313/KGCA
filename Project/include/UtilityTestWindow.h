#pragma once

#include "TBasicWindow.h"
#include "TTimer.h"

class UtilityTestWindow : public TBasicWindow
{
private:
	TTimer _timer;

public:
	UtilityTestWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : TBasicWindow(name, hInstance, nCmdShow) { }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
