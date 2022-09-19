#pragma once

#include "Texture.h"
#include <vector>
#include "Timer.h"

namespace SSB
{
	class Sprite : public Texture
	{
	private:
		std::vector<RECT> _actionSequence;
		bool _loop;
		Timer _timer;
		float _interval;
		int _currentActionIndex;

	public:
		Sprite(Texture* texture, std::vector<RECT> actionSequence, bool loop);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
