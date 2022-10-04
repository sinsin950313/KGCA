#pragma once

#include "Common.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"

namespace SSB
{
	class Sound : public Common
	{
	private:
		FMOD::Sound* _sound;
		FMOD::Channel* _channel = nullptr;
		bool _play = false;
		float _volume = 0.0f;
		const float _deltaVolume = 0.1f;
		unsigned int _totalPlayTime = 0;
		unsigned int _currentPlayTime = 0;

	public:
		Sound(FMOD::Sound* sound) { _sound = sound; }
		~Sound() { Release(); }

	public:
		void Play(bool loop);
		void Stop();
		void Pause();
		void Continue();
		void VolumeUp();
		void VolumeDown();
		void SetLoop();

	private:
		bool IsChannelAlive();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
