#pragma once

#include "Volume1.h"
#include <vector>
#include <set>

namespace SSB
{
	class CollisionDetectorInterface
	{
	public:
		virtual bool IsCollide(Volume1* volumeA, Volume1* volumeB) = 0;
		virtual bool IsIn(Volume1* volumeA, Volume1* volumeB) = 0;
		virtual std::vector<Vector3> GetIntersections(Volume1* volumeA, Volume1* volumeB) = 0;
	};

	class RayToTriangleCollisionDetector : public CollisionDetectorInterface
	{
	};

	class RayToAABBCollisionDetector : public CollisionDetectorInterface
	{
	};

	class RayToOBBCollisionDetector : public CollisionDetectorInterface
	{
	};

	class RayToSphereCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(Volume1* ray, Volume1* sphere) override;
		bool IsIn(Volume1* ray, Volume1* sphere) override;
		std::vector<Vector3> GetIntersections(Volume1* ray, Volume1* sphere) override;
	};
}