#pragma once

#include "VolumeInterface.h"
#include "Rectangle.h"

class Object : public VolumeInterface
{
private:
	Rectangle _rect;

public:
	Object() = default;
	Object(float left, float top, float width, float height) : _rect(left, top, width, height) { }
	const Rectangle* GetVolume() { return &_rect; }
	void Reposition(float left, float top);
	void Resize(float width, float height);
};
