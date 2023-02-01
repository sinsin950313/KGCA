#pragma once

#include "Volume1.h"
#include <vector>

namespace SSB
{
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
		operator BoxData();
		operator AABBData() override;
		operator OBBData() override;
		operator SphereData() override;
	};

	class Frustum1Volume : public Volume1
	{
	public:
		operator BoxData();
		operator AABBData() override;
		operator OBBData() override;
		operator SphereData() override;
	};
}
