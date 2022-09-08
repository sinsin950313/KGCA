#include "TDXWindow.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	TDXWindow win(L"Test", hInstance, nCmdShow);
	win.Init();
	win.Run();
	win.Release();
}
