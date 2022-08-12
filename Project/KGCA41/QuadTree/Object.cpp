#include "Object.h"
#include "Rectangle.h"

void Object::Reposition(float centerX, float centerY)
{
	_rect.Reposition(centerX, centerY);
}

void Object::Resize(float _width, float _height)
{
	_rect.Resize(_width, _height);
}

Rigidbody* Object::GetRigidBody()
{
	return &_rigidBody;
}
