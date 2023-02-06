#include "CollisionDetector.h"
#include "CollisionCalculator.h"
#include "Line1.h"
#include "Sphere1.h"
#include "Box1.h"
#include "Plane1.h"

namespace SSB
{
	extern DefaultCollisionCalculator kDefaultCollisionCalculator;

	bool RayToSphereCollisionDetector::IsCollide(Volume1* ray, Volume1* sphere)
	{
		RayData rayData = *(Ray1Volume*)ray;
		SphereData sphereData = *(Sphere1Volume*)sphere;
		if (kDefaultCollisionCalculator.IsCollide(rayData, sphereData))
		{
			return true;
		}
		return false;
	}
	bool RayToSphereCollisionDetector::IsIn(Volume1* ray, Volume1* sphere)
	{
		RayData rayData = *(Ray1Volume*)ray;
		SphereData sphereData = *(Sphere1Volume*)sphere;
		if (kDefaultCollisionCalculator.IsIn(rayData, sphereData))
		{
			return true;
		}
		return false;
	}
	std::vector<Vector3> RayToSphereCollisionDetector::GetIntersections(Volume1* ray, Volume1* sphere)
	{
		RayData rayData = *(Ray1Volume*)ray;
		SphereData sphereData = *(Sphere1Volume*)sphere;
		return { kDefaultCollisionCalculator.GetIntersections(rayData, sphereData) };
	}
	bool RayToTriangleCollisionDetector::IsCollide(Volume1* ray, Volume1* triangle)
	{
		RayData rayData = *(Ray1Volume*)ray;
		TriangleData triangleData = *(Triangle1Volume*)triangle;
		if (kDefaultCollisionCalculator.IsCollide(rayData, triangleData))
		{
			return true;
		}
		return false;
	}
	bool RayToTriangleCollisionDetector::IsIn(Volume1* ray, Volume1* triangle)
	{
		RayData rayData = *(Ray1Volume*)ray;
		TriangleData triangleData = *(Triangle1Volume*)triangle;
		if (kDefaultCollisionCalculator.IsIn(rayData, triangleData))
		{
			return true;
		}
		return false;
	}
	std::vector<Vector3> RayToTriangleCollisionDetector::GetIntersections(Volume1* ray, Volume1* triangle)
	{
		RayData rayData = *(Ray1Volume*)ray;
		TriangleData triangleData = *(Triangle1Volume*)triangle;
		return { kDefaultCollisionCalculator.GetIntersections(rayData, triangleData) };
	}
	bool RayToAABBCollisionDetector::IsCollide(Volume1* ray, Volume1* AABB)
	{
		RayData rayData = *(Ray1Volume*)ray;
		AABBData aabbData = *(AABB1Volume*)AABB;
		if (kDefaultCollisionCalculator.IsCollide(rayData, aabbData))
		{
			return true;
		}
		return false;
	}
	bool RayToAABBCollisionDetector::IsIn(Volume1* ray, Volume1* AABB)
	{
		RayData rayData = *(Ray1Volume*)ray;
		AABBData aabbData = *(AABB1Volume*)AABB;
		if (kDefaultCollisionCalculator.IsIn(rayData, aabbData))
		{
			return true;
		}
		return false;
	}
	std::vector<Vector3> RayToAABBCollisionDetector::GetIntersections(Volume1* ray, Volume1* AABB)
	{
		RayData rayData = *(Ray1Volume*)ray;
		AABBData aabbData = *(AABB1Volume*)AABB;
		return { kDefaultCollisionCalculator.GetIntersections(rayData, aabbData) };
	}
	bool RayToOBBCollisionDetector::IsCollide(Volume1* ray, Volume1* obb)
	{
		RayData rayData = *(Ray1Volume*)ray;
		OBBData obbData = *(OBB1Volume*)obb;
		if (kDefaultCollisionCalculator.IsCollide(rayData, obbData))
		{
			return true;
		}
		return false;
	}
	bool RayToOBBCollisionDetector::IsIn(Volume1* ray, Volume1* obb)
	{
		RayData rayData = *(Ray1Volume*)ray;
		OBBData obbData = *(OBB1Volume*)obb;
		if (kDefaultCollisionCalculator.IsIn(rayData, obbData))
		{
			return true;
		}
		return false;
	}
	std::vector<Vector3> RayToOBBCollisionDetector::GetIntersections(Volume1* ray, Volume1* obb)
	{
		RayData rayData = *(Ray1Volume*)ray;
		OBBData obbData = *(OBB1Volume*)obb;
		return { kDefaultCollisionCalculator.GetIntersections(rayData, obbData) };
	}
	bool AABBToTriangleCollisionDetector::IsCollide(Volume1* aabb, Volume1* triangle)
	{
		AABBData rayData = *(AABB1Volume*)aabb;
		TriangleData triangleData = *(Triangle1Volume*)triangle;
		if (kDefaultCollisionCalculator.IsCollide(rayData, triangleData))
		{
			return true;
		}
		return false;
	}
	bool AABBToTriangleCollisionDetector::IsIn(Volume1* aabb, Volume1* triangle)
	{
		AABBData aabbData = *(AABB1Volume*)aabb;
		OBBData obbData = *(OBB1Volume*)triangle;
		if (kDefaultCollisionCalculator.IsIn(aabbData, obbData))
		{
			return true;
		}
		return false;
	}
	std::vector<Vector3> AABBToTriangleCollisionDetector::GetIntersections(Volume1* aabb, Volume1* triangle)
	{
		AABBData aabbData = *(AABB1Volume*)aabb;
		TriangleData triangleData = *(Triangle1Volume*)triangle;
		return { kDefaultCollisionCalculator.GetIntersections(aabbData, triangleData) };
	}
	bool AABBToOBBCollisionDetector::IsCollide(Volume1* aabb, Volume1* obb)
	{
		AABBData aabbData = *(AABB1Volume*)aabb;
		OBBData obbData = *(OBB1Volume*)obb;
		if (kDefaultCollisionCalculator.IsCollide(aabbData, obbData))
		{
			return true;
		}
		return false;
	}
	bool AABBToOBBCollisionDetector::IsIn(Volume1* aabb, Volume1* obb)
	{
		AABBData aabbData = *(AABB1Volume*)aabb;
		OBBData obbData = *(OBB1Volume*)obb;
		if (kDefaultCollisionCalculator.IsIn(aabbData, obbData))
		{
			return true;
		}
		return false;
	}
	std::vector<Vector3> AABBToOBBCollisionDetector::GetIntersections(Volume1* aabb, Volume1* obb)
	{
		AABBData aabbData = *(AABB1Volume*)aabb;
		OBBData obbData = *(OBB1Volume*)obb;
		return { kDefaultCollisionCalculator.GetIntersections(aabbData, obbData) };
	}
	bool AABBToSphereCollisionDetector::IsCollide(Volume1* aabb, Volume1* sphere)
	{
		AABBData aabbData = *(AABB1Volume*)aabb;
		SphereData sphereData = *(SphereData*)sphere;
		if (kDefaultCollisionCalculator.IsCollide(aabbData, sphereData))
		{
			return true;
		}
		return false;
	}
	bool AABBToSphereCollisionDetector::IsIn(Volume1* aabb, Volume1* sphere)
	{
		AABBData aabbData = *(AABB1Volume*)aabb;
		SphereData sphereData = *(SphereData*)sphere;
		if (kDefaultCollisionCalculator.IsIn(aabbData, sphereData))
		{
			return true;
		}
		return false;
	}
	std::vector<Vector3> AABBToSphereCollisionDetector::GetIntersections(Volume1* aabb, Volume1* sphere)
	{
		AABBData aabbData = *(AABB1Volume*)aabb;
		SphereData sphereData = *(Sphere1Volume*)sphere;
		return { kDefaultCollisionCalculator.GetIntersections(aabbData, sphereData) };
	}
}