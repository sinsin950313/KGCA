#pragma once
class Point
{
private:
	float _x;
	float _y;

public:
	Point() = default;
	Point(float x, float y) : _x(x), _y(y) { }
	float Distance(const Point& p) const;

public:
	float GetX() const { return _x; }
	float GetY() const { return _y; }
	void Repoisition(float x, float y) { _x = x; _y = y; }
};

