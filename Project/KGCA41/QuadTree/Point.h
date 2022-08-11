#pragma once

class Point
{
private:
	float _x;
	float _y;

public:
	Point() = default;
	Point(float x, float y) : _x(x), _y(y) { }

public:
	float Distance(const Point& p) const;
	void Repoisition(float x, float y) { _x = x; _y = y; }

public:
	float GetX() const { return _x; }
	float GetY() const { return _y; }
};
