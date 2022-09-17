#pragma once

#include "Common.h"
#include <map>
#include <string>

namespace SSB
{
	class Scene : public Common
	{
	private:
		bool _finished = false;
		std::map<std::string, Scene*> _linkedScenes;
		Scene* _nextScene = nullptr;

	public:
		void SetFinished(bool finished) { _finished = finished; }
		bool IsFinished() { return _finished; }
		void SetNextScene(std::string sceneName) { _nextScene = _linkedScenes.find(sceneName)->second; }
		Scene* GetNextScene() { return _nextScene; }
		void LinkNewScene(std::string sceneName, Scene* scene) { _linkedScenes.insert(std::make_pair(sceneName, scene)); }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
