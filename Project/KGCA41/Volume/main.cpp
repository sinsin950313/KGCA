#include "Box1.h"
#include "Sphere1.h"
#include "Line1.h"
#include "CollisionCalculator.h"
#include <iostream>
#include <cassert>
#include "Common.h"

using namespace SSB;

void check(Volume1* src, VolumeData aim)
{
	assert(ZeroFloat(src->GetWorldPosition().GetX() - aim.Position.GetX()));
	assert(ZeroFloat(src->GetWorldPosition().GetY() - aim.Position.GetY()));
	assert(ZeroFloat(src->GetWorldPosition().GetZ() - aim.Position.GetZ()));

	auto tmp = src->GetWorldRotation();
	assert(ZeroFloat(src->GetWorldRotation().GetRow(0).GetX() - aim.Rotation.GetRow(0).GetX()));
	assert(ZeroFloat(src->GetWorldRotation().GetRow(0).GetY() - aim.Rotation.GetRow(0).GetY()));
	assert(ZeroFloat(src->GetWorldRotation().GetRow(0).GetZ() - aim.Rotation.GetRow(0).GetZ()));

	assert(ZeroFloat(src->GetWorldRotation().GetRow(1).GetX() - aim.Rotation.GetRow(1).GetX()));
	assert(ZeroFloat(src->GetWorldRotation().GetRow(1).GetY() - aim.Rotation.GetRow(1).GetY()));
	assert(ZeroFloat(src->GetWorldRotation().GetRow(1).GetZ() - aim.Rotation.GetRow(1).GetZ()));

	assert(ZeroFloat(src->GetWorldRotation().GetRow(2).GetX() - aim.Rotation.GetRow(2).GetX()));
	assert(ZeroFloat(src->GetWorldRotation().GetRow(2).GetY() - aim.Rotation.GetRow(2).GetY()));
	assert(ZeroFloat(src->GetWorldRotation().GetRow(2).GetZ() - aim.Rotation.GetRow(2).GetZ()));

	assert(ZeroFloat(src->GetWorldScale().GetX() - aim.Scale.GetX()));
	assert(ZeroFloat(src->GetWorldScale().GetY() - aim.Scale.GetY()));
	assert(ZeroFloat(src->GetWorldScale().GetZ() - aim.Scale.GetZ()));
}

void check(AABBData src, AABBData aim)
{
	assert(ZeroFloat(src.Min.GetX() - aim.Min.GetX()));
	assert(ZeroFloat(src.Min.GetY() - aim.Min.GetY()));
	assert(ZeroFloat(src.Min.GetZ() - aim.Min.GetZ()));

	assert(ZeroFloat(src.Max.GetX() - aim.Max.GetX()));
	assert(ZeroFloat(src.Max.GetY() - aim.Max.GetY()));
	assert(ZeroFloat(src.Max.GetZ() - aim.Max.GetZ()));
}

void check(OBBData src, OBBData aim)
{
	assert(ZeroFloat(src.Width - aim.Width));
	assert(ZeroFloat(src.Height - aim.Height));
	assert(ZeroFloat(src.Depth - aim.Depth));
}

void check(SphereData src, SphereData aim)
{
	assert(ZeroFloat(src.Radius - aim.Radius));
}

void check(Vector3 src, Vector3 aim)
{
	assert(ZeroFloat(src.GetX() - aim.GetX()));
	assert(ZeroFloat(src.GetY() - aim.GetY()));
	assert(ZeroFloat(src.GetZ() - aim.GetZ()));
}

int main()
{
	DefaultCollisionCalculator calculator;

	const float maxF = (std::numeric_limits<float>::max)();
	const float minF = -(std::numeric_limits<float>::max)();

	Vector3 center(10, 20, 30);
	float degree45 = 0.7853;
	HMatrix44 rot = HMatrix44::RotateFromXAxis(degree45);
	float root0_5 = 0.707;
	Vertex1Volume aim;
	aim.SetPosition(center);
	aim.SetRotation(0, degree45, 0);
	aim.SetScale(1, 1, 1);
	// origin data doesn't required when check extended data types
	VolumeData origin{ {0, 0, 0}, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {1, 1, 1} };

	{
		Vertex1Volume data;
		data.AddPosition(center);
		data.Rotate(rot);
		check(&data, aim);

		check(data.operator SSB::AABBData(), { origin, center, center });
		check(data.operator SSB::OBBData(), {origin, FDelta, FDelta, FDelta});
		check(data.operator SSB::SphereData(), { origin, FDelta });
	}

	{
		Ray1Volume data(Vector3(), { 0, 0, 1 });
		data.AddPosition(center);
		data.Rotate(rot);
		check(&data, aim);

		check(data.operator SSB::AABBData(), { origin, {10, minF, 30}, {10, 20, maxF} });
		check(data.operator SSB::OBBData(), { origin, 0, 0, maxF });
		check(data.operator SSB::SphereData(), { origin, maxF });
	}

	{
		Box1Volume data(2, 4, 6);
		data.AddPosition(center);
		data.Rotate(rot);
		data.SetScale(1, 2, 3);
		aim.SetScale(1, 2, 3);
		check(&data, aim);

		check(data.operator SSB::AABBData(), { origin, {9, 16.4683, 26.4606}, {11, 23.5316, 33.5393} });
		check(data.operator SSB::OBBData(), { origin, 2, 4, 6 });
		check(data.operator SSB::SphereData(), { origin,  3.7416});
	}

	{
		Sphere1Volume data;
		data.AddPosition(center);
		data.Rotate(rot);
		data.SetScale(1, 2, 3);
		float radius = 3.7416;
		check(&data, aim);

		check(data.operator SSB::AABBData(), { origin, {10 - radius, 20 - radius, 30 - radius}, {10 + radius, 20 + radius, 30 + radius} });
		check(data.operator SSB::OBBData(), {origin, radius * 2, radius * 2, radius * 2});
		check(data.operator SSB::SphereData(), { origin, radius });
	}

	//float degree90 = 1.5708;
	{
		Vertex1Volume parent;

		Box1Volume child(2, 2, 2);
		child.SetParent(&parent);
		child.SetPosition(center);
		child.SetScale(1, 2, 3);

		parent.SetPosition(center);
		parent.SetRotation(0, degree45, 0);
		parent.SetScale(1, 2, 3);

		Vertex1Volume aim;
		aim.SetPosition({20, -15.3461, 121.9273});
		aim.SetRotation(0, degree45, 0);
		aim.SetScale(1, 4, 9);
		check(&child, aim);

		check(child.operator SSB::AABBData(), { origin, {19, -24.5382, 112.7346}, {21, -6.1541, 131.1201} });
		check(child.operator SSB::OBBData(), {origin, 2, 8, 18});
		check(child.operator SSB::SphereData(), { origin, 9.8994 });
	}

	{
		VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		VolumeData collisionSuccess{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		VolumeData inSuccess{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		VolumeData fail{ {1, 1, 1} , Matrix33(), {1, 1, 1} };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			std::vector<Vector3> result = calculator.GetIntersections(source, collisionSuccess);
			check(result[0], { 0, 0, 0 });
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		VolumeData source;
		RayData collisionSuccess{ {{0, 0, 1}, Matrix33(), {1, 1, 1}}, {0, 0, -1}, {0, 0, 1} };
		RayData inSuccess{ {{0, 0, 1}, Matrix33(), {1, 1, 1}}, {0, 0, -1}, {0, 0, 1} };
		RayData fail{ {{2, 2, 2}, Matrix33(), {1, 1, 1}}, {2, 2, 2}, {-1, -1, -1} };

		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			check(result[0], {0, 0, 0});
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		TriangleData collisionSuccess{ {{0, 0, 0} , {1, 1, 0}, {2, 2, 0}} };
		TriangleData inSuccess{ {{-1, 0, 0} , {0, 1, 0}, {1, 0, 0}} };
		TriangleData fail{ {{2, 2, 2} , {2.5, 4, 2.5}, {3, 3, 3}} };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			check(result[0], { 0, 0, 0 });
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		AABBData collisionSuccess{ { {1, 1, 1} , Matrix33(), {2, 2, 2} }, {0, 0, 0} , {2, 2, 2} };
		AABBData inSuccess{ { {0, 0, 0} , Matrix33(), {2, 2, 2} }, {-1, -1, -1} , {1, 1, 1} };
		AABBData fail{ { {4, 4, 4} , Matrix33(), {2, 2, 2} }, {3, 3, 3} , {5, 5, 5} };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			check(result[0], {0, 0, 0});
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		OBBData collisionSuccess{ {{1, 1, 1} , Matrix33(), {1, 1, 1} }, 2, 2, 2 };
		OBBData inSuccess{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 1, 1, 1 };
		OBBData fail{ {{2, 2, 2} , Matrix33(), {1, 1, 1}}, 1, 1, 1 };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			check(result[0], { 0, 0, 0 });
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		SphereData collisionSuccess{ {{1, 0, 0} , Matrix33(), {1, 1, 1} }, 1 };
		SphereData inSuccess{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 1 };
		SphereData fail{ { {2, 2, 2} , Matrix33(), {1, 1, 1} }, 1 };

		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			check(result[0], { 0, 0, 0 });
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		RayData source{ {{0, 0, -1} , Matrix33(), {1, 1, 1} }, { 0, 0, -1 }, { 0, 0, 1 } };
		VolumeData collisionSuccess{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		//VolumeData inSuccess{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		VolumeData fail{ {10, 10, 10} , Matrix33(), {1, 1, 1} };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			//assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			check(result[0], { 0, 0, 0 });
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		RayData source{ {{0, 0, -1} , Matrix33(), {1, 1, 1} }, { 0, 0, -1 }, { 0, 0, 1 } };
		PlaneData collisionSuccess{ 0, 0, -1, 0 };
		//PlaneData inSuccess{ 0, 0, -1, -1 };
		PlaneData fail{ 0, 0, -1, -10 };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			//assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			check(result[0], { 0, 0, 0 });
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		RayData source{ {{0, 0, -1} , Matrix33(), {1, 1, 1} }, { 0, 0, -1 }, { 0, 0, 1 } };
		TriangleData collisionSuccess{ {{-1, 0, 0}, {0, 1, 0}, {1, 0, 0}} };
		//TriangleData inSuccess{ {{0, 0, 0}, {0, 1, 0}, {1, 0, 0}} };
		TriangleData fail{ {{-1, 0, -10}, {0, 1, -10}, {1, 0, -10} } };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			//assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			check(result[0], { 0, 0, 0 });
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		RayData source{ {{0, 0, -10} , Matrix33(), {1, 1, 1} }, { 0, 0, -10 }, { 0, 0, 1 } };
		AABBData collisionSuccess{ {{0, 0, 0} , Matrix33(), {2, 2, 2} }, {-1, -1, -1}, {1, 1, 1} };
		//AABBData inSuccess{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, {-1, -1, -1}, {1, 1, 1} };
		AABBData fail{ {{3, 3, 3} , Matrix33(), {1, 1, 1} }, {2, 2, 2}, {4, 4, 4} };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			//assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			check(result[0], { 0, 0, -1 });
			check(result[1], { 0, 0, 1 });
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		RayData source{ {{0, 0, -10} , Matrix33(), {1, 1, 1} }, { 0, 0, -10 }, { 0, 0, 1 } };
		OBBData collisionSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 2,2,2 };
		//OBBData inSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1,1,1 };
		OBBData fail{ {{2, 2, 2}, Matrix33(), {1, 1, 1} }, 1, 1, 1 };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			//assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			check(result[0], { 0, 0, -1 });
			check(result[1], { 0, 0, 1 });
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		RayData source{ {{0, 0, -10} , Matrix33(), {1, 1, 1} }, { 0, 0, -10 }, { 0, 0, 1 } };
		SphereData collisionSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1 };
		//SphereData inSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1 };
		SphereData fail{ {{2, 2, 2}, Matrix33(), {1, 1, 1} }, 1 };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			//assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			check(result[0], { 0, 0, -1 });
			check(result[1], { 0, 0, 1 });
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		AABBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, -5, -5 }, { 5, 5, 5 } };
		AABBData collisionSuccess{ {{5, 5, 5}, Matrix33(), {1, 1, 1}}, {0, 0, 0}, {10, 10, 10} };
		AABBData inSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, {-1, -1, -1}, {1, 1, 1} };
		AABBData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, {19, 19, 19}, {21, 21, 21} };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			//auto result = calculator.GetIntersections(source, collisionSuccess);
			//for (auto vertex : result)
			//{
			//check(vertex, );
			//}
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			//auto result = calculator.GetIntersections(source, fail);
			//assert(result.empty());
		}
	}

	{
		AABBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, -5, -5 }, { 5, 5, 5 } };
		OBBData collisionSuccess{ {{5, 5, 5}, Matrix33(), {1, 1, 1}}, 1, 1, 1 };
		OBBData inSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1, 1, 1 };
		OBBData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, 21, 21, 21 };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			//auto result = calculator.GetIntersections(source, collisionSuccess);
			//for (auto vertex : result)
			//{
			//check(vertex, );
			//}
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			//auto result = calculator.GetIntersections(source, fail);
			//assert(result.empty());
		}
	}

	{
		AABBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, -5, -5 }, { 5, 5, 5 } };
		SphereData collisionSuccess{ {{5, 5, 5}, Matrix33(), {1, 1, 1}}, 1 };
		SphereData inSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1 };
		SphereData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, 1 };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			//auto result = calculator.GetIntersections(source, collisionSuccess);
			//for (auto vertex : result)
			//{
			//check(vertex, );
			//}
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			//auto result = calculator.GetIntersections(source, fail);
			//assert(result.empty());
		}
	}

	{
		OBBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 4, 4, 4 };
		OBBData collisionSuccess{ {{2, 2, 2}, Matrix33(), {1, 1, 1}}, 2, 2, 2 };
		OBBData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, 1, 1, 1 };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			//if (!calculator.IsIn(source, inSuccess))
			//{
			//	std::cout << "OBBData - OBBData IsIn Test failed" << std::endl;
			//}
			//auto result = calculator.GetIntersections(source, collisionSuccess);
			//for (auto vertex : result)
			//{
			//check(vertex, );
			//}
		}

		{
			assert(!calculator.IsCollide(source, fail));
			//if (!!calculator.IsIn(source, fail))
			//{
			//	std::cout << "OBBData - OBBData Non-IsIn Test failed" << std::endl;
			//}
			//auto result = calculator.GetIntersections(source, fail);
			//assert(result.empty());
		}
	}

	{
		OBBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 4, 4, 4 };
		SphereData collisionSuccess{ {{2, 2, 2}, Matrix33(), {1, 1, 1}}, 1 };
		SphereData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, 1 };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			//if (!calculator.IsIn(source, inSuccess))
			//{
			//	std::cout << "OBBData - SphereData IsIn Test failed" << std::endl;
			//}
			//auto result = calculator.GetIntersections(source, collisionSuccess);
			//for (auto vertex : result)
			//{
			//check(vertex, );
			//}
		}

		{
			assert(!calculator.IsCollide(source, fail));
			//if (!!calculator.IsIn(source, fail))
			//{
			//	std::cout << "OBBData - SphereData Non-IsIn Test failed" << std::endl;
			//}
			//auto result = calculator.GetIntersections(source, fail);
			//assert(result.empty());
		}
	}

	{
		SphereData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 2 };
		SphereData collisionSuccess{ {{1, 1, 1}, Matrix33(), {1, 1, 1}}, 1 };
		SphereData inSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1 };
		SphereData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, 1 };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			//auto result = calculator.GetIntersections(source, collisionSuccess);
			//for (auto vertex : result)
			//{
			//check(vertex, );
			//}
		}

		{
			assert(!calculator.IsCollide(source, fail));
			assert(!calculator.IsIn(source, fail));
			//auto result = calculator.GetIntersections(source, fail);
			//assert(ZeroFloat(result.empty());
		}
	}

	std::cout << "All Clear" << std::endl;
	int i = 0;

	return 0;
}