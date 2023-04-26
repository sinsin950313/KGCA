#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment (lib, "CommunicationModule.lib")

#include <WinSock2.h>
#include <Windows.h>
#include "Common.h"
#include <vector>
#include "AsyncSelectBaseCommunicationModule.h"

namespace SSB
{
	class MessageAction : public CommunicationTypeAction
	{
	private:
		char _msg[256];
		HWND _messageBox;

	public:
		void SetMessage(char* buf, int length);
		void SetMessageBox(HWND messageBox);

	public:
		void operator()() override;
	};

	class ClientActionDecoder : public Decoder
	{
	private:
		AsyncSelectBaseCommunicationModule* _cm;
		UserID _id;
		HWND _messageBox;

	public:
		void SetCommunicationModule(CommunicationModule* cm);
		void SetMessagedUserID(UserID id);
		void SetMessageBox(HWND messageBox);

	public:
		CommunicationTypeAction* Decode(Packet packet) override;
	};

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
		SSB::AsyncSelectBaseCommunicationModule _cm;
		SSB::ClientActionDecoder _decoder;
		SSB::UserID _serverId;

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
