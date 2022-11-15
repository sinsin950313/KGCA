#include "FBXLoaderTest.h"

using namespace SSB;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	FBXLoaderTest window(L"Test", hInstance, nCmdShow);
	window.Init();
	window.Run();
	window.Release();
}
