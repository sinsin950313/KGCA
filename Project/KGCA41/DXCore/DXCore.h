#pragma once

#include "TDXWindow.h"

class TTimer;

class DXCore : public TDXWindow
{
private:
	TTimer* _timer;

public:
	DXCore(LPCWSTR name, HINSTANCE hInstance, int nCmdShow);

public:
	DWORD GetGlobalTime();

public:
	bool Init() override;
	bool Frame() override;
	bool Release() override;

protected:
	bool PreRender() override;
	bool MainRender() override;
	bool PostRender() override;
};
