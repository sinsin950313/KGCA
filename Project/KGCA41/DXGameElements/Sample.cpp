#include "GETestWindow.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	GETestWindow win(L"Test", hInstance, nCmdShow);
	win.Init();
	win.Run();
	win.Release();
}
