#include "ClientWindow.h"
#include <cassert>

DWORD WINAPI ClientThread(LPVOID lpThreadParameter)
{
	SSB::ClientWindow* window = (SSB::ClientWindow*)lpThreadParameter;

	//while (1)
	{
		char recvMsg[256]{ 0, };
		int recvByte = recv(window->_clientSocket, recvMsg, 256, 0);
		if (recvByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				PostQuitMessage(1);
				return 1;
			}
		}
		SendMessageA(window->_listBox, LB_ADDSTRING, 0, (LPARAM)recvMsg);
	}
}

namespace SSB
{
	ClientWindow* g_Window = nullptr;

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return g_Window->WindowProcedureCallbackFunction(hWnd, message, wParam, lParam);
	}
	ClientWindow::ClientWindow(HWND hwnd) : _hWnd(hwnd)
	{
		g_Window = this;
	}
	ClientWindow::ClientWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : _name(name), _hInstance(hInstance), _nCmdShow(nCmdShow)
	{
		g_Window = this;

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
			return;
		}

		ShowWindow(_hWnd, _nCmdShow);
	}

	bool ClientWindow::Init()
	{
		GetWindowRect(_hWnd, &_windowRect);
		GetClientRect(_hWnd, &_clientRect);

		UINT iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
		UINT iScreenHieght = GetSystemMetrics(SM_CYFULLSCREEN);
		UINT cx, cy;
		cx = (iScreenWidth - (_windowRect.right - _windowRect.left)) * 0.5f;
		cy = (iScreenHieght - (_windowRect.bottom - _windowRect.top)) * 0.5f;
		MoveWindow(_hWnd, cx, cy, _windowRect.right - _windowRect.left, _windowRect.bottom - _windowRect.top, true);

		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			return 0;
		}

		_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		{
			int ret = WSAAsyncSelect(_clientSocket, _hWnd, CUSTOM_NETWORK_MESSAGE, FD_READ);
			if (ret == SOCKET_ERROR)
			{
				return false;
			}
		}

		SOCKADDR_IN sa;
		sa.sin_family = AF_INET;
		sa.sin_addr.s_addr = inet_addr("127.0.0.1");
		sa.sin_port = htons(10000);
		{
			int ret = connect(_clientSocket, (sockaddr*)&sa, sizeof(sa));
			//if (ret == SOCKET_ERROR)
			//{
			//	TCHAR* buf = 0;
			//	int error = WSAGetLastError();
			//	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, error, 0, (TCHAR*)&buf, 0, 0);
			//	OutputDebugString(buf);
			//	WSACleanup();
			//	return 1;
			//}
		}

		//DWORD threadID;
		//_threadHandle = CreateThread(0, 0, ClientThread, (LPVOID)this, CREATE_SUSPENDED, &threadID);

		//u_long mode = TRUE;
		//ioctlsocket(clientSocket, FIONBIO, &mode);

		return true;
	}

	bool ClientWindow::Frame()
	{
		return true;
	}

	bool ClientWindow::Render()
	{
		return true;
	}

	bool ClientWindow::Release()
	{
		closesocket(_clientSocket);
		WSACleanup();
		return true;
	}

	UINT ClientWindow::GetClientWidth()
	{
		return _clientRect.right - _clientRect.left;
	}

	UINT ClientWindow::GetClientHeight()
	{
		return _clientRect.bottom - _clientRect.top;
	}

	void ClientWindow::Run()
	{
		ResumeThread(_threadHandle);

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

	LRESULT CALLBACK ClientWindow::WindowProcedureCallbackFunction(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case CUSTOM_NETWORK_MESSAGE:
		{
			if (FD_READ)
			{
				ClientThread(this);
			}
			break;
		}
		case WM_CREATE:
		{
			_editBox = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 500, 10, 200, 25, hWnd, (HMENU)1000, _hInstance, NULL);
			_button = CreateWindow(L"button", L"Send", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 700, 10, 50, 25, hWnd, (HMENU)1001, _hInstance, NULL);
			_listBox = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL, 0, 0, 500, 600, hWnd, (HMENU)1002, _hInstance, NULL);

			SendMessage(_listBox, LB_ADDSTRING, 0, (LPARAM)L"Chatting Start");
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case 1001:
			{
				char buffer[256]{ 0, };
				int ret = GetWindowTextA(_editBox, buffer, 256);
				if (ret == 0)
				{
					TCHAR* message = nullptr;
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, nullptr, GetLastError(), 0, (TCHAR*)&message, 0, nullptr);
					OutputDebugString(message);
				}
				int size = send(_clientSocket, buffer, 256, 0);
			}
			}
			break;
		}
		case WM_SIZE:
		{
			if (wParam != SIZE_MINIMIZED)
			{
				HRESULT hr;
				if (FAILED(hr = UpdateResize()))
				{
					assert(SUCCEEDED(hr));
					PostQuitMessage(1);
				}
				break;
			}
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		}

		return 0;
	}

	HRESULT ClientWindow::UpdateResize()
	{
		GetWindowRect(_hWnd, &_windowRect);
		GetClientRect(_hWnd, &_clientRect);

		return S_OK;
	}
}
