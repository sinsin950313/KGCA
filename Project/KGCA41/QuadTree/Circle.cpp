#include "Circle.h"
#include <math.h>

bool Circle::operator&&(const Circle& circle) const
{
	float dx = fabs(GetCenterX() - circle.GetCenterX());
	float dy = fabs(GetCenterY() - circle.GetCenterY());
	float distance = sqrt(dx * dx + dy * dy);

	return distance <= GetRadius() + circle.GetRadius();
}

void Circle::Resize(float centerX, float centerY, float radius)
{
	_centerX = centerX;
	_centerY = centerY;
	_radius = radius;
}
