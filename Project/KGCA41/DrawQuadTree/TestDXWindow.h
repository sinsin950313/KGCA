#pragma once
#include "TDXWindow.h"
#include "Core.h"

class TestDXWindow : public TDXWindow
{
private:
	Core _core;

public:
	TestDXWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : TDXWindow(L"Test", hInstance, nCmdShow) { }

public:
	bool Init() override;
	bool Frame() override;
	bool MainRender() override;
	bool Release() override;
};

