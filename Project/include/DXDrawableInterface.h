#pragma once

#include <d3d11.h>

namespace SSB
{
	class DXDrawableInterface
	{
	public:
		virtual void Draw(ID3D11DeviceContext* dc) = 0;
	};
}
