#include "TestDXWindow.h"

bool TestDXWindow::Init()
{
	TDXWindow::Init();
	_core.SetDevice(GetDevice(), GetDeviceContext());
	_core.Init();
	return true;
}

bool TestDXWindow::Frame()
{
	TDXWindow::Frame();
	_core.Frame();
	return true;
}

bool TestDXWindow::MainRender()
{
	TDXWindow::MainRender();
	_core.Render();
	Sleep(100);
	return true;
}

bool TestDXWindow::Release()
{
	TDXWindow::Release();
	_core.Release();
	return true;
}
