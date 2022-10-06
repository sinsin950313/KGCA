#include "BasicWindow.h"

namespace SSB
{
	BasicWindow* g_Window = nullptr;

	BasicWindow::BasicWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : _name(name), _hInstance(hInstance), _nCmdShow(nCmdShow)
	{
		g_Window = this;
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return g_Window->WindowProcedureCallbackFunction(hWnd, message, wParam, lParam);
	}

	bool BasicWindow::Init()
	{
		WNDCLASSEXW wcex;
		ZeroMemory(&wcex, sizeof(wcex));

		wcex.cbSize = sizeof(WNDCLASSEXW);
		wcex.lpszClassName = _name;
		wcex.hInstance = _hInstance;
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

		_atom = RegisterClassEx(&wcex);

		RECT rect{ 0, 0, _width, _height };
		DWORD csStyle = WS_OVERLAPPEDWINDOW;
		AdjustWindowRect(&rect, csStyle, FALSE);
		_hWnd = CreateWindowW(_name, _name, csStyle, 0, 0, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, _hInstance, nullptr);
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

	bool BasicWindow::Frame()
	{
		return false;
	}

	bool BasicWindow::Render()
	{
		return false;
	}

	bool BasicWindow::Release()
	{
		return false;
	}

	UINT BasicWindow::GetClientWidth()
	{
		return _clientRect.right - _clientRect.left;
	}

	UINT BasicWindow::GetClientHeight()
	{
		return _clientRect.bottom - _clientRect.top;
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
			else
			{
				Frame();
				Render();
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
}
