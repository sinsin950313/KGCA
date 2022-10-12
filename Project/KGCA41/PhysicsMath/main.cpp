#include "PhysicsVector.h"
#include <iostream>

int main()
{
	SSB::Vector2D vec;
	*vec[0] = 10;
	*vec[1] = 20;
	std::cout << vec.LengthSquare() << std::endl;
	std::cout << vec.Length() << std::endl;
	std::cout << vec.Dot(vec) << std::endl;

	SSB::Vector2D tmp = vec + vec;
	tmp = tmp - vec;
	tmp = tmp * 4;
	tmp = tmp / 2;
	tmp = SSB::Vector2D();

	vec.Normalize();
	SSB::Vector2D identity = vec.Identity();
	vec.Clear();

	SSB::Vector2D varVec(2, 1.0f, 2.0f);

	SSB::Vector3DData aVecData{ 1, 1, 0 };
	SSB::Vector3D aVec(std::move(aVecData));
	SSB::Vector3DData bVecData{ 0, 1, 1 };
	SSB::Vector3D bVec(std::move(bVecData));
	auto crossResult = bVec.Cross(aVec);
}