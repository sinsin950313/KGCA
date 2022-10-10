#include "DX2DGameProject.h"

using namespace SSB;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	DX2DGameProject win(L"TopGun!", hInstance, nCmdShow);
	win.Init();
	win.Run();
	win.Release();
}
