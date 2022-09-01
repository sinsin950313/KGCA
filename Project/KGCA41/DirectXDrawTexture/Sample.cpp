#include "TDXTextureWindow.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	TDXTextureWindow win(L"Test", hInstance, nCmdShow);
	win.Init();
	win.Run();
	win.Release();
}
