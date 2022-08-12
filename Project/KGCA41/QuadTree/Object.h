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
	Object(float centerX, float centerY, float _width, float _height) : _rect(centerX, centerY, _width, _height), _rigidBody() { }
	const Rectangle* GetVolume() { return &_rect; }
	void Reposition(float centerX, float centerY);
	void Resize(float _width, float _height);
	Rigidbody* GetRigidBody();
};
