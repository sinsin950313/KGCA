#pragma once
#include "DXWindow.h"
#include "DXObject.h"
#include "Map.h"

namespace SSB
{
	class ToolBaseTest : public DXWindow
	{
	private:
		DXObject* _object;
		DXObject* _objectBack;
		Map* _terrain;
		DebugCamera* _dCamera;
		ModelViewCamera* _mCamera;

		Timer* _timer;
		int _frames;
		DWORD _beforeTime;
		float _fps;

	public:
		ToolBaseTest(HWND hwnd) : DXWindow(hwnd) { }
		ToolBaseTest(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXWindow(name, hInstance, nCmdShow) { }
		virtual ~ToolBaseTest();

	public:
		bool Init() override;
		bool Frame() override;
		bool Release() override;

	protected:
		bool PreRender() override;
	};
}
