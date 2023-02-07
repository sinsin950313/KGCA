#pragma once

#include "Volume1.h"
#include <vector>

namespace SSB
{
	//class AABB1Volume : public Volume1
	//{
	//public:
	//	AABB1Volume(float width = 1.0f, float height = 1.0f, float depth = 1.0f);

	//private:
	//	std::vector<Vector3> GetVertices(Vector3 center, Matrix33 rotation, Vector3 scale);
	//	std::vector<PlaneData> GetPlanes(Vector3 center, Matrix33 rotation, Vector3 scale);

	//public:
	//	std::vector<Vector3> GetWorldVertices();
	//	std::vector<PlaneData> GetWorldPlanes();
	//	std::vector<Vector3> GetLocalVertices();
	//	std::vector<PlaneData> GetLocalPlanes();

	//public:
	//	operator AABBData() override;
	//	operator OBBData() override;
	//	operator SphereData() override;
	//};

	//class OBB1Volume : public Volume1
	//{
	//public:
	//	operator AABBData() override;
	//	operator OBBData() override;
	//	operator SphereData() override;
	//};

	//      5-7
	//      | |
	//      1-3
	//	5-1 1-3 3-7 7-5
	//	| | | | | | | |
	//	4-0 0-2 2-6 6-4
	//      0-2
	//      | |
	//      4-6
	class Box1Volume : public Volume1
	{
	public:
		Box1Volume(float width = 1.0f, float height = 1.0f, float depth = 1.0f);

	private:
		std::vector<Vector3> GetVertices(Vector3 center, Matrix33 rotation, Vector3 scale);
		std::vector<PlaneData> GetPlanes(Vector3 center, Matrix33 rotation, Vector3 scale);

	public:
		std::vector<Vector3> GetWorldVertices();
		std::vector<PlaneData> GetWorldPlanes();
		std::vector<Vector3> GetLocalVertices();
		std::vector<PlaneData> GetLocalPlanes();

	public:
		std::vector<Vector3> GetWorldBaseVertices() override;
		std::vector<TriangleData> GetWorldBaseTriangles() override;

	public:
		operator BoxData();
		operator AABBData() override;
		operator OBBData() override;
		operator SphereData() override;
	};
}
