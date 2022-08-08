#include "Collision.h"
#include "Rect.h"
#include "Object.h"
#include <algorithm>

bool Collision::IsCollide(const Rect& r1, const Rect& r2)
{
	float maxWidth = r1.GetWidth() + r2.GetWidth();
	float maxHeight = r1.GetHeight() + r2.GetHeight();

	float unionWidth = std::max(r1.GetRight(), r2.GetRight()) - std::min(r1.GetLeft(), r2.GetLeft());
	float unionHeight = std::max(r1.GetBottom(), r2.GetBottom()) - std::min(r1.GetTop(), r2.GetTop());

	return unionWidth <= maxWidth && unionHeight <= maxHeight;
}

bool Collision::IsOverlap(const Rect& r1, const Rect& r2)
{
	return IsCollide(r1, r2);
}

Rect Collision::GetCollision(const Rect& r1, const Rect& r2)
{
	return r1 & r2;
}

bool Collision::IsCollide(const Object& obj1, const Object& obj2)
{
	return obj1.IsCollide(obj2);
}

Rect Collision::GetCollision(const Object& obj1, const Object& obj2)
{
	return obj1.GetCollision(obj2);
}
