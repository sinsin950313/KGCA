#pragma once

#include <d2d1.h>

namespace SSB
{
	class DXTextableInterface
	{
	public:
		virtual void Draw(ID2D1RenderTarget* renderTarget) = 0;
	};
}
