#pragma once

#include <vector>
#include "Common.h"

class DX2DObject;

namespace SSB
{
	class Terrain : public Common
	{
		std::vector<DX2DObject*> _tiles;
		
	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
