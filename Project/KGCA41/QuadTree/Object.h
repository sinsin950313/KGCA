#pragma once

#include "VolumeInterface.h"
#include "Rectangle.h"
#include "CustomMath.h"

class Object : public VolumeInterface
{
private:
	Rectangle _rect;

public:
	Object(CustomFloat centerX, CustomFloat centerY, CustomFloat width, CustomFloat height) : _rect(centerX, centerY, width, height) { }
	const Rectangle* GetVolume() { return &_rect; }
	void Reposition(CustomFloat centerX, CustomFloat centerY);
	void Resize(CustomFloat width, CustomFloat height);
};
