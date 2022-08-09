#include "Rectangle.h"
#include <math.h>
#include <algorithm>

Rectangle::Rectangle(float left, float top, float width, float height)
{
	Resize(left, top, width, height);
}

bool Rectangle::operator==(const Rectangle& rect) const
{
	auto IsSame = [](float a, float b)->bool { return fabs(a - b) < 0.001f; };
	if (IsSame(_left, rect._left))
	{
		if (IsSame(_top, rect._top))
		{
			if (IsSame(_right, rect._right))
			{
				if (IsSame(_bottom, rect._bottom))
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
	if (_roughBoundary && rect._roughBoundary)
	{
		float maxWidth = GetWidth() + rect.GetWidth();
		float maxHeight = GetHeight() + rect.GetHeight();

		float unionWidth = std::max(GetRight(), rect.GetRight()) - std::min(GetLeft(), rect.GetLeft());
		float unionHeight = std::max(GetBottom(), rect.GetBottom()) - std::min(GetTop(), rect.GetTop());

		return unionWidth <= maxWidth && unionHeight <= maxHeight;
	}
	return false;
}

void Rectangle::Resize(float left, float top, float width, float height)
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

		float centerX = left + (width / 2);
		float centerY = top + (height / 2);

		float a = width / 2;
		float b = width / 2;
		float radius = sqrt(a * a + b * b);
		_roughBoundary.Resize(centerX, centerY, radius);
}
