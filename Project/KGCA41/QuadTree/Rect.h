#pragma once

class Rect
{
	float _left;
	float _top;
	float _right;
	float _bottom;
	float _width;
	float _height;

public:
	Rect() = default;
	Rect(float left, float top, float width, float height)
	{
		Resize(left, top, width, height);
	}

public:
	float GetLeft() const { return _left; }
	float GetTop() const { return _top; }
	float GetRight() const { return _right; }
	float GetBottom() const { return _bottom; }
	float GetWidth() const { return _width; }
	float GetHeight() const { return _height; }

public:
	bool operator==(const Rect& rect) const;
	Rect operator&(const Rect& rect) const;
	bool operator&&(const Rect& rect) const;

public:
	void Resize(float left, float top, float width, float height);
};
