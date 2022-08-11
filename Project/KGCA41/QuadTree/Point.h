#pragma once

#include "CustomMath.h"

class Point
{
private:
	CustomFloat _x;
	CustomFloat _y;

public:
	Point() = default;
	Point(CustomFloat x, CustomFloat y) : _x(x), _y(y) { }

public:
	CustomFloat Distance(const Point& p) const;
	void Repoisition(CustomFloat x, CustomFloat y) { _x = x; _y = y; }

public:
	CustomFloat GetX() const { return _x; }
	CustomFloat GetY() const { return _y; }
};
