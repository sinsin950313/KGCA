#include "UtilityTestWIndow.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UtilityTestWindow window(L"Test", hInstance, nCmdShow);
	window.Init();
	window.Run();
	window.Release();
}
