#include "Point.h"
#include <math.h>

CustomFloat Point::Distance(const Point& p) const
{
	CustomFloat dx = _x - p._x;
	CustomFloat dy = _y - p._y;
	return sqrt(dx * dx + dy * dy);
}
