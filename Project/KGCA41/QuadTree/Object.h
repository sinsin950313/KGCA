#pragma once

#include "VolumeInterface.h"
#include "Rectangle.h"
#include "Rigidbody.h"

class Object : public VolumeInterface
{
private:
	Rectangle _rect;
	Rigidbody _rigidBody;

public:
	Object(float centerX, float centerY, float width, float height) : _rect(centerX, centerY, width, height), _rigidBody() { }
	const Rectangle* GetVolume() { return &_rect; }
	void Reposition(float centerX, float centerY);
	void Resize(float width, float height);
	Rigidbody* GetRigidBody();
};
