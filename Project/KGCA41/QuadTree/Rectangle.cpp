#include "Rectangle.h"
#include <math.h>
#include <algorithm>

Rectangle::Rectangle(float centerX, float centerY, float width, float height) : Volume(centerX, centerY, width, height)
{
	Resize(centerX, centerY, width, height);
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

void Rectangle::Resize(float centerX, float centerY, float width, float height)
{
	float halfWidth = width / 2;
	float halfHeight = height / 2;

	_lt.Repoisition(centerX - halfWidth, centerY - halfHeight);
	_rb.Repoisition(centerX + halfWidth, centerY + halfHeight);
	_width = width;
	_height = height;
}

std::vector<Point*> Rectangle::GetDetailVolumeVertexes()
{
	AddVertexes(new Point(_lt));
	AddVertexes(new Point(_lt.GetX(), _rb.GetY()));
	AddVertexes(new Point(_rb.GetX(), _lt.GetY()));
	AddVertexes(new Point(_rb));

	return GetVertexes();
}

bool Rectangle::IsIn(const Point& p) const
{
	float x = p.GetX();
	float y = p.GetY();
	return _lt.GetX() <= x && x <= _rb.GetX() && y <= _lt.GetY() && y <= _rb.GetY();
}
