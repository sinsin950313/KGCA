#pragma once

#include <WinSock2.h>
#include "Common.h"
#include "CommonSocket.h"

#pragma comment(lib, "CommunicationModule.lib")

namespace SSB
{
	class ClientWindow : public Common
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
		HWND _editBox;
		HWND _button;
		HWND _listBox;

	public:
		CommunicationModule _cm;
		UserID _serverID;
		HANDLE _threadHandle;

	public:
		ClientWindow(HWND hwnd);
		ClientWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow);

	public:
		void Run();
		LRESULT CALLBACK WindowProcedureCallbackFunction(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	public:
		virtual HRESULT UpdateResize();

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
}

