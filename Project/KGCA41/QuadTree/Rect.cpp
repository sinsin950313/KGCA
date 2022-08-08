#include "Rect.h"
#include <math.h>
#include <algorithm>

bool Rect::operator==(const Rect& rect)
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

Rect Rect::operator&(const Rect& rect) const
{
	float left = std::max(GetLeft(), rect.GetLeft());
	float right = std::min(GetRight(), rect.GetRight());
	float top = std::max(GetTop(), rect.GetTop());
	float bottom = std::min(GetBottom(), rect.GetBottom());

	return Rect(left, top, right - left, bottom - top);
}

void Rect::Resize(float left, float top, float width, float height)
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
