#include "Point.h"
#include <math.h>

float Point::Distance(const Point& p) const
{
	float dx = _x - p._x;
	float dy = _y - p._y;
	return sqrt(dx * dx + dy * dy);
}
