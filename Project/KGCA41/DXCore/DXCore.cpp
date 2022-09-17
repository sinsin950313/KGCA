#include "DXCore.h"
#include "Timer.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include "TextManager.h"
#include "TextureManager.h"

namespace SSB
{
	DXCore* g_DXCore = nullptr;

	DXCore::DXCore(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXWindow(name, hInstance, nCmdShow)
	{
		g_DXCore = this;
	}

	DWORD DXCore::GetGlobalTime()
	{
		return _timer->GetElapseTime();
	}

	bool DXCore::Init()
	{
		DXWindow::Init();

		_timer = new Timer();
		_timer->Init();
		_timer->Start();

		InputManager::GetInstance().Set(GetWindowHandle());
		InputManager::GetInstance().Init();

		ShaderManager::GetInstance().Init();

		TextManager::GetInstance().Init();

		TextureManager::GetInstance().Init();

		_currentScene->Init();

		return true;
	}

	bool DXCore::Frame()
	{
		DXWindow::Frame();

		_timer->Frame();
		InputManager::GetInstance().Frame();
		ShaderManager::GetInstance().Frame();
		TextManager::GetInstance().Frame();
		TextureManager::GetInstance().Frame();

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
		DXWindow::Release();

		_timer->Release();
		delete _timer;

		InputManager::GetInstance().Release();
		ShaderManager::GetInstance().Release();
		TextManager::GetInstance().Release();
		TextureManager::GetInstance().Release();

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
		DXWindow::PreRender();

		_timer->Render();
		InputManager::GetInstance().Render();
		ShaderManager::GetInstance().Render();
		TextManager::GetInstance().Render();
		TextureManager::GetInstance().Render();

		_currentScene->Render();

		return true;
	}

	bool DXCore::MainRender()
	{
		//rendering

		DXWindow::MainRender();
		return true;
	}

	bool DXCore::PostRender()
	{
		//rendering

		DXWindow::PostRender();
		return true;
	}
}
