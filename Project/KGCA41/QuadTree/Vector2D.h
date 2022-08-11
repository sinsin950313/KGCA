#pragma once

#include "Point.h"
#include <math.h>

class Vector2D : public Point
{
public:
	Vector2D() = default;
	Vector2D(float x, float y) : Point(x, y) { }

public:
	float LengthSquare() const { return GetX() * GetX() + GetY() * GetY(); }
	float Length() const { return sqrt(LengthSquare()); }
	float Dot(const Vector2D& vec);
	Vector2D Cross(const Vector2D& vec) = delete;

public:
	Vector2D operator+(const Vector2D& vec);
	Vector2D operator-(const Vector2D& vec);

public:
	void Repoint(float x, float y) { Repoisition(x, y); }
	void Normalize();
	Vector2D Identity();
};
