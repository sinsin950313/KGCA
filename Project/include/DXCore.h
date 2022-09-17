#pragma once

#include "DXWindow.h"
#include "Scene.h"
#include <map>
#include <string>

namespace SSB
{
	class Timer;

	class DXCore : public DXWindow
	{
	private:
		Timer* _timer;
		std::map<std::string, Scene*> _scenes;
		Scene* _currentScene = nullptr;

	public:
		DXCore(LPCWSTR name, HINSTANCE hInstance, int nCmdShow);

	public:
		DWORD GetGlobalTime();
		void NewScene(std::string sceneName, Scene* scene) { _scenes.insert(std::make_pair(sceneName, scene)); }
		Scene* GetScene(std::string sceneName) { return _scenes.find(sceneName)->second; }
		void SetCurrentScene(std::string sceneName) { _currentScene = _scenes.find(sceneName)->second; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Release() override;

	protected:
		bool PreRender() override;
		bool MainRender() override;
		bool PostRender() override;
	};
}
