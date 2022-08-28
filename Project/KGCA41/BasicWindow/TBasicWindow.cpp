#include "TBasicWindow.h"

TBasicWindow* g_Window = nullptr;

TBasicWindow::TBasicWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : _name(name), _hInstance(hInstance), _nCmdShow(nCmdShow)
{
	g_Window = this;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return g_Window->WindowProcedureCallbackFunction(hWnd, message, wParam, lParam);
}

bool TBasicWindow::Init()
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

	RECT rect{ 0, 0, _width, _height };
	AdjustWindowRect(&rect, wcex.style, FALSE);
	_hWnd = CreateWindowW(_name, L"Title", WS_OVERLAPPEDWINDOW, 0, 0, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, _hInstance, nullptr);
	if (!_hWnd)
	{
		return false;
	}

	ShowWindow(_hWnd, _nCmdShow);
	GetWindowRect(_hWnd, &_windowRect);
	GetClientRect(_hWnd, &_clientRect);

	UINT iScreenWidht = GetSystemMetrics(SM_CXFULLSCREEN);
	UINT iScreenHieght = GetSystemMetrics(SM_CYFULLSCREEN);
	UINT cx, cy;
	cx = (iScreenWidht - (_windowRect.right - _windowRect.left)) * 0.5f;
	cy = (iScreenHieght - (_windowRect.bottom - _windowRect.top)) * 0.5f;
	MoveWindow(_hWnd, cx, cy, _windowRect.right - _windowRect.left, _windowRect.bottom - _windowRect.top, true);

	return true;
}

bool TBasicWindow::Frame()
{
	return false;
}

bool TBasicWindow::Render()
{
	return false;
}

bool TBasicWindow::Release()
{
	return false;
}

UINT TBasicWindow::GetClientWidth()
{
	return _clientRect.right - _clientRect.left;
}

UINT TBasicWindow::GetClientHeight()
{
	return _clientRect.bottom - _clientRect.top;
}

void TBasicWindow::Run()
{
	MSG msg{ 0, };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Frame();
			Render();
		}
	}
}

LRESULT CALLBACK TBasicWindow::WindowProcedureCallbackFunction(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
