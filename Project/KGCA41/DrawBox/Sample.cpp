#include "BoxDrawer.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	BoxDrawer bd(L"Test", hInstance, nCmdShow);
	bd.Init();
	bd.Run();
	bd.Release();
}
