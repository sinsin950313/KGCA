#pragma once

#include "Point.h"
#include <math.h>
#include "CustomMath.h"

class Vector2D : public Point
{
public:
	Vector2D() = default;
	Vector2D(CustomFloat x, CustomFloat y) : Point(x, y) { }

public:
	CustomFloat LengthSquare() const { return GetX() * GetX() + GetY() * GetY(); }
	CustomFloat Length() const { return sqrt(LengthSquare()); }
	CustomFloat Dot(const Vector2D& vec);
	Vector2D Cross(const Vector2D& vec) = delete;

public:
	Vector2D operator+(const Vector2D& vec);
	Vector2D operator-(const Vector2D& vec);

public:
	void Repoint(CustomFloat x, CustomFloat y) { Repoisition(x, y); }
	void Normalize();
	Vector2D Identity();
};
