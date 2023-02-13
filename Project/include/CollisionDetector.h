#pragma once

#include "CollisionSystemVolume.h"
#include <vector>
#include <set>

namespace SSB
{
	class CollisionDetectorInterface
	{
	public:
		virtual bool IsCollide(CollisionSystemVolume* volumeA, CollisionSystemVolume* volumeB) = 0;
		virtual bool IsIn(CollisionSystemVolume* volumeA, CollisionSystemVolume* volumeB) = 0;
		virtual std::vector<Vector3> GetIntersections(CollisionSystemVolume* volumeA, CollisionSystemVolume* volumeB) = 0;
	};

	//class AABBToTriangleCollisionDetector : public CollisionDetectorInterface
	//{
	//public:
	//	bool IsCollide(CollisionSystemVolume* aabb, CollisionSystemVolume* triangle) override;
	//	bool IsIn(CollisionSystemVolume* aabb, CollisionSystemVolume* triangle) override;
	//	std::vector<Vector3> GetIntersections(CollisionSystemVolume* aabb, CollisionSystemVolume* triangle) override;
	//};

	class AABBToAABBCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(CollisionSystemVolume* aabb1, CollisionSystemVolume* aabb2) override;
		bool IsIn(CollisionSystemVolume* aabb1, CollisionSystemVolume* aabb2) override;
		std::vector<Vector3> GetIntersections(CollisionSystemVolume* aabb1, CollisionSystemVolume* aabb2) override;
	};

	//class AABBToOBBCollisionDetector : public CollisionDetectorInterface
	//{
	//public:
	//	bool IsCollide(CollisionSystemVolume* aabb, CollisionSystemVolume* obb) override;
	//	bool IsIn(CollisionSystemVolume* aabb, CollisionSystemVolume* obb) override;
	//	std::vector<Vector3> GetIntersections(CollisionSystemVolume* aabb, CollisionSystemVolume* obb) override;
	//};

	//class AABBToSphereCollisionDetector : public CollisionDetectorInterface
	//{
	//public:
	//	bool IsCollide(CollisionSystemVolume* aabb, CollisionSystemVolume* sphere) override;
	//	bool IsIn(CollisionSystemVolume* aabb, CollisionSystemVolume* sphere) override;
	//	std::vector<Vector3> GetIntersections(CollisionSystemVolume* aabb, CollisionSystemVolume* sphere) override;
	//};

	//class OBBToTriangleCollisionDetector : public CollisionDetectorInterface
	//{
	//public:
	//	bool IsCollide(CollisionSystemVolume* obb, CollisionSystemVolume* triangle) override;
	//	bool IsIn(CollisionSystemVolume* obb, CollisionSystemVolume* triangle) override;
	//	std::vector<Vector3> GetIntersections(CollisionSystemVolume* obb, CollisionSystemVolume* triangle) override;
	//};

	//class OBBToAABBCollisionDetector : public CollisionDetectorInterface
	//{
	//public:
	//	bool IsCollide(CollisionSystemVolume* obb, CollisionSystemVolume* aabb) override;
	//	bool IsIn(CollisionSystemVolume* obb, CollisionSystemVolume* aabb) override;
	//	std::vector<Vector3> GetIntersections(CollisionSystemVolume* obb, CollisionSystemVolume* aabb) override;
	//};

	class OBBToOBBCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(CollisionSystemVolume* obb1, CollisionSystemVolume* obb2) override;
		bool IsIn(CollisionSystemVolume* obb1, CollisionSystemVolume* obb2) override;
		std::vector<Vector3> GetIntersections(CollisionSystemVolume* obb1, CollisionSystemVolume* obb2) override;
	};

	//class OBBToSphereCollisionDetector : public CollisionDetectorInterface
	//{
	//public:
	//	bool IsCollide(CollisionSystemVolume* obb, CollisionSystemVolume* sphere) override;
	//	bool IsIn(CollisionSystemVolume* obb, CollisionSystemVolume* sphere) override;
	//	std::vector<Vector3> GetIntersections(CollisionSystemVolume* obb, CollisionSystemVolume* sphere) override;
	//};

	//class SphereToTriangleCollisionDetector : public CollisionDetectorInterface
	//{
	//public:
	//	bool IsCollide(CollisionSystemVolume* sphere, CollisionSystemVolume* triangle) override;
	//	bool IsIn(CollisionSystemVolume* sphere, CollisionSystemVolume* triangle) override;
	//	std::vector<Vector3> GetIntersections(CollisionSystemVolume* sphere, CollisionSystemVolume* triangle) override;
	//};

	//class SphereToAABBCollisionDetector : public CollisionDetectorInterface
	//{
	//public:
	//	bool IsCollide(CollisionSystemVolume* sphere, CollisionSystemVolume* aabb) override;
	//	bool IsIn(CollisionSystemVolume* sphere, CollisionSystemVolume* aabb) override;
	//	std::vector<Vector3> GetIntersections(CollisionSystemVolume* sphere, CollisionSystemVolume* aabb) override;
	//};

	//class SphereToOBBCollisionDetector : public CollisionDetectorInterface
	//{
	//public:
	//	bool IsCollide(CollisionSystemVolume* sphere, CollisionSystemVolume* obb) override;
	//	bool IsIn(CollisionSystemVolume* sphere, CollisionSystemVolume* obb) override;
	//	std::vector<Vector3> GetIntersections(CollisionSystemVolume* sphere, CollisionSystemVolume* obb) override;
	//};

	class SphereToSphereCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(CollisionSystemVolume* sphere1, CollisionSystemVolume* sphere2) override;
		bool IsIn(CollisionSystemVolume* sphere1, CollisionSystemVolume* sphere2) override;
		std::vector<Vector3> GetIntersections(CollisionSystemVolume* sphere1, CollisionSystemVolume* sphere2) override;
	};

	class RayToTriangleCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(CollisionSystemVolume* ray, CollisionSystemVolume* triangle) override;
		bool IsIn(CollisionSystemVolume* ray, CollisionSystemVolume* triangle) override;
		std::vector<Vector3> GetIntersections(CollisionSystemVolume* ray, CollisionSystemVolume* triangle) override;
	};

	//class RayToAABBCollisionDetector : public CollisionDetectorInterface
	//{
	//public:
	//	bool IsCollide(CollisionSystemVolume* ray, CollisionSystemVolume* aabb) override;
	//	bool IsIn(CollisionSystemVolume* ray, CollisionSystemVolume* aabb) override;
	//	std::vector<Vector3> GetIntersections(CollisionSystemVolume* ray, CollisionSystemVolume* aabb) override;
	//};

	//class RayToOBBCollisionDetector : public CollisionDetectorInterface
	//{
	//public:
	//	bool IsCollide(CollisionSystemVolume* ray, CollisionSystemVolume* obb) override;
	//	bool IsIn(CollisionSystemVolume* ray, CollisionSystemVolume* obb) override;
	//	std::vector<Vector3> GetIntersections(CollisionSystemVolume* ray, CollisionSystemVolume* obb) override;
	//};

	class RayToSphereCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(CollisionSystemVolume* ray, CollisionSystemVolume* sphere) override;
		bool IsIn(CollisionSystemVolume* ray, CollisionSystemVolume* sphere) override;
		std::vector<Vector3> GetIntersections(CollisionSystemVolume* ray, CollisionSystemVolume* sphere) override;
	};

	class BoxToBoxCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(CollisionSystemVolume* box1, CollisionSystemVolume* box2) override;
		bool IsIn(CollisionSystemVolume* box1, CollisionSystemVolume* box2) override;
		std::vector<Vector3> GetIntersections(CollisionSystemVolume* box1, CollisionSystemVolume* box2) override;
	};

	class BoxToRayCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(CollisionSystemVolume* box, CollisionSystemVolume* ray) override;
		bool IsIn(CollisionSystemVolume* box, CollisionSystemVolume* ray) override;
		std::vector<Vector3> GetIntersections(CollisionSystemVolume* box, CollisionSystemVolume* ray) override;
	};

	class BoxToSphereCollisionDetector : public CollisionDetectorInterface
	{
	public:
		bool IsCollide(CollisionSystemVolume* box, CollisionSystemVolume* sphere) override;
		bool IsIn(CollisionSystemVolume* box, CollisionSystemVolume* sphere) override;
		std::vector<Vector3> GetIntersections(CollisionSystemVolume* box, CollisionSystemVolume* sphere) override;
	};
}