#include "DX2DGameProject.h"

DX2DGameProject::DX2DGameProject(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXCore(name, hInstance, nCmdShow)
{

}

bool DX2DGameProject::Init()
{
	DXCore::Init();
	return true;
}

bool DX2DGameProject::Frame()
{
	DXCore::Frame();
	return true;
}

bool DX2DGameProject::Release()
{
	for (auto object : _objects)
	{
		delete object;
	}
	delete _player;

	DXCore::Release();

	return true;
}

bool DX2DGameProject::PreRender()
{
	DXCore::PreRender();
	return true;
}

bool DX2DGameProject::MainRender()
{
	DXCore::MainRender();
	return true;
}

bool DX2DGameProject::PostRender()
{
	DXCore::PostRender();
	return true;
}
