#include "Rectangle.h"
#include <math.h>
#include <algorithm>
#include <iostream>

Rectangle::Rectangle(float centerX, float centerY, float width, float height)
	: Volume(Vector2D(2, centerX, centerY), sqrt(width* width + height * height) / 2, RectangleVertexFactory(-width / 2, -height / 2, width / 2, height / 2))
	, _width(width), _height(height)
{
	Resize(width, height);
	Vector2D tmp(2, centerX, centerY);
	Reposition(tmp);
}

bool Rectangle::operator==(const Rectangle& rect) const
{
	auto IsSame = [](float a, float b)->bool { return fabs(a - b) < 0.001f; };
	if (IsSame(GetLeft(), rect.GetLeft()))
	{
		if (IsSame(GetTop(), rect.GetTop()))
		{
			if (IsSame(GetRight(), rect.GetRight()))
			{
				if (IsSame(GetBottom(), rect.GetBottom()))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//Rectangle Rectangle::operator&(const Rectangle& rect) const
//{
//	float left = std::max(GetLeft(), rect.GetLeft());
//	float right = std::min(GetRight(), rect.GetRight());
//	float top = std::max(GetTop(), rect.GetTop());
//	float bottom = std::min(GetBottom(), rect.GetBottom());
//
//	return Rectangle(left, top, right - left, bottom - top);
//}

bool Rectangle::operator&&(const Rectangle& rect) const
{
	return IsCollide(rect);
}

void Rectangle::Resize(float width, float height)
{
	Volume::Resize(sqrt(width * width + height * height) / 2);

	_width = width;
	_height = height;

	_lt = Vector2D(2, -GetWidth() / 2, GetHeight() / 2);
	_rb = Vector2D(2, GetWidth() / 2, -GetHeight() / 2);
}

bool Rectangle::IsIn(const Vector2D& coordinate, const Vector2D& v) const
{
	if (Volume::IsIn(coordinate, v))
	{
		Vector2D absoulte = v + coordinate;
		Vector2D relative = absoulte - GetCenter();

		float x = relative.Get(0);
		float y = relative.Get(1);
		return _lt.Get(0) <= x && x <= _rb.Get(0) && _rb.Get(1) <= y && y <= _lt.Get(1);
	}
	return false;
}

void Rectangle::Print() const
{
	std::cout << GetLeft() << ", " << GetTop() << ", " << GetRight() << ", " << GetBottom() << ", " << GetWidth() << ", " << GetHeight() << std::endl << std::endl;
}

RectangleVertexFactory::RectangleVertexFactory(float left, float top, float right, float bottom)
	: _lt(2, left, top), _rb(2, right, bottom)
{
}

std::vector<Vector2D*> RectangleVertexFactory::operator()()
{
	std::vector<Vector2D*> ret;

	ret.push_back(new Vector2D(_lt));
	ret.push_back(new Vector2D(2, _lt.Get(0), _rb.Get(1)));
	ret.push_back(new Vector2D(2, _rb.Get(0), _lt.Get(1)));
	ret.push_back(new Vector2D(_rb));

	return ret;
}
