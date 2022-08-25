#include "BasicWindow.h"

BasicWindow* g_Window = nullptr;

BasicWindow::BasicWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : _name(name), _hInstance(hInstance), _nCmdShow(nCmdShow)
{
	g_Window = this;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return g_Window->WindowProcedureCallbackFunction(hWnd, message, wParam, lParam);
}

void BasicWindow::Init()
{
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.lpszClassName = _name;
	wcex.hInstance = _hInstance;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &WndProc;
	wcex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

	_atom = RegisterClassExW(&wcex);

	_hWnd = CreateWindowW(_name, L"Title", WS_OVERLAPPEDWINDOW, 0, 0, 600, 800, nullptr, nullptr, _hInstance, nullptr);
	if (!_hWnd)
	{
		return;
	}

	ShowWindow(_hWnd, _nCmdShow);
}

void BasicWindow::Run()
{
	MSG msg{ 0, };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

LRESULT CALLBACK BasicWindow::WindowProcedureCallbackFunction(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
