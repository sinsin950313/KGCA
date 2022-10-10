#pragma once

#include <d3d11.h>
#include "Common.h"

namespace SSB
{
	struct Position2D
	{
		float x;
		float y;
	};

	class DXDrawableInterface : public Common
	{
	public:
		virtual void Draw(ID3D11DeviceContext* dc) = 0;
		virtual void UpdateParentData(Position2D parentCenter, float parentRadian) = 0;
	};
}
