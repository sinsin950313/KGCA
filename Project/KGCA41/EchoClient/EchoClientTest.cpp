#include <WinSock2.h>
#include "ClientWindow.h"
#include <iostream>

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	SSB::ClientWindow window(L"Client", hInstance, nCmdShow);
	window.Init();
	window.Run();
	window.Release();
}
