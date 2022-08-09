#pragma once

#include "Circle.h"

class Rectangle
{
	float _left;
	float _top;
	float _right;
	float _bottom;
	float _width;
	float _height;

	Circle _roughBoundary;

public:
	Rectangle() = default;
	Rectangle(float left, float top, float width, float height);

public:
	float GetLeft() const { return _left; }
	float GetTop() const { return _top; }
	float GetRight() const { return _right; }
	float GetBottom() const { return _bottom; }
	float GetWidth() const { return _width; }
	float GetHeight() const { return _height; }

public:
	bool operator==(const Rectangle& rect) const;
	Rectangle operator&(const Rectangle& rect) const;
	bool operator&&(const Rectangle& rect) const;

public:
	void Resize(float left, float top, float width, float height);
};
