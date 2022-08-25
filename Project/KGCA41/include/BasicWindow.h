#pragma once

#include <Windows.h>

class BasicWindow
{
private:
	ATOM _atom;
	LPCWSTR _name;
	HINSTANCE _hInstance;
	HWND _hWnd;
	int _nCmdShow;

public:
	BasicWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow);
	void Init();
	void Run();
	LRESULT CALLBACK WindowProcedureCallbackFunction(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
