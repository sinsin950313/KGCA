#pragma once

#include <Windows.h>
#include "CommonClass.h"

class TBasicWindow : public Common
{
private:
	ATOM _atom;
	LPCWSTR _name;
	HINSTANCE _hInstance;
	HWND _hWnd;
	int _nCmdShow;
	UINT _width = 800;
	UINT _height = 600;

	RECT _windowRect;
	RECT _clientRect;

public:
	TBasicWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow);
	void Run();
	LRESULT CALLBACK WindowProcedureCallbackFunction(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

public:
	HWND GetWindowHandle() { return _hWnd; }
	HINSTANCE GetInstanceHandle() { return _hInstance; }
	UINT GetClientWidth();
	UINT GetClientHeight();
};
