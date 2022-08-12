#include "Rectangle.h"
#include <math.h>
#include <algorithm>

Rectangle::Rectangle(float centerX, float centerY, float width, float height)
	: Volume(centerX, centerY, 0, RectangleVertexFactory(centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2)))
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
}

void Rectangle::Reposition(float centerX, float centerY)
{
	Volume::Reposition(centerX, centerY);

	_lt.Repoisition(centerX - GetWidth() / 2, centerY - GetHeight() / 2);
	_rb.Repoisition(centerX + GetWidth() / 2, centerY + GetHeight() / 2);
}

bool Rectangle::IsIn(const Point& p) const
{
	if (Volume::IsIn(p))
	{
		float x = p.GetX();
		float y = p.GetY();
		return _lt.GetX() <= x && x <= _rb.GetX() && _lt.GetY() <= y && y <= _rb.GetY();
	}
	return false;
}

RectangleVertexFactory::RectangleVertexFactory(float left, float top, float right, float bottom)
	: _lt(left, top), _rb(right, bottom)
{
}

std::vector<Point*> RectangleVertexFactory::operator()()
{
	std::vector<Point*> ret;

	ret.push_back(new Point(_lt));
	ret.push_back(new Point(_lt.GetX(), _rb.GetY()));
	ret.push_back(new Point(_rb.GetX(), _lt.GetY()));
	ret.push_back(new Point(_rb));

	return ret;
}
