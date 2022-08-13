#include "Rectangle.h"
#include <math.h>
#include <algorithm>
#include <iostream>

Rectangle::Rectangle(float centerX, float centerY, float width, float height)
	: Volume(centerX, centerY, sqrt(width* width + height * height) / 2, RectangleVertexFactory(-width / 2, -height / 2, width / 2, height / 2))
	, _width(width), _height(height)
{
	Resize(width, height);
	Reposition(centerX, centerY);
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

Rectangle Rectangle::operator&(const Rectangle& rect) const
{
	float left = std::max(GetLeft(), rect.GetLeft());
	float right = std::min(GetRight(), rect.GetRight());
	float top = std::max(GetTop(), rect.GetTop());
	float bottom = std::min(GetBottom(), rect.GetBottom());

	return Rectangle(left, top, right - left, bottom - top);
}

bool Rectangle::operator&&(const Rectangle& rect) const
{
	return IsCollide(rect);
}

void Rectangle::Resize(float width, float height)
{
	Volume::Resize(sqrt(width * width + height * height) / 2);

	_width = width;
	_height = height;

	_lt.Repoint(-GetWidth() / 2, -GetHeight() / 2);
	_rb.Repoint(GetWidth() / 2, GetHeight() / 2);
}

void Rectangle::Reposition(float centerX, float centerY)
{
	Volume::Reposition(centerX, centerY);
}

bool Rectangle::IsIn(const Vector2D& coordinate, const Vector2D& v) const
{
	if (Volume::IsIn(coordinate, v))
	{
		Vector2D absoulte = v + coordinate;
		Vector2D relative = absoulte - GetCenter();

		float x = relative.GetX();
		float y = relative.GetY();
		return _lt.GetX() <= x && x <= _rb.GetX() && _lt.GetY() <= y && y <= _rb.GetY();
	}
	return false;
}

void Rectangle::Print() const
{
	std::cout << GetLeft() << ", " << GetTop() << ", " << GetRight() << ", " << GetBottom() << std::endl << std::endl;
}

RectangleVertexFactory::RectangleVertexFactory(float left, float top, float right, float bottom)
	: _lt(left, top), _rb(right, bottom)
{
}

std::vector<Vector2D*> RectangleVertexFactory::operator()()
{
	std::vector<Vector2D*> ret;

	ret.push_back(new Vector2D(_lt));
	ret.push_back(new Vector2D(_lt.GetX(), _rb.GetY()));
	ret.push_back(new Vector2D(_rb.GetX(), _lt.GetY()));
	ret.push_back(new Vector2D(_rb));

	return ret;
}
