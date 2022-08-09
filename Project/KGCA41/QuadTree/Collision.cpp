#include "Collision.h"
#include "Rect.h"
#include "Object.h"

bool Collision::IsCollide(const Rect& r1, const Rect& r2)
{
	return r1 && r2;
}

bool Collision::IsOverlap(const Rect& r1, const Rect& r2)
{
	Rect tmp = GetCollision(r1, r2);
	return tmp == r1 || tmp == r2;
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
