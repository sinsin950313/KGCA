#pragma once

#include "Common.h"

namespace SSB
{
	class SpriteManager : public Common
	{
	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
