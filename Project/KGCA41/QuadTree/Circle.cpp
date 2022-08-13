#define _USE_MATH_DEFINES

#include "Circle.h"
#include <math.h>

bool Circle::operator&&(const Circle& circle) const
{
	return IsCollide(circle);
}

bool Circle::operator==(const Circle& circle) const
{
	auto IsSame = [](float a, float b)->bool { return fabs(a - b) < 0.001f; };
	return IsSame(GetCenterX(), circle.GetCenterX()) && IsSame(GetCenterY(), circle.GetCenterY()) && IsSame(GetRadius(), circle.GetRadius());
}

CircleVertexFactory::CircleVertexFactory(float centerX, float centerY, float radius) : _center(centerX, centerY), _radius(radius)
{
}

std::vector<Vector2D*> CircleVertexFactory::operator()()
{
	float round = 2 * M_PI * GetRadius();
	float radian = 0.0f;
	std::vector<Vector2D*> ret;
	if (round <= 8)
	{
		for (int i = 0; i < 8; ++i)
		{
			radian += M_PI / 4;

			float x = GetCenterX() + cosf(radian);
			float y = GetCenterY() + sinf(radian);

			ret.push_back(new Vector2D(x, y));
		}
	}
	else
	{
		const float delta = 1.0f / GetRadius();
		while (radian + delta <= round)
		{
			radian += delta;

			float x = GetCenterX() + cosf(radian);
			float y = GetCenterY() + sinf(radian);

			ret.push_back(new Vector2D(x, y));
		}
	}

	return ret;
}
