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
	public:
		bool IsCollide(Volume1* ray, Volume1* triangle) override;
		bool IsIn(Volume1* ray, Volume1* triangle) override;
		std::vector<Vector3> GetIntersections(Volume1* ray, Volume1* triangle) override;
	};

	class RayToAABBCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(Volume1* ray, Volume1* aabb) override;
		bool IsIn(Volume1* ray, Volume1* aabb) override;
		std::vector<Vector3> GetIntersections(Volume1* ray, Volume1* aabb) override;
	};

	class RayToOBBCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(Volume1* ray, Volume1* obb) override;
		bool IsIn(Volume1* ray, Volume1* obb) override;
		std::vector<Vector3> GetIntersections(Volume1* ray, Volume1* obb) override;
	};

	class RayToSphereCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(Volume1* ray, Volume1* sphere) override;
		bool IsIn(Volume1* ray, Volume1* sphere) override;
		std::vector<Vector3> GetIntersections(Volume1* ray, Volume1* sphere) override;
	};

	class AABBToTriangleCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(Volume1* aabb, Volume1* triangle) override;
		bool IsIn(Volume1* aabb, Volume1* triangle) override;
		std::vector<Vector3> GetIntersections(Volume1* aabb, Volume1* triangle) override;
	};

	class AABBToOBBCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(Volume1* aabb, Volume1* obb) override;
		bool IsIn(Volume1* aabb, Volume1* obb) override;
		std::vector<Vector3> GetIntersections(Volume1* aabb, Volume1* obb) override;
	};

	class AABBToSphereCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(Volume1* aabb, Volume1* sphere) override;
		bool IsIn(Volume1* aabb, Volume1* sphere) override;
		std::vector<Vector3> GetIntersections(Volume1* aabb, Volume1* sphere) override;
	};
}