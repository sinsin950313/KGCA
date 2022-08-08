#pragma once

#include "VolumeInterface.h"
#include "Rect.h"

class Object : public VolumeInterface
{
private:
	Rect _rect;

public:
	Object() = default;
	const Rect* GetVolume() { return &_rect; }
	bool IsCollide(const Object& obj) const;
	Rect GetCollision(const Object& obj) const;
};
