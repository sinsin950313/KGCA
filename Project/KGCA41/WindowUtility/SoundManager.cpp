#pragma comment (lib, "fmod_vc.lib")

#include "SoundManager.h"
#include "CommonUtility.h"
#include <cassert>

namespace SSB
{
	SoundManager SoundManager::_instance;

	SoundManager::SoundManager()
	{
		Init();
	}

	SoundManager& SoundManager::GetInstance()
	{
		return _instance;
	}

	bool SoundManager::LoadSound(std::wstring fileName)
	{
		auto fullpath = GetPath(fileName);
		if (_soundList.find(fileName) == _soundList.end())
		{
			FMOD::Sound* sound = nullptr;
			FMOD_RESULT fr = _system->createSound((wtm(fullpath)).c_str(), FMOD_DEFAULT, nullptr, &sound);
			if (fr != FMOD_OK)
			{
				assert(fr == FMOD_OK);
				return false;
			}
			_soundList.insert(std::make_pair(fileName, sound));
		}
		return true;
	}

	Sound* SoundManager::Load(std::wstring fileName)
	{
		LoadSound(fileName);
		FMOD::Sound* sound = _soundList.find(fileName)->second;

		return new Sound(sound);
	}

	void SoundManager::PlayInstanceSound(std::wstring fileName)
	{
		LoadSound(fileName);
		FMOD::Sound* sound = _soundList.find(fileName)->second;
		FMOD::Channel* channel;
		_system->playSound(sound, nullptr, false, &channel);
	}

	bool SoundManager::Init()
	{
		FMOD::System_Create(&_system);
		_system->init(32, FMOD_INIT_NORMAL, 0);

		return true;
	}

	bool SoundManager::Frame()
	{
		_system->update();

		return true;
	}

	bool SoundManager::Render()
	{
		return true;
	}

	bool SoundManager::Release()
	{
		for (auto sound : _soundList)
		{
			sound.second->release();
		}
		_soundList.clear();

		if (_system)
		{
			_system->close();
			_system->release();
			_system = nullptr;
		}

		return true;
	}
}
