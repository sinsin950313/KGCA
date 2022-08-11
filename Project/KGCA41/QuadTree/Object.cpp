#include "Object.h"
#include "Rectangle.h"

void Object::Reposition(CustomFloat centerX, CustomFloat centerY)
{
	_rect.Resize(centerX, centerY, _rect.GetWidth(), _rect.GetHeight());
}

void Object::Resize(CustomFloat width, CustomFloat height)
{
	_rect.Resize(_rect.GetLeft(), _rect.GetTop(), width, height);
}
