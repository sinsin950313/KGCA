#include "TBasicWindow.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	TBasicWindow window(L"Test", hInstance, nCmdShow);
	window.Init();
	window.Run();
}