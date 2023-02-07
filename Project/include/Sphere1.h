#pragma once

#include "Volume1.h"

namespace SSB
{
	class Sphere1Volume : public Volume1
	{
		static const int PI;

	public:
		Sphere1Volume(float radius = 1.0f);

	private:
		float GetRadius(Vector3 scale);

	public:
		// Resize radius to sqrt(width * width + height * height + depth * depth);
		float GetWorldRadius();
		float GetLocalRadius();

	public:
		// Reference : http://www.songho.ca/opengl/gl_sphere.html
		std::vector<Vector3> GetWorldBaseVertices() override;
		std::vector<TriangleData> GetWorldBaseTriangles() override;

	public:
		operator AABBData() override;
		operator OBBData() override;
		operator SphereData() override;
	};
}
