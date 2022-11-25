#pragma once

#include "Texture.h"
#include <string>
#include <map>

namespace SSB
{
	class DX2DAnimation : public Sprite
	{
	private:
		std::map<std::string, SpriteAction*> _actionList;
		SpriteAction* _currentAction;

	public:
		DX2DAnimation(TextureResource* resource, TextureResource* maskResource = nullptr);
		~DX2DAnimation();

	public:
		void SetCurrentState(std::string stateName);
		void RegisterState(std::string stateName, SpriteAction* resource);
		void ChangeCurrentState(std::string stateName);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		TexturePartCoordinateRatio GetCurrentTexturePart() override;
	};
}
