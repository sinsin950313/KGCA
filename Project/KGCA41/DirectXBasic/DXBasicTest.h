#pragma once
#include "DXWindow.h"
#include "DXObject.h"

namespace SSB
{
	class DXBasicTest : public DXWindow
	{
	private:
		DXObject* _object;
		DebugCamera* _dCamera;

	public:
		DXBasicTest(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXWindow(name, hInstance, nCmdShow) { }

	public:
		bool Init() override;
		bool Frame() override;
		bool Release() override;

	protected:
		bool PreRender() override;
	};
}
