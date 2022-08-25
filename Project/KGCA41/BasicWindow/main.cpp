#include "BasicWindow.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	BasicWindow window(L"Test", hInstance, nCmdShow);
	window.Init();
	window.Run();
}