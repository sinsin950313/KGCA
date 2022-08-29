#include "TriangleDrawer.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	TriangleDrawer td(L"Test", hInstance, nCmdShow);
	td.Init();
	td.Run();
	td.Release();
}
