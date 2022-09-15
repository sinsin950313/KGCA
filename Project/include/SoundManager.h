#pragma once

#include <map>
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <string>
#include "CommonClass.h"
#include "Sound.h"

class SoundManager : public Common
{
private:
	FMOD::System* _system;
	std::map<std::wstring, FMOD::Sound*> _soundList;
	std::wstring _path = L"../../Resource/Sound/";

public:
	static SoundManager* _instance;

private:
	SoundManager();

public:
	static SoundManager& GetInstance();
	~SoundManager();

public:
	void SetPath(std::wstring path) { _path = path; }
	Sound* Load(std::wstring fileName);
	void PlayInstanceSound(std::wstring fileName);
	FMOD::System* GetSystem() { return _system; }

private:
	std::wstring GetPath(std::wstring fileName) { return _path + fileName; }
	bool LoadSound(std::wstring fileName);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
