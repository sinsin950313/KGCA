#pragma once

#include "CommonClass.h"
#include "Rectangle.h"

class DX2DCamera : public Common
{
private:
	Custom::Rectangle _lensArea;

public:
	DX2DCamera(Vector2D center, float width, float height) : _lensArea(center.Get(0), center.Get(1), width, height) { }

public:
	Custom::Rectangle GetLensArea() { return _lensArea; }
	void Move(Vector2D center);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
