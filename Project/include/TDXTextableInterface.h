#pragma once

#include <d2d1.h>

class TDXTextableInterface
{
public:
	virtual void Draw(ID2D1RenderTarget* renderTarget) = 0;
};
