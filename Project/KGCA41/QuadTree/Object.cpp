#include "Object.h"
#include "Rectangle.h"

void Object::Reposition(float left, float top)
{
	_rect.Resize(left, top, _rect.GetWidth(), _rect.GetHeight());
}

void Object::Resize(float width, float height)
{
	_rect.Resize(_rect.GetLeft(), _rect.GetTop(), width, height);
}
