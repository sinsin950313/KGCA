#include "DXCore.h"
#include "TTimer.h"
#include "TInputManager.h"
#include "TShaderManager.h"
#include "TTextManager.h"
#include "TTextureManager.h"

DXCore* g_DXCore = nullptr;

DXCore::DXCore(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : TDXWindow(name, hInstance, nCmdShow)
{
	g_DXCore = this;
}

DWORD DXCore::GetGlobalTime()
{
	return _timer->GetElapseTime();
}

bool DXCore::Init()
{
	TDXWindow::Init();

	_timer = new TTimer();
	_timer->Init();
	_timer->Start();

	TInputManager::GetInstance().Set(GetWindowHandle());
	TInputManager::GetInstance().Init();

	TShaderManager::GetInstance().Init();

	TTextManager::GetInstance().Init();

	TTextureManager::GetInstance().Init();

	_currentScene->Init();

	return true;
}

bool DXCore::Frame()
{
	TDXWindow::Frame();

	_timer->Frame();
	TInputManager::GetInstance().Frame();
	TShaderManager::GetInstance().Frame();
	TTextManager::GetInstance().Frame();
	TTextureManager::GetInstance().Frame();

	if (_currentScene->IsFinished())
	{
		_currentScene = _currentScene->GetNextScene();
		_currentScene->Init();
	}
	_currentScene->Frame();

	return true;
}

bool DXCore::Release()
{
	TDXWindow::Release();

	_timer->Release();
	delete _timer;

	TInputManager::GetInstance().Release();
	TShaderManager::GetInstance().Release();
	TTextManager::GetInstance().Release();
	TTextureManager::GetInstance().Release();

	_currentScene = nullptr;

	for (auto scene : _scenes)
	{
		scene.second->Release();
		delete scene.second;
	}
	_scenes.clear();

	return true;
}

bool DXCore::PreRender()
{
	TDXWindow::PreRender();

	_timer->Render();
	TInputManager::GetInstance().Render();
	TShaderManager::GetInstance().Render();
	TTextManager::GetInstance().Render();
	TTextureManager::GetInstance().Render();

	_currentScene->Render();

	return true;
}

bool DXCore::MainRender()
{
	//rendering

	TDXWindow::MainRender();
	return true;
}

bool DXCore::PostRender()
{
	//rendering

	TDXWindow::PostRender();
	return true;
}
