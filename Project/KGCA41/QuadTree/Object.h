#pragma once

#include "VolumeInterface.h"
#include "Rect.h"

class Object : public VolumeInterface
{
private:
	Rect _rect;

public:
	Object() = default;
	Object(float left, float top, float width, float height) : _rect(left, top, width, height) { }
	const Rect* GetVolume() { return &_rect; }
	void Reposition(float left, float top);
	void Resize(float width, float height);

public:
	bool IsCollide(const Object& obj) const;
	Rect GetCollision(const Object& obj) const;
};
