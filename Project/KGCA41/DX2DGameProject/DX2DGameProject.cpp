#include "DX2DGameProject.h"
#include "TestScene.h"

namespace SSB
{
	DX2DGameProject::DX2DGameProject(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXCore(name, hInstance, nCmdShow)
	{
		NewScene("TestScene", new TestScene());
		SetCurrentScene("TestScene");
	}
}
