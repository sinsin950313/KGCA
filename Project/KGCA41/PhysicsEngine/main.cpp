#include "PhysicsVector.h"
#include <iostream>

int main()
{
	Vector2D vec;
	*vec[0] = 10;
	*vec[1] = 20;
	std::cout << vec.LengthSquare() << std::endl;
	std::cout << vec.Length() << std::endl;

	Vector2D vec2;
	*vec2[0] = 20;
	*vec2[1] = 10;

	std::cout << vec.Dot(vec2) << std::endl;

	vec.Normalize();
}