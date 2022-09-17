#pragma once
#pragma comment (lib, "DirectXBasic.lib")

#include "DXWindow.h"
#include "DX2DObject.h"
#include "Text.h"

namespace SSB
{
	class GETestWindow : public DXWindow
	{
	private:
		Text* _text;
		DX2DObject* _background;
		DX2DObject* _object;

	public:
		GETestWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXWindow(name, hInstance, nCmdShow) { }

	public:
		bool Init() override;
		bool Frame() override;
		bool Release() override;

	protected:
		bool PreRender() override;
		bool MainRender() override;
		bool PostRender() override;
	};
}
