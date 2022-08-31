#include "TestDXWindow.h"
#include <thread>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	TestDXWindow win(L"Test", hInstance, nCmdShow);
	win.Init();
	win.Run();
	win.Release();
}