#include "DX2DAnimation.h"

SSB::DX2DAnimation::DX2DAnimation(TextureResource* resource, TextureResource* maskResource) : Sprite(resource, maskResource)
{
}

SSB::DX2DAnimation::~DX2DAnimation()
{
	Release();
}

void SSB::DX2DAnimation::SetCurrentState(std::string stateName)
{
	_currentAction = _actionList.find(stateName)->second;
	_currentAction->ResetAction();
	SetSamplerState(_currentAction->GetSamplerState());
}

void SSB::DX2DAnimation::RegisterState(std::string stateName, SpriteAction* resource)
{
	_actionList.insert(std::make_pair(stateName, resource));
	resource->Init();
}

void SSB::DX2DAnimation::ChangeCurrentState(std::string stateName)
{
	SetCurrentState(stateName);
}

bool SSB::DX2DAnimation::Init()
{
	Sprite::Init();

	return true;
}

bool SSB::DX2DAnimation::Frame()
{
	Sprite::Frame();

	_currentAction->Frame();

	return true;
}

bool SSB::DX2DAnimation::Render()
{
	Sprite::Render();

	return true;
}

bool SSB::DX2DAnimation::Release()
{
	for (auto iter : _actionList)
	{
		iter.second->Release();
		delete iter.second;
	}
	_actionList.clear();

	_currentAction = nullptr;

	Sprite::Release();

	return true;
}

SSB::TexturePartCoordinateRatio SSB::DX2DAnimation::GetCurrentTexturePart()
{
	return _currentAction->GetCurrentTexturePart();
}
