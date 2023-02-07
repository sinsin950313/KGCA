#include "CollisionDetector.h"
#include "CollisionCalculator.h"
#include "Line1.h"

namespace SSB
{
	extern DefaultCollisionCalculator kDefaultCollisionCalculator;

	bool RayToSphereCollisionDetector::IsCollide(Volume1* ray, Volume1* sphere)
	{
		RayData rayData = *(Ray1Volume*)ray;
		SphereData sphereData = sphere->operator SSB::SphereData();
		return kDefaultCollisionCalculator.IsCollide(rayData, sphereData);
	}
	bool RayToSphereCollisionDetector::IsIn(Volume1* ray, Volume1* sphere)
	{
		RayData rayData = *(Ray1Volume*)ray;
		SphereData sphereData = sphere->operator SSB::SphereData();
		return kDefaultCollisionCalculator.IsIn(rayData, sphereData);
	}
	std::vector<Vector3> RayToSphereCollisionDetector::GetIntersections(Volume1* ray, Volume1* sphere)
	{
		RayData rayData = *(Ray1Volume*)ray;
		SphereData sphereData = sphere->operator SSB::SphereData();
		return { kDefaultCollisionCalculator.GetIntersections(rayData, sphereData) };
	}
	bool RayToTriangleCollisionDetector::IsCollide(Volume1* ray, Volume1* triangle)
	{
		RayData rayData = *(Ray1Volume*)ray;
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			if (kDefaultCollisionCalculator.IsCollide(rayData, triangleData))
			{
				return true;
			}
		}
		return false;
	}
	bool RayToTriangleCollisionDetector::IsIn(Volume1* ray, Volume1* triangle)
	{
		RayData rayData = *(Ray1Volume*)ray;
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			if (kDefaultCollisionCalculator.IsIn(rayData, triangleData))
			{
				return true;
			}
		}
		return false;
	}
	std::vector<Vector3> RayToTriangleCollisionDetector::GetIntersections(Volume1* ray, Volume1* triangle)
	{
		std::vector<Vector3> ret;
		RayData rayData = *(Ray1Volume*)ray;
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			std::vector<Vector3> tmp = kDefaultCollisionCalculator.GetIntersections(rayData, triangleData);
			ret.insert(ret.end(), tmp.begin(), tmp.end());
		}
		return ret;
	}
	bool RayToAABBCollisionDetector::IsCollide(Volume1* ray, Volume1* AABB)
	{
		RayData rayData = *(Ray1Volume*)ray;
		AABBData aabbData = AABB->operator SSB::AABBData();
		return kDefaultCollisionCalculator.IsCollide(rayData, aabbData);
	}
	bool RayToAABBCollisionDetector::IsIn(Volume1* ray, Volume1* AABB)
	{
		RayData rayData = *(Ray1Volume*)ray;
		AABBData aabbData = AABB->operator SSB::AABBData();
		return kDefaultCollisionCalculator.IsIn(rayData, aabbData);
	}
	std::vector<Vector3> RayToAABBCollisionDetector::GetIntersections(Volume1* ray, Volume1* AABB)
	{
		RayData rayData = *(Ray1Volume*)ray;
		AABBData aabbData = AABB->operator SSB::AABBData();
		return { kDefaultCollisionCalculator.GetIntersections(rayData, aabbData) };
	}
	bool RayToOBBCollisionDetector::IsCollide(Volume1* ray, Volume1* obb)
	{
		RayData rayData = *(Ray1Volume*)ray;
		OBBData obbData = obb->operator SSB::OBBData();
		return kDefaultCollisionCalculator.IsCollide(rayData, obbData);
	}
	bool RayToOBBCollisionDetector::IsIn(Volume1* ray, Volume1* obb)
	{
		RayData rayData = *(Ray1Volume*)ray;
		OBBData obbData = obb->operator SSB::OBBData();
		return kDefaultCollisionCalculator.IsIn(rayData, obbData);
	}
	std::vector<Vector3> RayToOBBCollisionDetector::GetIntersections(Volume1* ray, Volume1* obb)
	{
		RayData rayData = *(Ray1Volume*)ray;
		OBBData obbData = obb->operator SSB::OBBData();
		return { kDefaultCollisionCalculator.GetIntersections(rayData, obbData) };
	}
	bool AABBToTriangleCollisionDetector::IsCollide(Volume1* aabb, Volume1* triangle)
	{
		AABBData rayData = aabb->operator SSB::AABBData();
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			if (kDefaultCollisionCalculator.IsCollide(rayData, triangleData))
			{
				return true;
			}
		}
		return false;
	}
	bool AABBToTriangleCollisionDetector::IsIn(Volume1* aabb, Volume1* triangle)
	{
		AABBData aabbData = aabb->operator SSB::AABBData();
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			if (kDefaultCollisionCalculator.IsIn(aabbData, triangleData))
			{
				return true;
			}
		}
		return false;
	}
	std::vector<Vector3> AABBToTriangleCollisionDetector::GetIntersections(Volume1* aabb, Volume1* triangle)
	{
		std::vector<Vector3> ret;
		RayData rayData = *(Ray1Volume*)triangle;
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			std::vector<Vector3> tmp = kDefaultCollisionCalculator.GetIntersections(rayData, triangleData);
			ret.insert(ret.end(), tmp.begin(), tmp.end());
		}
		return ret;
	}
	bool AABBToOBBCollisionDetector::IsCollide(Volume1* aabb, Volume1* obb)
	{
		AABBData aabbData = aabb->operator SSB::AABBData();
		OBBData obbData = obb->operator SSB::OBBData();
		return kDefaultCollisionCalculator.IsCollide(aabbData, obbData);
	}
	bool AABBToOBBCollisionDetector::IsIn(Volume1* aabb, Volume1* obb)
	{
		AABBData aabbData = aabb->operator SSB::AABBData();
		OBBData obbData = obb->operator SSB::OBBData();
		return kDefaultCollisionCalculator.IsIn(aabbData, obbData);
	}
	std::vector<Vector3> AABBToOBBCollisionDetector::GetIntersections(Volume1* aabb, Volume1* obb)
	{
		AABBData aabbData = aabb->operator SSB::AABBData();
		OBBData obbData = obb->operator SSB::OBBData();
		return { kDefaultCollisionCalculator.GetIntersections(aabbData, obbData) };
	}
	bool AABBToSphereCollisionDetector::IsCollide(Volume1* aabb, Volume1* sphere)
	{
		AABBData aabbData = aabb->operator SSB::AABBData();
		SphereData sphereData = *(SphereData*)sphere;
		return kDefaultCollisionCalculator.IsCollide(aabbData, sphereData);
	}
	bool AABBToSphereCollisionDetector::IsIn(Volume1* aabb, Volume1* sphere)
	{
		AABBData aabbData = aabb->operator SSB::AABBData();
		SphereData sphereData = *(SphereData*)sphere;
		return kDefaultCollisionCalculator.IsIn(aabbData, sphereData);
	}
	std::vector<Vector3> AABBToSphereCollisionDetector::GetIntersections(Volume1* aabb, Volume1* sphere)
	{
		AABBData aabbData = aabb->operator SSB::AABBData();
		SphereData sphereData = sphere->operator SSB::SphereData();
		return { kDefaultCollisionCalculator.GetIntersections(aabbData, sphereData) };
	}
	bool AABBToAABBCollisionDetector::IsCollide(Volume1* aabb1, Volume1* aabb2)
	{
		AABBData aabb1Data = aabb1->operator SSB::AABBData();
		AABBData aabb2Data = aabb2->operator SSB::AABBData();
		return kDefaultCollisionCalculator.IsCollide(aabb1Data, aabb2Data);
	}
	bool AABBToAABBCollisionDetector::IsIn(Volume1* aabb1, Volume1* aabb2)
	{
		AABBData aabb1Data = aabb1->operator SSB::AABBData();
		AABBData aabb2Data = aabb2->operator SSB::AABBData();
		return kDefaultCollisionCalculator.IsIn(aabb1Data, aabb2Data);
	}
	std::vector<Vector3> AABBToAABBCollisionDetector::GetIntersections(Volume1* aabb1, Volume1* aabb2)
	{
		AABBData aabb1Data = aabb1->operator SSB::AABBData();
		AABBData aabb2Data = aabb2->operator SSB::AABBData();
		return kDefaultCollisionCalculator.GetIntersections(aabb1Data, aabb2Data);
	}
	bool SphereToSphereCollisionDetector::IsCollide(Volume1* sphere1, Volume1* sphere2)
	{
		SphereData sphere1Data = sphere1->operator SSB::SphereData();
		SphereData sphere2Data = sphere2->operator SSB::SphereData();
		return kDefaultCollisionCalculator.IsCollide(sphere1Data, sphere2Data);
	}
	bool SphereToSphereCollisionDetector::IsIn(Volume1* sphere1, Volume1* sphere2)
	{
		SphereData sphere1Data = sphere1->operator SSB::SphereData();
		SphereData sphere2Data = sphere2->operator SSB::SphereData();
		return kDefaultCollisionCalculator.IsIn(sphere1Data, sphere2Data);
	}
	std::vector<Vector3> SphereToSphereCollisionDetector::GetIntersections(Volume1* sphere1, Volume1* sphere2)
	{
		SphereData sphere1Data = sphere1->operator SSB::SphereData();
		SphereData sphere2Data = sphere2->operator SSB::SphereData();
		return kDefaultCollisionCalculator.GetIntersections(sphere1Data, sphere2Data);
	}
	bool OBBToTriangleCollisionDetector::IsCollide(Volume1* obb, Volume1* triangle)
	{
		OBBData obbData = obb->operator SSB::OBBData();
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			if (kDefaultCollisionCalculator.IsCollide(obbData, triangleData))
			{
				return true;
			}
		}
		return false;
	}

	bool OBBToTriangleCollisionDetector::IsIn(Volume1* obb, Volume1* triangle)
	{
		OBBData obbData = obb->operator SSB::OBBData();
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			if (kDefaultCollisionCalculator.IsIn(obbData, triangleData))
			{
				return true;
			}
		}
		return false;
	}

	std::vector<Vector3> OBBToTriangleCollisionDetector::GetIntersections(Volume1* obb, Volume1* triangle)
	{
		std::vector<Vector3> ret;
		OBBData obbData = obb->operator SSB::OBBData();
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			std::vector<Vector3> tmp = kDefaultCollisionCalculator.GetIntersections(obbData, triangleData);
			ret.insert(ret.end(), tmp.begin(), tmp.end());
		}
		return ret;
	}

	bool OBBToAABBCollisionDetector::IsCollide(Volume1* obb, Volume1* aabb)
	{
		OBBData obbData = obb->operator SSB::OBBData();
		AABBData aabbData = aabb->operator SSB::AABBData();
		return kDefaultCollisionCalculator.IsCollide(obbData, aabbData);
	}

	bool OBBToAABBCollisionDetector::IsIn(Volume1* obb, Volume1* aabb)
	{
		OBBData obbData = obb->operator SSB::OBBData();
		AABBData aabbData = aabb->operator SSB::AABBData();
		return kDefaultCollisionCalculator.IsIn(obbData, aabbData);
	}

	std::vector<Vector3> OBBToAABBCollisionDetector::GetIntersections(Volume1* obb, Volume1* aabb)
	{
		OBBData obbData = obb->operator SSB::OBBData();
		AABBData aabbData = aabb->operator SSB::AABBData();
		return kDefaultCollisionCalculator.GetIntersections(obbData, aabbData);
	}

	bool OBBToOBBCollisionDetector::IsCollide(Volume1* obb1, Volume1* obb2)
	{
		OBBData obb1Data = obb1->operator SSB::OBBData();
		OBBData obb2Data = obb2->operator SSB::OBBData();
		return kDefaultCollisionCalculator.IsCollide(obb1Data, obb2Data);
	}
	bool OBBToOBBCollisionDetector::IsIn(Volume1* obb1, Volume1* obb2)
	{
		OBBData obb1Data = obb1->operator SSB::OBBData();
		OBBData obb2Data = obb2->operator SSB::OBBData();
		return kDefaultCollisionCalculator.IsIn(obb1Data, obb2Data);
	}
	std::vector<Vector3> OBBToOBBCollisionDetector::GetIntersections(Volume1* obb1, Volume1* obb2)
	{
		OBBData obb1Data = obb1->operator SSB::OBBData();
		OBBData obb2Data = obb2->operator SSB::OBBData();
		return kDefaultCollisionCalculator.GetIntersections(obb1Data, obb2Data);
	}
	bool SphereToTriangleCollisionDetector::IsCollide(Volume1* sphere, Volume1* triangle)
	{
		SphereData sphereData = sphere->operator SSB::SphereData();
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			if (kDefaultCollisionCalculator.IsCollide(sphereData, triangleData))
			{
				return true;
			}
		}
		return false;
	}

	bool SphereToTriangleCollisionDetector::IsIn(Volume1* sphere, Volume1* triangle)
	{
		SphereData sphereData = sphere->operator SSB::SphereData();
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			if (kDefaultCollisionCalculator.IsIn(sphereData, triangleData))
			{
				return true;
			}
		}
		return false;
	}

	std::vector<Vector3> SphereToTriangleCollisionDetector::GetIntersections(Volume1* sphere, Volume1* triangle)
	{
		std::vector<Vector3> ret;
		SphereData sphereData = sphere->operator SSB::SphereData();
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			std::vector<Vector3> tmp = kDefaultCollisionCalculator.GetIntersections(sphereData, triangleData);
			ret.insert(ret.end(), tmp.begin(), tmp.end());
		}
		return ret;
	}

	bool SphereToAABBCollisionDetector::IsCollide(Volume1* sphere, Volume1* aabb)
	{
		SphereData sphereData = sphere->operator SSB::SphereData();
		AABBData aabbData = aabb->operator SSB::AABBData();
		return kDefaultCollisionCalculator.IsCollide(sphereData, aabbData);
	}

	bool SphereToAABBCollisionDetector::IsIn(Volume1* sphere, Volume1* aabb)
	{
		SphereData sphereData = sphere->operator SSB::SphereData();
		AABBData aabbData = aabb->operator SSB::AABBData();
		return kDefaultCollisionCalculator.IsIn(sphereData, aabbData);
	}

	std::vector<Vector3> SphereToAABBCollisionDetector::GetIntersections(Volume1* sphere, Volume1* aabb)
	{
		SphereData sphereData = sphere->operator SSB::SphereData();
		AABBData aabbData = aabb->operator SSB::AABBData();
		return kDefaultCollisionCalculator.GetIntersections(sphereData, aabbData);
	}

	bool OBBToSphereCollisionDetector::IsCollide(Volume1* obb, Volume1* sphere)
	{
		OBBData obbData = obb->operator SSB::OBBData();
		SphereData sphereData = sphere->operator SSB::SphereData();
		return kDefaultCollisionCalculator.IsCollide(obbData, sphereData);
	}

	bool OBBToSphereCollisionDetector::IsIn(Volume1* obb, Volume1* sphere)
	{
		OBBData obbData = obb->operator SSB::OBBData();
		SphereData sphereData = sphere->operator SSB::SphereData();
		return kDefaultCollisionCalculator.IsIn(obbData, sphereData);
	}

	std::vector<Vector3> OBBToSphereCollisionDetector::GetIntersections(Volume1* obb, Volume1* sphere)
	{
		OBBData obbData = obb->operator SSB::OBBData();
		SphereData sphereData = sphere->operator SSB::SphereData();
		return kDefaultCollisionCalculator.GetIntersections(obbData, sphereData);
	}

	bool SphereToOBBCollisionDetector::IsCollide(Volume1* sphere, Volume1* obb)
	{
		SphereData sphereData = sphere->operator SSB::SphereData();
		OBBData obbData = obb->operator SSB::OBBData();
		return kDefaultCollisionCalculator.IsCollide(sphereData, obbData);
	}

	bool SphereToOBBCollisionDetector::IsIn(Volume1* sphere, Volume1* obb)
	{
		SphereData sphereData = sphere->operator SSB::SphereData();
		OBBData obbData = obb->operator SSB::OBBData();
		return kDefaultCollisionCalculator.IsIn(sphereData, obbData);
	}

	std::vector<Vector3> SphereToOBBCollisionDetector::GetIntersections(Volume1* sphere, Volume1* obb)
	{
		SphereData sphereData = sphere->operator SSB::SphereData();
		OBBData obbData = obb->operator SSB::OBBData();
		return kDefaultCollisionCalculator.GetIntersections(sphereData, obbData);
	}
}