#include "Collision.h"
#include "Rectangle.h"
#include "Circle.h"

bool Collision::IsCollide(const Rectangle& r1, const Rectangle& r2)
{
	return (r1 && r2) || (r2 && r1);
}

bool Collision::IsOverlap(const Rectangle& r1, const Rectangle& r2)
{
	Rectangle tmp = GetCollision(r1, r2);
	return tmp == r1 || tmp == r2;
}

Rectangle Collision::GetCollision(const Rectangle& r1, const Rectangle& r2)
{
	return r1 & r2;
}

bool Collision::IsCollide(const Circle& cir1, const Circle& cir2)
{
	return cir1 && cir2;
}
