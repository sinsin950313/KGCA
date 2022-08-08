#include "Object.h"
#include "Rect.h"
#include "Collision.h"

bool Object::IsCollide(const Object& obj) const
{
	return Collision::IsCollide(_rect, obj._rect);
}

Rect Object::GetCollision(const Object& obj) const
{
	return _rect & obj._rect;
}
