#include "PhysicsVector.h"
#include <iostream>

int main()
{
	Vector2D vec;
	*vec[0] = 10;
	*vec[1] = 20;
	std::cout << vec.LengthSquare() << std::endl;
	std::cout << vec.Length() << std::endl;
	std::cout << vec.Dot(vec) << std::endl;

	Vector2D tmp = vec + vec;
	tmp = tmp - vec;
	tmp = tmp * 4;
	tmp = tmp / 2;
	tmp = Vector2D();

	vec.Normalize();
	Vector2D identity = vec.Identity();
	vec.Clear();

	Vector2D varVec(2, 1.0f, 2.0f);
}