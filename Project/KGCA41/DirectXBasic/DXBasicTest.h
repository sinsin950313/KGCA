#pragma once
#include "DXWindow.h"

namespace SSB
{
	class DXObject;
	class Map;

	class DXBasicTest : public DXWindow
	{
	private:
		DXObject* _object;
		//DXObject* _objectBack;
		//Map* _terrain;
		DebugCamera* _dCamera;
		ModelViewCamera* _mCamera;

		Timer* _timer;
		int _frames;
		DWORD _beforeTime;
		float _fps;

	public:
		DXBasicTest(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXWindow(name, hInstance, nCmdShow) { }
		~DXBasicTest();

	public:
		bool Init() override;
		bool Frame() override;
		bool Release() override;

	protected:
		bool PreRender() override;
	};
}
