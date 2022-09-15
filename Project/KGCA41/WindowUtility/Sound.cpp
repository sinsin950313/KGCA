#include "Sound.h"
#include "SoundManager.h"

bool Sound::Init()
{
	_channel = nullptr;
	_play = false;
	_volume = 0.5f;
	_sound->getLength(&_totalPlayTime, FMOD_TIMEUNIT_MS);
	_currentPlayTime = 0;

	return true;
}

bool Sound::Frame()
{
	if (IsChannelAlive())
	{
		_channel->getPosition(&_currentPlayTime, FMOD_TIMEUNIT_MS);
	}

	return true;
}

bool Sound::Render()
{
	return true;
}

bool Sound::Release()
{
	_sound = nullptr;

	return true;
}

void Sound::Play(bool loop)
{
	if (!IsChannelAlive())
	{
		SoundManager::GetInstance().GetSystem()->playSound(_sound, nullptr, false, &_channel);
		_channel->setVolume(_volume);
	}
}

void Sound::Stop()
{
	if (IsChannelAlive())
	{
		_channel->stop();
	}
}

void Sound::Pause()
{
	if (IsChannelAlive())
	{
		_channel->setPaused(true);
	}
}

void Sound::Continue()
{
	if (IsChannelAlive())
	{
		_channel->setPaused(false);
	}
}

void Sound::VolumeUp()
{
	_volume += _deltaVolume;
	_volume = fmin(1.0f, _volume);
	if (IsChannelAlive())
	{
		_channel->setVolume(_volume);
	}
}

void Sound::VolumeDown()
{
	_volume -= _deltaVolume;
	_volume = fmax(0.0f, _volume);
	if (IsChannelAlive())
	{
		_channel->setVolume(_volume);
	}
}

void Sound::SetLoop()
{
	_sound->setMode(FMOD_LOOP_NORMAL);
}

bool Sound::IsChannelAlive()
{
	if (_channel != nullptr)
	{
		_channel->isPlaying(&_play);
		return _play;
	}
	_channel = nullptr;
	return false;
}
