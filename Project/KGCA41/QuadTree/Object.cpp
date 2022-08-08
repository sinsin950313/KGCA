#include "Object.h"

bool Rect::operator==(const Rect& rect)
{
}

Rect Rect::operator&(const Rect& rect)
{
}

bool Object::IsCollide(const Object& obj)
{
}

Rect Object::GetCollision(const Object& obj)
{
}

bool Collision::IsCollide(const Rect& r1, const Rect& r2)
{
}

bool Collision::IsOverlap(const Rect& r1, const Rect& r2)
{
}

Rect Collision::GetCollision(const Rect& r1, const Rect& r2)
{
}

bool Collision::IsCollide(const Object& obj1, const Object& obj2)
{
}

Rect Collision::GetCollision(const Object& obj1, const Object& obj2)
{
}
