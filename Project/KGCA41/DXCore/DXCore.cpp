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

		_beforeTime = _timer->GetElapseTime();
		_frames = 0;
		_fps = 0.0f;

		InputManager::GetInstance().Set(GetWindowHandle());
		InputManager::GetInstance().Init();

        DXStateManager::GetInstance().Init();

		ShaderManager::GetInstance().Init();

		TextManager::GetInstance().Init();

		TextureResourceManager::GetInstance().Init();

		SoundManager::GetInstance().Init();

		_currentScene->Init();

		_timerText = new Text(L"", { 0, 0, 500, 100 });
        _timerText->SetTextFormat(TextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
        _timerText->SetBrush(TextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
        _timerText->Init();

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

		++_frames;
		if (1000.0f < _timer->GetElapseTime() - _beforeTime)
		{
			_fps = _frames * 1000.0f / (_timer->GetElapseTime() - _beforeTime);
			_frames = 0;
			_beforeTime = _timer->GetElapseTime();
		}
		_timerText->SetString(L"Time : " + std::to_wstring(_timer->GetElapseTime() / 1000.0f) + L" FPS : " + std::to_wstring(_fps));

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

		_timerText->Release();

		return true;
	}

	bool DXCore::PreRender()
	{
		DXWindow::PreRender();

		_timer->Render();
		_timerText->Render();
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
