#include "Box1.h"
#include "Sphere1.h"
#include "Line1.h"
#include "CollisionCalculator.h"
#include <iostream>
#include <cassert>

using namespace SSB;

void check(Volume1* src, VolumeData aim)
{
	assert(src->GetWorldPosition().GetX() == aim.Position.GetX());
	assert(src->GetWorldPosition().GetY() == aim.Position.GetY());
	assert(src->GetWorldPosition().GetZ() == aim.Position.GetZ());

	assert(src->GetWorldRotation().GetRow(0).GetX() == aim.Rotation.GetRow(0).GetX());
	assert(src->GetWorldRotation().GetRow(0).GetY() == aim.Rotation.GetRow(0).GetY());
	assert(src->GetWorldRotation().GetRow(0).GetZ() == aim.Rotation.GetRow(0).GetZ());

	assert(src->GetWorldRotation().GetRow(1).GetX() == aim.Rotation.GetRow(1).GetX());
	assert(src->GetWorldRotation().GetRow(1).GetY() == aim.Rotation.GetRow(1).GetY());
	assert(src->GetWorldRotation().GetRow(1).GetZ() == aim.Rotation.GetRow(1).GetZ());

	assert(src->GetWorldRotation().GetRow(2).GetX() == aim.Rotation.GetRow(2).GetX());
	assert(src->GetWorldRotation().GetRow(2).GetY() == aim.Rotation.GetRow(2).GetY());
	assert(src->GetWorldRotation().GetRow(2).GetZ() == aim.Rotation.GetRow(2).GetZ());

	assert(src->GetWorldScale().GetX() == aim.Scale.GetX());
	assert(src->GetWorldScale().GetY() == aim.Scale.GetY());
	assert(src->GetWorldScale().GetZ() == aim.Scale.GetZ());
}

void check(AABBData src, AABBData aim)
{
	assert(src.Min.GetX() == aim.Min.GetX());
	assert(src.Min.GetY() == aim.Min.GetY());
	assert(src.Min.GetZ() == aim.Min.GetZ());

	assert(src.Max.GetX() == aim.Max.GetX());
	assert(src.Max.GetY() == aim.Max.GetY());
	assert(src.Max.GetZ() == aim.Max.GetZ());
}

void check(OBBData src, OBBData aim)
{
	assert(src.Width == aim.Width);
	assert(src.Height == aim.Height);
	assert(src.Depth == aim.Depth);
}

void check(SphereData src, SphereData aim)
{
	assert(src.Radius == aim.Radius);
}

void check(Vector3 src, Vector3 aim)
{
	assert(src.GetX() == aim.GetX());
	assert(src.GetY() == aim.GetY());
	assert(src.GetZ() == aim.GetZ());
}

int main()
{
	DefaultCollisionCalculator calculator;

	{
		Vertex1Volume data;
		check(&data);
		check(data.operator SSB::AABBData());
		check(data.operator SSB::OBBData());
		check(data.operator SSB::SphereData());
	}

	{
		Ray1Volume data(Vector3(), { 1, 0, 0 });
		check(&data);
		check(data.operator SSB::AABBData());
		check(data.operator SSB::OBBData());
		check(data.operator SSB::SphereData());
	}

	{
		Box1Volume data;
		check(&data);
		check(data.operator SSB::AABBData());
		check(data.operator SSB::OBBData());
		check(data.operator SSB::SphereData());
	}

	{
		Sphere1Volume data;
		check(&data);
		check(data.operator SSB::AABBData());
		check(data.operator SSB::OBBData());
		check(data.operator SSB::SphereData());
	}

	{
		Vertex1Volume parent;
		Box1Volume child;
		child.SetParent(&parent);
		check(&child);
		check(child.operator SSB::AABBData());
		check(child.operator SSB::OBBData());
		check(child.operator SSB::SphereData());
	}

	{
		VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		VolumeData collisionSuccess{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		VolumeData inSuccess{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		VolumeData fail{ {1, 1, 1} , Matrix33(), {1, 1, 1} };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			for (auto vertex : result)
			{
				check(vertex, );
			}
		}

		{
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		VolumeData source{ {0, 0, 0}, Matrix33(), {1, 1, 1} };
		RayData collisionSuccess{ {{0, 0, 1}, Matrix33(), {1, 1, 1}}, {0, 0, 1}, {0, 0, -1} };
		RayData inSuccess{ {{0, 0, 1}, Matrix33(), {1, 1, 1}}, {0, 0, 1}, {0, 0, -1} };
		RayData fail{ {{2, 2, 2}, Matrix33(), {1, 1, 1}}, {2, 2, 2}, {-1, -1, -1} };

		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			for (auto vertex : result)
			{
				check(vertex, );
			}
		}

		{
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		TriangleData collisionSuccess{ {{0, 0, 0} , {1, 1, 1}, {2, 2, 0}} };
		TriangleData inSuccess{ {{0, 0, 0} , {1, 1, 1}, {2, 2, 0}} };
		TriangleData fail{ {{2, 2, 2} , {2.5, 4, 2.5}, {3, 3, 3}} };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			for (auto vertex : result)
			{
				check(vertex, );
			}
		}

		{
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		AABBData collisionSuccess{ { {0.5f, 0.5f, 0.5f} , Matrix33(), {1, 1, 1} }, {0, 0, 0} , {1, 1, 1} };
		AABBData inSuccess{ { {0.5f, 0.5f, 0.5f} , Matrix33(), {1, 1, 1} }, {0, 0, 0} , {1, 1, 1} };
		AABBData fail{ { {1.5f, 1.5f, 1.5f} , Matrix33(), {1, 1, 1} }, {1, 1, 1} , {2, 2, 2} };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			for (auto vertex : result)
			{
				check(vertex, );
			}
		}

		{
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		OBBData collisionSuccess{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 1, 1, 1 };
		OBBData inSuccess{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 1, 1, 1 };
		OBBData fail{ {{2, 2, 2} , Matrix33(), {1, 1, 1}}, 1, 1, 1 };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			for (auto vertex : result)
			{
				check(vertex, );
			}
		}

		{
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		SphereData collisionSuccess{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 1 };
		SphereData inSuccess{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 1 };
		SphereData fail{ { {2, 2, 2} , Matrix33(), {1, 1, 1} }, 1 };

		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			for (auto vertex : result)
			{
				check(vertex, );
			}
		}

		{
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		RayData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { 0, 0, 0 }, { 1, 1, 1 } };
		VolumeData collisionSuccess{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		VolumeData inSuccess{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		VolumeData fail{ {10, 10, 10} , Matrix33(), {1, 1, 1} };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			for (auto vertex : result)
			{
				check(vertex, );
			}
		}

		{
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		RayData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { 0, 0, 0 }, { 1, 1, 1 } };
		PlaneData collisionSuccess{ -1, 0, 0, 1 };
		PlaneData inSuccess{ -1, 0, 0, 1 };
		PlaneData fail{ 1, 0, 0, -1 };

		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			for (auto vertex : result)
			{
				check(vertex, );
			}
		}

		{
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		RayData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { 0, 0, 0 }, { 1, 0, 0 } };
		TriangleData collisionSuccess{ {{0, 0, 0}, {0, 1, 0}, {1, 0, 0}} };
		TriangleData inSuccess{ {{0, 0, 0}, {0, 1, 0}, {1, 0, 0}} };
		TriangleData fail{ {{1, 1, 1}, {2, 1, 1}, {1, 2, 1} } };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			for (auto vertex : result)
			{
				check(vertex, );
			}
		}

		{
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		RayData source{ {{-5, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, 0, 0 }, { 1, 0, 0 } };
		AABBData collisionSuccess{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, {-1, -1, -1}, {1, 1, 1} };
		AABBData inSuccess{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, {-1, -1, -1}, {1, 1, 1} };
		AABBData fail{ {{3, 3, 3} , Matrix33(), {1, 1, 1} }, {2, 2, 2}, {4, 4, 4} };

		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			for (auto vertex : result)
			{
				check(vertex, );
			}
		}

		{
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		RayData source{ {{-5, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, 0, 0 }, { 1, 0, 0 } };
		OBBData collisionSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1,1,1 };
		OBBData inSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1,1,1 };
		OBBData fail{ {{2, 2, 2}, Matrix33(), {1, 1, 1} }, 1, 1, 1 };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			for (auto vertex : result)
			{
				check(vertex, );
			}
		}

		{
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		RayData source{ {{-5, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, 0, 0 }, { 1, 0, 0 } };
		SphereData collisionSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1 };
		SphereData inSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1 };
		SphereData fail{ {{2, 2, 2}, Matrix33(), {1, 1, 1} }, 1 };
		{
			assert(calculator.IsCollide(source, collisionSuccess));
			assert(calculator.IsIn(source, inSuccess));
			auto result = calculator.GetIntersections(source, collisionSuccess);
			for (auto vertex : result)
			{
				check(vertex, );
			}
		}

		{
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			auto result = calculator.GetIntersections(source, fail);
			assert(result.empty());
		}
	}

	{
		AABBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, -5, -5 }, { 5, 5, 5 } };
		AABBData collisionSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, {-1, -1, -1}, {1, 1, 1} };
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
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			//auto result = calculator.GetIntersections(source, fail);
			//assert(result.empty());
		}
	}

	{
		AABBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, -5, -5 }, { 5, 5, 5 } };
		OBBData collisionSuccess{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1, 1, 1 };
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
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			//auto result = calculator.GetIntersections(source, fail);
			//assert(result.empty());
		}
	}

	{
		AABBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, -5, -5 }, { 5, 5, 5 } };
		SphereData collisionSuccess{ {{5, 5, 5}, Matrix33(), {1, 1, 1}}, 1 };
		SphereData inSuccess{ {{5, 5, 5}, Matrix33(), {1, 1, 1}}, 1 };
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
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			//auto result = calculator.GetIntersections(source, fail);
			//assert(result.empty());
		}
	}

	{
		OBBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 5, 5, 5 };
		OBBData collisionSuccess{ {{2, 2, 2}, Matrix33(), {1, 1, 1}}, 1 };
		OBBData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, 1 };
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
			assert(calculator.IsCollide(source, fail));
			//if (!!calculator.IsIn(source, fail))
			//{
			//	std::cout << "OBBData - OBBData Non-IsIn Test failed" << std::endl;
			//}
			//auto result = calculator.GetIntersections(source, fail);
			//assert(result.empty());
		}
	}

	{
		OBBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 5, 5, 5 };
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
			assert(calculator.IsCollide(source, fail));
			//if (!!calculator.IsIn(source, fail))
			//{
			//	std::cout << "OBBData - SphereData Non-IsIn Test failed" << std::endl;
			//}
			//auto result = calculator.GetIntersections(source, fail);
			//assert(result.empty());
		}
	}

	{
		SphereData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 1 };
		SphereData collisionSuccess{ {{1, 1, 1}, Matrix33(), {1, 1, 1}}, 1 };
		SphereData inSuccess{ {{1, 1, 1}, Matrix33(), {1, 1, 1}}, 1 };
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
			assert(calculator.IsCollide(source, fail));
			assert(calculator.IsIn(source, fail));
			//auto result = calculator.GetIntersections(source, fail);
			//assert(result.empty());
		}
	}

	int i = 0;

	return 0;
}