#pragma once

#include "Volume1.h"

namespace SSB
{
	class Sphere1Volume : public Volume1
	{
	public:
		Sphere1Volume(float radius = 1.0f);

	private:
		float GetRadius(Vector3 scale);

	public:
		// Resize radius to sqrt(width * width + height * height + depth * depth);
		float GetWorldRadius();
		float GetLocalRadius();

	public:
		operator AABBData() override;
		operator OBBData() override;
		operator SphereData() override;
	};
}
