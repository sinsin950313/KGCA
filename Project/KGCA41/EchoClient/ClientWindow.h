#pragma once

#include <Windows.h>
#include "Common.h"
#include <vector>

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

		HWND _editBox;
		HWND _button;
		HWND _listBox;
		//HANDLE _threadHandle;

	public:
		//SOCKET _clientSocket;

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
