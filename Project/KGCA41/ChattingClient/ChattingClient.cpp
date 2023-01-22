#include "ChattingClient.h"
#include <cassert>
#include "AsyncSelectBaseCommunicationModule.h"

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

		_cm.SetWindowHandle(_hWnd);
		_serverId = _cm.Connect();
		_cm.RegisterAsyncSelectSocket(_serverId);
		class EnterPacketContent : public PacketContent
		{
		public:
			PacketContentStruct Serialize() override
			{
				PacketContentStruct data;
				data.Size = 0;
				return data;
			}
		};
		EnterPacketContent content;
		_cm.Write(_serverId, SSB::Packet(ServerEnter, content));

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
		class ExitPacketContent : public PacketContent
		{
		public:
			PacketContentStruct Serialize() override
			{
				PacketContentStruct data;
				data.Size = 0;
				return data;
			}
		};
		ExitPacketContent content;
		_cm.Write(_serverId, SSB::Packet(ServerExit, content));
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
		Release();
	}

	LRESULT CALLBACK ClientWindow::WindowProcedureCallbackFunction(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case CUSTOM_NETWORK_MESSAGE:
		{
			WORD selectEvent = WSAGETSELECTEVENT(lParam);
			switch (selectEvent)
			{
			case FD_READ:
			{
				SSB::Packet packet;
				if (_cm.Read(_serverId, packet))
				{
					_decoder.SetMessagedUserID(_serverId);
					CommunicationTypeAction* action = _decoder.Decode(packet);
					(*action)();
				}
				break;
			}
			}
			break;
		}
		case WM_CREATE:
		{
			_editBox = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 500, 10, 200, 25, hWnd, (HMENU)1000, _hInstance, NULL);
			_button = CreateWindow(L"button", L"Send", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 700, 10, 50, 25, hWnd, (HMENU)1001, _hInstance, NULL);
			_listBox = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL, 0, 0, 500, 600, hWnd, (HMENU)1002, _hInstance, NULL);

			SendMessage(_listBox, LB_ADDSTRING, 0, (LPARAM)L"Chatting Start");

			_decoder.SetCommunicationModule(&_cm);
			_decoder.SetMessageBox(_listBox);
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case 1001:
			{
#define BufferSize 200
				char buffer[BufferSize]{ 0, };
				int ret = GetWindowTextA(_editBox, buffer, BufferSize);
				if (ret == 0)
				{
					TCHAR* message = nullptr;
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, nullptr, GetLastError(), 0, (TCHAR*)&message, 0, nullptr);
					OutputDebugString(message);
				}

				class MessagePacketContent : public PacketContent
				{
				private:
					int _length;
					char* _buffer[PacketSize - HeaderSize];

				public:
					void SetMessage(char* buf, int size)
					{
						memcpy(_buffer, buf, size);
						_length = size;
					}

				public:
					PacketContentStruct Serialize() override
					{
						PacketContentStruct data;
						data.Size = _length;
						memcpy(data.Stream, _buffer, _length);
						return data;
					}
				};
				MessagePacketContent content;
				content.SetMessage(buffer, BufferSize);
				_cm.Write(_serverId, SSB::Packet(MessageTransfer, content));
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
	void ClientActionDecoder::SetCommunicationModule(CommunicationModule* cm)
	{
		_cm = (AsyncSelectBaseCommunicationModule*)cm;
	}
	void ClientActionDecoder::SetMessagedUserID(UserID id)
	{
		_id = id;
	}
	void ClientActionDecoder::SetMessageBox(HWND messageBox)
	{
		_messageBox = messageBox;
	}
	CommunicationTypeAction* ClientActionDecoder::Decode(Packet packet)
	{
		HeaderStructure header;
		memcpy(&header, packet.Serialize(), HeaderSize);

		CommunicationTypeAction* ret = nullptr;
		switch (header.Type)
		{
		case ServerEnter:
		{
			break;
		}
		case MessageTransfer:
		{
			static MessageAction action;
			action.SetMessage((char*)packet.Serialize() + HeaderSize, header.ContentLength);
			action.SetMessageBox(_messageBox);
			ret = &action;
			break;
		}
		case ServerExit:
		{
			break;
		}

		return ret;
		}
	}
	void MessageAction::SetMessage(char* buf, int length)
	{
		ZeroMemory(_msg, sizeof(_msg) / sizeof(_msg[0]));
		memcpy(_msg, buf, length);
	}
	void MessageAction::SetMessageBox(HWND messageBox)
	{
		_messageBox = messageBox;
	}
	void MessageAction::operator()()
	{
		char buffer[256];
		memcpy(buffer, _msg, sizeof(_msg) / sizeof(_msg[0]));
		SendMessageA(_messageBox, LB_ADDSTRING, 0, (LPARAM)buffer);
	}
}
