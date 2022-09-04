#pragma once
#pragma comment (lib, "DirectXBasic.lib")

#include "TDXWindow.h"
#include "TCore.h"

class DXUtilityTestWindow : public TDXWindow
{
public:
	DXUtilityTestWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : TDXWindow(name, hInstance, nCmdShow) { }
	TText* _test;

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

protected:
	bool PreRender() override;
	bool MainRender() override;
	bool PostRender() override;
};
