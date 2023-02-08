#include "Box1.h"
#include "Sphere1.h"
#include "Line1.h"
#include "CollisionCalculator.h"
#include <iostream>

using namespace SSB;

int main()
{
	DefaultCollisionCalculator calculator;

	Vertex1Volume vertex;
	Ray1Volume ray(Vector3(), { 1, 0, 0 });
	Box1Volume box;
	Sphere1Volume sphere;
	sphere.SetParent(&vertex);

	{
		VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		VolumeData success{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		VolumeData fail{ {1, 1, 1} , Matrix33(), {1, 1, 1} };
		{
			if (!calculator.IsCollide(source, success))
			{
				std::cout << "VolumeData - VolumeData Collision Test failed" << std::endl;
			}
			if (!calculator.IsIn(source, success))
			{
				std::cout << "VolumeData - VolumeData IsIn Test failed" << std::endl;
			}
			auto result = calculator.GetIntersections(source, success);
			for (auto vertex : result)
			{
				std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
			}
		}

		{
			if (!!calculator.IsCollide(source, fail))
			{
				std::cout << "VolumeData - VolumeData Non-Collision Test failed" << std::endl;
			}
			if (!!calculator.IsIn(source, fail))
			{
				std::cout << "VolumeData - VolumeData Non-IsIn Test failed" << std::endl;
			}
			auto result = calculator.GetIntersections(source, fail);
			if (!result.empty())
			{
				std::cout << "VolumeData - VolumeData Non-Collision GetIntersection Test failed" << std::endl;
			}
		}
	}

	{
		VolumeData source{ {0, 0, 0}, Matrix33(), {1, 1, 1} };
		RayData success{ {{0, 0, 1}, Matrix33(), {1, 1, 1}}, {0, 0, 1}, {0, 0, -1} };
		RayData fail{ {{2, 2, 2}, Matrix33(), {1, 1, 1}}, {2, 2, 2}, {-1, -1, -1} };

		{
			if (!calculator.IsCollide(source, success))
			{
				std::cout << "VolumeData - RayData Collision Test failed" << std::endl;
			}
			if (!calculator.IsIn(source, success))
			{
				std::cout << "VolumeData - RayData IsIn Test failed" << std::endl;
			}
			auto result = calculator.GetIntersections(source, success);
			for (auto vertex : result)
			{
				std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
			}
		}

		{
			if (!!calculator.IsCollide(source, fail))
			{
				std::cout << "VolumeData - RayData Non-Collision Test failed" << std::endl;
			}
			if (!!calculator.IsIn(source, fail))
			{
				std::cout << "VolumeData - RayData Non-IsIn Test failed" << std::endl;
			}
			auto result = calculator.GetIntersections(source, fail);
			if (!result.empty())
			{
				std::cout << "VolumeData - RayData Non-Collision GetIntersection Test failed" << std::endl;
			}
		}
	}

	{
		VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
		TriangleData success{ {{0, 0, 0} , {1, 1, 1}, {2, 2, 0}} };
		TriangleData fail{ {{2, 2, 2} , {2.5, 4, 2.5}, {3, 3, 3}} };
		{
			if (!calculator.IsCollide(source, success))
			{
				std::cout << "VolumeData - TriangleData Collision Test failed" << std::endl;
			}
			if (!calculator.IsIn(source, success))
			{
				std::cout << "VolumeData - TriangleData IsIn Test failed" << std::endl;
			}
			auto result = calculator.GetIntersections(source, success);
			for (auto vertex : result)
			{
				std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
			}
		}

		{
			if (!!calculator.IsCollide(source, fail))
			{
				std::cout << "VolumeData - TriangleData Non-Collision Test failed" << std::endl;
			}
			if (!!calculator.IsIn(source, fail))
			{
				std::cout << "VolumeData - TriangleData Non-IsIn Test failed" << std::endl;
			}
			auto result = calculator.GetIntersections(source, fail);
			if (!result.empty())
			{
				std::cout << "VolumeData - TriangleData Non-Collision GetIntersection Test failed" << std::endl;
			}
		}

		{
			VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
			AABBData success{ { {0.5f, 0.5f, 0.5f} , Matrix33(), {1, 1, 1} }, {0, 0, 0} , {1, 1, 1} };
			AABBData fail{ { {1.5f, 1.5f, 1.5f} , Matrix33(), {1, 1, 1} }, {1, 1, 1} , {2, 2, 2} };
			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "VolumeData - AABBData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "VolumeData - AABBData IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, success);
				for (auto vertex : result)
				{
					std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "VolumeData - AABBData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "VolumeData - AABBData Non-IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, fail);
				if (!result.empty())
				{
					std::cout << "VolumeData - AABBData Non-Collision GetIntersection Test failed" << std::endl;
				}
			}
		}

		{
			VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
			OBBData success{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 1, 1, 1 };
			OBBData fail{ {{2, 2, 2} , Matrix33(), {1, 1, 1}}, 1, 1, 1 };
			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "VolumeData - OBBData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "VolumeData - OBBData IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, success);
				for (auto vertex : result)
				{
					std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "VolumeData - OBBData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "VolumeData - OBBData Non-IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, fail);
				if (!result.empty())
				{
					std::cout << "VolumeData - OBBData Non-Collision GetIntersection Test failed" << std::endl;
				}
			}
		}

		{
			VolumeData source{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
			SphereData success{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 1 };
			SphereData fail{ { {2, 2, 2} , Matrix33(), {1, 1, 1} }, 1 };

			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "VolumeData - SphereData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "VolumeData - SphereData IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, success);
				for (auto vertex : result)
				{
					std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "VolumeData - SphereData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "VolumeData - SphereData Non-IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, fail);
				if (!result.empty())
				{
					std::cout << "VolumeData - SphereData Non-Collision GetIntersection Test failed" << std::endl;
				}
			}
		}

		{
			RayData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { 0, 0, 0 }, { 1, 1, 1 } };
			VolumeData success{ {0, 0, 0} , Matrix33(), {1, 1, 1} };
			VolumeData fail{ {10, 10, 10} , Matrix33(), {1, 1, 1} };
			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "RayData - VolumeData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "RayData - VolumeData IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, success);
				for (auto vertex : result)
				{
					std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "RayData - VolumeData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "RayData - VolumeData Non-IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, fail);
				if (!result.empty())
				{
					std::cout << "RayData - VolumeData Non-Collision GetIntersection Test failed" << std::endl;
				}
			}
		}

		{
			RayData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { 0, 0, 0 }, { 1, 1, 1 } };
			PlaneData success{ -1, 0, 0, 1 };
			PlaneData fail{ 1, 0, 0, -1 };

			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "RayData - PlaneData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "RayData - PlaneData IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, success);
				for (auto vertex : result)
				{
					std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "RayData - PlaneData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "RayData - PlaneData Non-IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, fail);
				if (!result.empty())
				{
					std::cout << "RayData - PlaneData Non-Collision GetIntersection Test failed" << std::endl;
				}
			}
		}

		{
			RayData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { 0, 0, 0 }, { 1, 0, 0 } };
			TriangleData success{ {{0, 0, 0}, {0, 1, 0}, {1, 0, 0}} };
			TriangleData fail{ {{1, 1, 1}, {2, 1, 1}, {1, 2, 1} } };
			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "RayData - TriangleData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "RayData - TriangleData IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, success);
				for (auto vertex : result)
				{
					std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "RayData - TriangleData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "RayData - TriangleData Non-IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, fail);
				if (!result.empty())
				{
					std::cout << "RayData - TriangleData Non-Collision GetIntersection Test failed" << std::endl;
				}
			}
		}

		{
			RayData source{ {{-5, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, 0, 0 }, { 1, 0, 0 } };
			AABBData success{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, {-1, -1, -1}, {1, 1, 1} };
			AABBData fail{ {{3, 3, 3} , Matrix33(), {1, 1, 1} }, {2, 2, 2}, {4, 4, 4} };

			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "RayData - AABBData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "RayData - AABBData IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, success);
				for (auto vertex : result)
				{
					std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "RayData - AABBData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "RayData - AABBData Non-IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, fail);
				if (!result.empty())
				{
					std::cout << "RayData - AABBData Non-Collision GetIntersection Test failed" << std::endl;
				}
			}
		}

		{
			RayData source{ {{-5, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, 0, 0 }, { 1, 0, 0 } };
			OBBData success{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1,1,1 };
			OBBData fail{ {{2, 2, 2}, Matrix33(), {1, 1, 1} }, 1, 1, 1 };
			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "RayData - OBBData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "RayData - OBBData IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, success);
				for (auto vertex : result)
				{
					std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "RayData - OBBData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "RayData - OBBData Non-IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, fail);
				if (!result.empty())
				{
					std::cout << "RayData - OBBData Non-Collision GetIntersection Test failed" << std::endl;
				}
			}
		}

		{
			RayData source{ {{-5, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, 0, 0 }, { 1, 0, 0 } };
			SphereData success{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1 };
			SphereData fail{ {{2, 2, 2}, Matrix33(), {1, 1, 1} }, 1 };
			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "RayData - SphereData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "RayData - SphereData IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, success);
				for (auto vertex : result)
				{
					std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "RayData - SphereData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "RayData - SphereData Non-IsIn Test failed" << std::endl;
				}
				auto result = calculator.GetIntersections(source, fail);
				if (!result.empty())
				{
					std::cout << "RayData - SphereData Non-Collision GetIntersection Test failed" << std::endl;
				}
			}
		}

		{
			AABBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, -5, -5 }, { 5, 5, 5 } };
			AABBData success{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, {-1, -1, -1}, {1, 1, 1} };
			AABBData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, {19, 19, 19}, {21, 21, 21} };
			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "AABBData - AABBData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "AABBData - AABBData IsIn Test failed" << std::endl;
				}
				//auto result = calculator.GetIntersections(source, success);
				//for (auto vertex : result)
				//{
				//	std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				//}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "AABBData - AABBData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "AABBData - AABBData Non-IsIn Test failed" << std::endl;
				}
				//auto result = calculator.GetIntersections(source, fail);
				//if (!result.empty())
				//{
				//	std::cout << "AABBData - AABBData Non-Collision GetIntersection Test failed" << std::endl;
				//}
			}
		}

		{
			AABBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, -5, -5 }, { 5, 5, 5 } };
			OBBData success{ {{0, 0, 0}, Matrix33(), {1, 1, 1}}, 1, 1, 1 };
			OBBData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, 21, 21, 21 };
			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "AABBData - OBBData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "AABBData - OBBData IsIn Test failed" << std::endl;
				}
				//auto result = calculator.GetIntersections(source, success);
				//for (auto vertex : result)
				//{
				//	std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				//}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "AABBData - OBBData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "AABBData - OBBData Non-IsIn Test failed" << std::endl;
				}
				//auto result = calculator.GetIntersections(source, fail);
				//if (!result.empty())
				//{
				//	std::cout << "AABBData - OBBData Non-Collision GetIntersection Test failed" << std::endl;
				//}
			}
		}

		{
			AABBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, { -5, -5, -5 }, { 5, 5, 5 } };
			SphereData success{ {{5, 5, 5}, Matrix33(), {1, 1, 1}}, 1 };
			SphereData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, 1 };
			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "AABBData - SphereData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "AABBData - SphereData IsIn Test failed" << std::endl;
				}
				//auto result = calculator.GetIntersections(source, success);
				//for (auto vertex : result)
				//{
				//	std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				//}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "AABBData - SphereData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "AABBData - SphereData Non-IsIn Test failed" << std::endl;
				}
				//auto result = calculator.GetIntersections(source, fail);
				//if (!result.empty())
				//{
				//	std::cout << "AABBData - SphereData Non-Collision GetIntersection Test failed" << std::endl;
				//}
			}
		}

		{
			OBBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 5, 5, 5 };
			OBBData success{ {{2, 2, 2}, Matrix33(), {1, 1, 1}}, 1 };
			OBBData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, 1 };
			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "OBBData - OBBData Collision Test failed" << std::endl;
				}
				//if (!calculator.IsIn(source, success))
				//{
				//	std::cout << "OBBData - OBBData IsIn Test failed" << std::endl;
				//}
				//auto result = calculator.GetIntersections(source, success);
				//for (auto vertex : result)
				//{
				//	std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				//}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "OBBData - OBBData Non-Collision Test failed" << std::endl;
				}
				//if (!!calculator.IsIn(source, fail))
				//{
				//	std::cout << "OBBData - OBBData Non-IsIn Test failed" << std::endl;
				//}
				//auto result = calculator.GetIntersections(source, fail);
				//if (!result.empty())
				//{
				//	std::cout << "OBBData - OBBData Non-Collision GetIntersection Test failed" << std::endl;
				//}
			}
		}

		{
			OBBData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 5, 5, 5 };
			SphereData success{ {{2, 2, 2}, Matrix33(), {1, 1, 1}}, 1 };
			SphereData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, 1 };
			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "OBBData - SphereData Collision Test failed" << std::endl;
				}
				//if (!calculator.IsIn(source, success))
				//{
				//	std::cout << "OBBData - SphereData IsIn Test failed" << std::endl;
				//}
				//auto result = calculator.GetIntersections(source, success);
				//for (auto vertex : result)
				//{
				//	std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				//}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "OBBData - SphereData Non-Collision Test failed" << std::endl;
				}
				//if (!!calculator.IsIn(source, fail))
				//{
				//	std::cout << "OBBData - SphereData Non-IsIn Test failed" << std::endl;
				//}
				//auto result = calculator.GetIntersections(source, fail);
				//if (!result.empty())
				//{
				//	std::cout << "OBBData - SphereData Non-Collision GetIntersection Test failed" << std::endl;
				//}
			}
		}

		{
			SphereData source{ {{0, 0, 0} , Matrix33(), {1, 1, 1} }, 1 };
			SphereData success{ {{1, 1, 1}, Matrix33(), {1, 1, 1}}, 1 };
			SphereData fail{ {{20, 20, 20}, Matrix33(), {1, 1, 1} }, 1 };
			{
				if (!calculator.IsCollide(source, success))
				{
					std::cout << "SphereData - SphereData Collision Test failed" << std::endl;
				}
				if (!calculator.IsIn(source, success))
				{
					std::cout << "SphereData - SphereData IsIn Test failed" << std::endl;
				}
				//auto result = calculator.GetIntersections(source, success);
				//for (auto vertex : result)
				//{
				//	std::cout << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << std::endl;
				//}
			}

			{
				if (!!calculator.IsCollide(source, fail))
				{
					std::cout << "SphereData - SphereData Non-Collision Test failed" << std::endl;
				}
				if (!!calculator.IsIn(source, fail))
				{
					std::cout << "SphereData - SphereData Non-IsIn Test failed" << std::endl;
				}
				//auto result = calculator.GetIntersections(source, fail);
				//if (!result.empty())
				//{
				//	std::cout << "SphereData - SphereData Non-Collision GetIntersection Test failed" << std::endl;
				//}
			}
		}

		int i = 0;

		return 0;
	}
}