#pragma comment (lib, "DXGameElements.lib")

#include "DXCore.h"
#include "Timer.h"
#include "InputManager.h"
#include "DXStateManager.h"
#include "ShaderManager.h"
#include "TextManager.h"
#include "TextureManager.h"
#include "SoundManager.h"

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

        DXStateManager::GetInstance().Init();

		ShaderManager::GetInstance().Init();

		TextManager::GetInstance().Init();

		TextureResourceManager::GetInstance().Init();

		SoundManager::GetInstance().Init();

		_currentScene->Init();

		return true;
	}

	bool DXCore::Frame()
	{
		DXWindow::Frame();

		_timer->Frame();
		InputManager::GetInstance().Frame();
        DXStateManager::GetInstance().Frame();
		ShaderManager::GetInstance().Frame();
		TextManager::GetInstance().Frame();
		TextureResourceManager::GetInstance().Frame();
		SoundManager::GetInstance().Frame();

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
        DXStateManager::GetInstance().Release();
		ShaderManager::GetInstance().Release();
		TextManager::GetInstance().Release();
		TextureResourceManager::GetInstance().Release();
		SoundManager::GetInstance().Release();

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
        DXStateManager::GetInstance().Render();
		ShaderManager::GetInstance().Render();
		TextManager::GetInstance().Render();
		TextureResourceManager::GetInstance().Render();
		SoundManager::GetInstance().Render();

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
