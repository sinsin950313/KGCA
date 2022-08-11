#include "Object.h"
#include "Rectangle.h"

void Object::Reposition(float centerX, float centerY)
{
	_rect.Resize(centerX, centerY, _rect.GetWidth(), _rect.GetHeight());
}

void Object::Resize(float width, float height)
{
	_rect.Resize(_rect.GetLeft(), _rect.GetTop(), width, height);
}
