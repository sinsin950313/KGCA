#pragma once

#include <d3d11.h>

class TDXDrawableInterface
{
public:
	virtual void Draw(ID3D11DeviceContext* dc) = 0;
};
