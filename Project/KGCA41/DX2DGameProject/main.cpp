#include "DX2DGameProject.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	DX2DGameProject win(L"Test", hInstance, nCmdShow);
	win.Init();
	win.Run();
	win.Release();
}
