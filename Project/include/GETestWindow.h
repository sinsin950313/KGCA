#pragma once
#pragma comment (lib, "DirectXBasic.lib")

#include "DXWindow.h"
#include "DX2DObject.h"
#include "Text.h"
#include "UI.h"

namespace SSB
{
	class GETestWindow : public DXWindow
	{
	private:
		Text* _text;
		DX2DObject* _background;
		DX2DObject* _object;
		DX2DObject* _spriteObject;
		DX2DObject* _objectWithFile;
		DX2DObject* _spriteObjectWithFile;
		DX2DObject* _animationObject;
		Button* _button;
		TextUI* _textUI;
		DX2DObject* _dialog;

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
