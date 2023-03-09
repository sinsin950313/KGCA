#include "CharacterToolTest.h"
#include "FBXLoader.h"

namespace SSB
{
	CharacterToolTest::CharacterToolTest(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXWindow(name, hInstance, nCmdShow)
	{
	}
	SSB::CharacterToolTest::CharacterToolTest(HWND hwnd) : DXWindow(hwnd)
	{
	}
	bool CharacterToolTest::Init()
	{
		DXWindow::Init();

		_tool.Init();
		_tool.RegisterObjectFileName("Swat.FBX");
		_tool.RegisterScriptFileName("CharacterToolTest.FBXScript");
		_tool.Import();

		_tool.Import();

		_tool.SelectCurrentAction(_tool.kNewActionName);

		//_tool.ChangeActionName("strafe");
		//_tool.ChangeEndFrame(20);

		_tool.RegisterScriptFileName("CharacterToolResult.FBXScript");
		_tool.Export();

		_tool.SelectCurrentAction("backward");

		_camera = new DebugCamera();
		ChangeMainCamera(_camera);
		GetMainCamera()->Move({ 0, 0, -10 });

		return true;
	}
	bool SSB::CharacterToolTest::Frame()
	{
		DXWindow::Frame();

		_tool.Frame();
		_camera->Frame();

		return true;
	}
	bool CharacterToolTest::Release()
	{
		_tool.Release();
		_camera->Release();

		DXWindow::Release();
		return true;
	}
	bool CharacterToolTest::PreRender()
	{
		DXWindow::PreRender();

		_tool.Render();
		_camera->Render();

		return true;
	}
}
