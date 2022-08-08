#pragma once

#include "VolumeInterface.h"

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
	int GetLeft() const { return _left; }
	int GetTop() const { return _top; }
	int GetRight() const { return _right; }
	int GetBottom() const { return _bottom; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

public:
	bool operator==(const Rect& rect);
	Rect operator&(const Rect& rect);

public:
	void Resize(float left, float top, float width, float height)
	{
		_left = left;
		_top = top;
		_width = width;
		_height = height;
		_right = _left + _width;
		_bottom = _top + _height;

		//if (mapWidth < _left + _width)
		//{
		//	_left = width - _width;
		//}
		//if (mapHeight < _top + _height)
		//{
		//	_top = height - _height;
		//}
	}
};

class Object : public VolumeInterface
{
private:
	Rect _rect;

public:
	Object() = default;
	const Rect* GetVolume() { return &_rect; }
	bool IsCollide(const Object& obj);
	Rect GetCollision(const Object& obj);
};

class Collision
{
public:
	static bool IsCollide(const Rect& r1, const Rect& r2);
	static bool IsOverlap(const Rect& r1, const Rect& r2);
	static Rect GetCollision(const Rect& r1, const Rect& r2);

public:
	static bool IsCollide(const Object& obj1, const Object& obj2);
	static Rect GetCollision(const Object& obj1, const Object& obj2);
};
