#include "Vector2D.h"

float Vector2D::Dot(const Vector2D& vec)
{
	return GetX() * vec.GetX() + GetY() * vec.GetY();
}

Vector2D Vector2D::operator+(const Vector2D& vec) const
{
	return Vector2D(GetX() + vec.GetX(), GetY() + GetY());
}

void Vector2D::operator+=(const Vector2D& vec)
{
	Repoint(GetX() + vec.GetX(), GetY() + vec.GetY());
}

Vector2D Vector2D::operator-(const Vector2D& vec) const
{
	return Vector2D(GetX() - vec.GetX(), GetY() - GetY());
}

Vector2D Vector2D::operator*(float scalar) const
{
	return Vector2D(GetX() * scalar, GetY() * scalar);
}

Vector2D Vector2D::operator/(float scalar) const
{
	return operator*(1 / scalar);
}

void Vector2D::Normalize()
{
	Vector2D tmp = Identity();
	Repoint(tmp.GetX(), tmp.GetY());
}

Vector2D Vector2D::Identity()
{
	float lengthInvert = 1 / Length();
	Vector2D ret(GetX() * lengthInvert, GetY() * lengthInvert);
	return ret;
}

Point operator+(const Point& p, const Vector2D vec)
{
	return Point(p.GetX() + vec.GetX(), p.GetY() + vec.GetY());
}
