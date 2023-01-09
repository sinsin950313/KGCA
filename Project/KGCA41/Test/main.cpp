#include "DXWindow.h"

using namespace SSB;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	DXWindow window(L"Test", hInstance, nCmdShow);
	window.Init();
	window.Run();
	window.Release();
}
