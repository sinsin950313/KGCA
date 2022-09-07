#pragma once
#pragma comment (lib, "DirectXBasic.lib")

#include "TDXWindow.h"
#include "TDX2DObject.h"
#include "TText.h"

class GETestWindow : public TDXWindow
{
private:
	TText* _text;
	TDX2DObject* _object;

public:
	GETestWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : TDXWindow(name, hInstance, nCmdShow) { }

public:
	bool Init() override;
	bool Frame() override;
	bool Release() override;

protected:
	bool PreRender() override;
	bool MainRender() override;
	bool PostRender() override;
};
