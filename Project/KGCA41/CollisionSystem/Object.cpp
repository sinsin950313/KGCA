#include "Object.h"
#include "Rectangle.h"

void Object::Reposition(float centerX, float centerY)
{
	_rect.Reposition(centerX, centerY);
}

void Object::Resize(float width, float height)
{
	_rect.Resize(width, height);
}

Rigidbody* Object::GetRigidBody()
{
	return &_rigidBody;
}
