#include "Object.h"
#include "Rect.h"
#include "Collision.h"

void Object::Reposition(float left, float top)
{
	_rect.Resize(left, top, _rect.GetWidth(), _rect.GetHeight());
}

void Object::Resize(float width, float height)
{
	_rect.Resize(_rect.GetLeft(), _rect.GetTop(), width, height);
}

bool Object::IsCollide(const Object& obj) const
{
	return Collision::IsCollide(_rect, obj._rect);
}

Rect Object::GetCollision(const Object& obj) const
{
	return _rect & obj._rect;
}
