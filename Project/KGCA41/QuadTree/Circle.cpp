#define _USE_MATH_DEFINES

#include "Circle.h"
#include <math.h>

bool Circle::operator&&(const Circle& circle) const
{
	return IsCollide(circle);
}

bool Circle::operator==(const Circle& circle) const
{
	auto IsSame = [](CustomFloat a, CustomFloat b)->bool { return fabs(a - b) < 0.001f; };
	return IsSame(GetCenterX(), circle.GetCenterX()) && IsSame(GetCenterY(), circle.GetCenterY()) && IsSame(GetRadius(), circle.GetRadius());
}

CircleVertexFactory::CircleVertexFactory(CustomFloat centerX, CustomFloat centerY, CustomFloat radius) : _center(centerX, centerY), _radius(radius)
{
}

std::vector<Point*> CircleVertexFactory::operator()()
{
	CustomFloat round = 2 * M_PI * GetRadius();
	CustomFloat radian = 0.0f;
	std::vector<Point*> ret;
	if (round <= 8)
	{
		for (int i = 0; i < 8; ++i)
		{
			radian += M_PI / 4;

			CustomFloat x = GetCenterX() + cosf(radian);
			CustomFloat y = GetCenterY() + sinf(radian);

			ret.push_back(new Point(x, y));
		}
	}
	else
	{
		const CustomFloat delta = 1.0f / GetRadius();
		while (radian + delta <= round)
		{
			radian += delta;

			CustomFloat x = GetCenterX() + cosf(radian);
			CustomFloat y = GetCenterY() + sinf(radian);

			ret.push_back(new Point(x, y));
		}
	}

	return ret;
}
