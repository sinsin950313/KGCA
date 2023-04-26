#include <WinSock2.h>
#include "ClientWindow.h"
#include <cassert>

const SSB::ProtocolType DefaultMsg = 1000;

namespace SSB
{
	class DefaultAction : public CommunicationTypeAction
	{
	private:
		char* _target;
		char* _msg;
		int _length;

	public:
		void SetMessage(char* msg, int length);
		void SetData(char* msg);

	public:
		void operator()() override;
	};
	void DefaultAction::SetMessage(char* msg, int length)
	{
		_msg = msg;
		_length = length;
	}
	void DefaultAction::SetData(char* msg)
	{
		_target = msg;
	}
	void DefaultAction::operator()()
	{
		memcpy(_target, _msg, _length);
	}

	class DefaultDecoder : public Decoder
	{
	public:
		CommunicationTypeAction* Decode(Packet packet) override;
	};
	CommunicationTypeAction* DefaultDecoder::Decode(Packet packet)
	{
		int totalLength = packet.GetLength();
		char* str = (char*)packet.Serialize();
		HeaderStructure header;
		memcpy(&header, str, HeaderSize);

		CommunicationTypeAction* ret = nullptr;

		ProtocolType protocol = header.Type;
		switch (protocol)
		{
		case DefaultMsg:
		{
			static DefaultAction action;
			action.SetMessage(str + HeaderSize, header.ContentLength);
			ret = (CommunicationTypeAction*)&action;
			break;
		}
		}

		return ret;
	}

	class DefaultPacketContent : public PacketContent
	{
	private:
		char _str[256];
		int _length;

	public:
		void SetMessage(char* str, int length);

	public:
		PacketContentStruct Serialize() override;
	};
	void DefaultPacketContent::SetMessage(char* str, int length)
	{
		_length = length;
		memcpy(_str, str, length);
	}
	PacketContentStruct DefaultPacketContent::Serialize()
	{
		PacketContentStruct ret;
		ret.Size = _length;
		memcpy(&ret.Stream, _str, _length);
		return ret;
	}
}

DWORD WINAPI ClientThread(LPVOID lpThreadParameter)
{
	SSB::ClientWindow* window = (SSB::ClientWindow*)lpThreadParameter;

	while (1)
	{
		SSB::Packet packet;
		if (window->_cm.Read(window->_serverID, packet))
		{
			SSB::DefaultDecoder decoder;
			SSB::DefaultAction* action = (SSB::DefaultAction*)decoder.Decode(packet);

			char recvMsg[256]{ 0, };
			action->SetData(recvMsg);
			(*action)();
			SendMessageA(window->_listBox, LB_ADDSTRING, 0, (LPARAM)recvMsg);
		}
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

		_serverID = _cm.Connect();

		DWORD threadID;
		_threadHandle = CreateThread(0, 0, ClientThread, (LPVOID)this, CREATE_SUSPENDED, &threadID);

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
				char buffer[200]{ 0, };
				int ret = GetWindowTextA(_editBox, buffer, 256);
				if (ret == 0)
				{
					TCHAR* message = nullptr;
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, nullptr, GetLastError(), 0, (TCHAR*)&message, 0, nullptr);
					OutputDebugString(message);
				}

				SSB::DefaultPacketContent content;
				content.SetMessage(buffer, 200);
				_cm.Write(_serverID, Packet(DefaultMsg, content));
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

