#include "CollisionDetector.h"
#include "CollisionCalculator.h"
#include "Line1.h"
#include "CollisionTree1.h"

namespace SSB
{
	DefaultCollisionCalculator kDefaultCollisionCalculator;

	bool RayToSphereCollisionDetector::IsCollide(CollisionSystemVolume* ray, CollisionSystemVolume* sphere)
	{
		RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
		SphereData sphereData = sphere->operator SSB::SphereData();
		return kDefaultCollisionCalculator.IsCollide(rayData, sphereData);
	}
	bool RayToSphereCollisionDetector::IsIn(CollisionSystemVolume* ray, CollisionSystemVolume* sphere)
	{
		RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
		SphereData sphereData = sphere->operator SSB::SphereData();
		return kDefaultCollisionCalculator.IsIn(rayData, sphereData);
	}
	std::vector<Vector3> RayToSphereCollisionDetector::GetIntersections(CollisionSystemVolume* ray, CollisionSystemVolume* sphere)
	{
		RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
		SphereData sphereData = sphere->operator SSB::SphereData();
		return { kDefaultCollisionCalculator.GetIntersections(rayData, sphereData) };
	}
	bool RayToTriangleCollisionDetector::IsCollide(CollisionSystemVolume* ray, CollisionSystemVolume* triangle)
	{
		RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
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
	bool RayToTriangleCollisionDetector::IsIn(CollisionSystemVolume* ray, CollisionSystemVolume* triangle)
	{
		RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
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
	std::vector<Vector3> RayToTriangleCollisionDetector::GetIntersections(CollisionSystemVolume* ray, CollisionSystemVolume* triangle)
	{
		std::vector<Vector3> ret;
		RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
		std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
		for (auto triangleData : triangles)
		{
			std::vector<Vector3> tmp = kDefaultCollisionCalculator.GetIntersections(rayData, triangleData);
			ret.insert(ret.end(), tmp.begin(), tmp.end());
		}
		return ret;
	}
	//bool RayToAABBCollisionDetector::IsCollide(CollisionSystemVolume* ray, CollisionSystemVolume* aabb)
	//{
	//	RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
	//	AABBData aabbData = aabb->operator SSB::AABBData();
	//	return kDefaultCollisionCalculator.IsCollide(rayData, aabbData);
	//}
	//bool RayToAABBCollisionDetector::IsIn(CollisionSystemVolume* ray, CollisionSystemVolume* aabb)
	//{
	//	RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
	//	AABBData aabbData = aabb->operator SSB::AABBData();
	//	return kDefaultCollisionCalculator.IsIn(rayData, aabbData);
	//}
	//std::vector<Vector3> RayToAABBCollisionDetector::GetIntersections(CollisionSystemVolume* ray, CollisionSystemVolume* aabb)
	//{
	//	RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
	//	AABBData aabbData = aabb->operator SSB::AABBData();
	//	return { kDefaultCollisionCalculator.GetIntersections(rayData, aabbData) };
	//}
	//bool RayToOBBCollisionDetector::IsCollide(CollisionSystemVolume* ray, CollisionSystemVolume* obb)
	//{
	//	RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
	//	OBBData obbData = obb->operator SSB::OBBData();
	//	return kDefaultCollisionCalculator.IsCollide(rayData, obbData);
	//}
	//bool RayToOBBCollisionDetector::IsIn(CollisionSystemVolume* ray, CollisionSystemVolume* obb)
	//{
	//	RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
	//	OBBData obbData = obb->operator SSB::OBBData();
	//	return kDefaultCollisionCalculator.IsIn(rayData, obbData);
	//}
	//std::vector<Vector3> RayToOBBCollisionDetector::GetIntersections(CollisionSystemVolume* ray, CollisionSystemVolume* obb)
	//{
	//	RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
	//	OBBData obbData = obb->operator SSB::OBBData();
	//	return { kDefaultCollisionCalculator.GetIntersections(rayData, obbData) };
	//}
	//bool AABBToTriangleCollisionDetector::IsCollide(CollisionSystemVolume* aabb, CollisionSystemVolume* triangle)
	//{
	//	//AABBData rayData = aabb->operator SSB::AABBData();
	//	//std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
	//	//for (auto triangleData : triangles)
	//	//{
	//	//	if (kDefaultCollisionCalculator.IsCollide(rayData, triangleData))
	//	//	{
	//	//		return true;
	//	//	}
	//	//}
	//	return false;
	//}
	//bool AABBToTriangleCollisionDetector::IsIn(CollisionSystemVolume* aabb, CollisionSystemVolume* triangle)
	//{
	//	//AABBData aabbData = aabb->operator SSB::AABBData();
	//	//std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
	//	//for (auto triangleData : triangles)
	//	//{
	//	//	if (kDefaultCollisionCalculator.IsIn(aabbData, triangleData))
	//	//	{
	//	//		return true;
	//	//	}
	//	//}
	//	return false;
	//}
	//std::vector<Vector3> AABBToTriangleCollisionDetector::GetIntersections(CollisionSystemVolume* aabb, CollisionSystemVolume* triangle)
	//{
	//	std::vector<Vector3> ret;
	//	//AABBData aabbData = *(Ray1Volume*)aabb;
	//	//std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
	//	//for (auto triangleData : triangles)
	//	//{
	//	//	std::vector<Vector3> tmp = kDefaultCollisionCalculator.GetIntersections(aabbData, triangleData);
	//	//	ret.insert(ret.end(), tmp.begin(), tmp.end());
	//	//}
	//	return ret;
	//}
	//bool AABBToOBBCollisionDetector::IsCollide(CollisionSystemVolume* aabb, CollisionSystemVolume* obb)
	//{
	//	AABBData aabbData = aabb->operator SSB::AABBData();
	//	OBBData obbData = obb->operator SSB::OBBData();
	//	return kDefaultCollisionCalculator.IsCollide(aabbData, obbData);
	//}
	//bool AABBToOBBCollisionDetector::IsIn(CollisionSystemVolume* aabb, CollisionSystemVolume* obb)
	//{
	//	AABBData aabbData = aabb->operator SSB::AABBData();
	//	OBBData obbData = obb->operator SSB::OBBData();
	//	return kDefaultCollisionCalculator.IsIn(aabbData, obbData);
	//}
	//std::vector<Vector3> AABBToOBBCollisionDetector::GetIntersections(CollisionSystemVolume* aabb, CollisionSystemVolume* obb)
	//{
	//	//AABBData aabbData = aabb->operator SSB::AABBData();
	//	//OBBData obbData = obb->operator SSB::OBBData();
	//	//return { kDefaultCollisionCalculator.GetIntersections(aabbData, obbData) };
	//	return std::vector<Vector3>();
	//}
	//bool AABBToSphereCollisionDetector::IsCollide(CollisionSystemVolume* aabb, CollisionSystemVolume* sphere)
	//{
	//	AABBData aabbData = aabb->operator SSB::AABBData();
	//	SphereData sphereData = *(SphereData*)sphere;
	//	return kDefaultCollisionCalculator.IsCollide(aabbData, sphereData);
	//}
	//bool AABBToSphereCollisionDetector::IsIn(CollisionSystemVolume* aabb, CollisionSystemVolume* sphere)
	//{
	//	AABBData aabbData = aabb->operator SSB::AABBData();
	//	SphereData sphereData = *(SphereData*)sphere;
	//	return kDefaultCollisionCalculator.IsIn(aabbData, sphereData);
	//}
	//std::vector<Vector3> AABBToSphereCollisionDetector::GetIntersections(CollisionSystemVolume* aabb, CollisionSystemVolume* sphere)
	//{
	//	//AABBData aabbData = aabb->operator SSB::AABBData();
	//	//SphereData sphereData = sphere->operator SSB::SphereData();
	//	//return { kDefaultCollisionCalculator.GetIntersections(aabbData, sphereData) };
	//	return std::vector<Vector3>();
	//}
	bool AABBToAABBCollisionDetector::IsCollide(CollisionSystemVolume* aabb1, CollisionSystemVolume* aabb2)
	{
		AABBData aabb1Data = aabb1->operator SSB::AABBData();
		AABBData aabb2Data = aabb2->operator SSB::AABBData();
		return kDefaultCollisionCalculator.IsCollide(aabb1Data, aabb2Data);
	}
	bool AABBToAABBCollisionDetector::IsIn(CollisionSystemVolume* aabb1, CollisionSystemVolume* aabb2)
	{
		AABBData aabb1Data = aabb1->operator SSB::AABBData();
		AABBData aabb2Data = aabb2->operator SSB::AABBData();
		return kDefaultCollisionCalculator.IsIn(aabb1Data, aabb2Data);
	}
	std::vector<Vector3> AABBToAABBCollisionDetector::GetIntersections(CollisionSystemVolume* aabb1, CollisionSystemVolume* aabb2)
	{
		//AABBData aabb1Data = aabb1->operator SSB::AABBData();
		//AABBData aabb2Data = aabb2->operator SSB::AABBData();
		//return kDefaultCollisionCalculator.GetIntersections(aabb1Data, aabb2Data);
		return std::vector<Vector3>();
	}
	bool SphereToSphereCollisionDetector::IsCollide(CollisionSystemVolume* sphere1, CollisionSystemVolume* sphere2)
	{
		SphereData sphere1Data = sphere1->operator SSB::SphereData();
		SphereData sphere2Data = sphere2->operator SSB::SphereData();
		return kDefaultCollisionCalculator.IsCollide(sphere1Data, sphere2Data);
	}
	bool SphereToSphereCollisionDetector::IsIn(CollisionSystemVolume* sphere1, CollisionSystemVolume* sphere2)
	{
		SphereData sphere1Data = sphere1->operator SSB::SphereData();
		SphereData sphere2Data = sphere2->operator SSB::SphereData();
		return kDefaultCollisionCalculator.IsIn(sphere1Data, sphere2Data);
	}
	std::vector<Vector3> SphereToSphereCollisionDetector::GetIntersections(CollisionSystemVolume* sphere1, CollisionSystemVolume* sphere2)
	{
		//SphereData sphere1Data = sphere1->operator SSB::SphereData();
		//SphereData sphere2Data = sphere2->operator SSB::SphereData();
		//return kDefaultCollisionCalculator.GetIntersections(sphere1Data, sphere2Data);
		return std::vector<Vector3>();
	}
	//bool OBBToTriangleCollisionDetector::IsCollide(CollisionSystemVolume* obb, CollisionSystemVolume* triangle)
	//{
	//	//OBBData obbData = obb->operator SSB::OBBData();
	//	//std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
	//	//for (auto triangleData : triangles)
	//	//{
	//	//	if (kDefaultCollisionCalculator.IsCollide(obbData, triangleData))
	//	//	{
	//	//		return true;
	//	//	}
	//	//}
	//	return false;
	//}

	//bool OBBToTriangleCollisionDetector::IsIn(CollisionSystemVolume* obb, CollisionSystemVolume* triangle)
	//{
	//	//OBBData obbData = obb->operator SSB::OBBData();
	//	//std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
	//	//for (auto triangleData : triangles)
	//	//{
	//	//	if (kDefaultCollisionCalculator.IsIn(obbData, triangleData))
	//	//	{
	//	//		return true;
	//	//	}
	//	//}
	//	return false;
	//}

	//std::vector<Vector3> OBBToTriangleCollisionDetector::GetIntersections(CollisionSystemVolume* obb, CollisionSystemVolume* triangle)
	//{
	//	std::vector<Vector3> ret;
	//	//OBBData obbData = obb->operator SSB::OBBData();
	//	//std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
	//	//for (auto triangleData : triangles)
	//	//{
	//	//	std::vector<Vector3> tmp = kDefaultCollisionCalculator.GetIntersections(obbData, triangleData);
	//	//	ret.insert(ret.end(), tmp.begin(), tmp.end());
	//	//}
	//	return ret;
	//}

	//bool OBBToAABBCollisionDetector::IsCollide(CollisionSystemVolume* obb, CollisionSystemVolume* aabb)
	//{
	//	OBBData obbData = obb->operator SSB::OBBData();
	//	AABBData aabbData = aabb->operator SSB::AABBData();
	//	return kDefaultCollisionCalculator.IsCollide(obbData, aabbData);
	//}

	//bool OBBToAABBCollisionDetector::IsIn(CollisionSystemVolume* obb, CollisionSystemVolume* aabb)
	//{
	//	//OBBData obbData = obb->operator SSB::OBBData();
	//	//AABBData aabbData = aabb->operator SSB::AABBData();
	//	//return kDefaultCollisionCalculator.IsIn(obbData, aabbData);
	//	return false;
	//}

	//std::vector<Vector3> OBBToAABBCollisionDetector::GetIntersections(CollisionSystemVolume* obb, CollisionSystemVolume* aabb)
	//{
	//	//OBBData obbData = obb->operator SSB::OBBData();
	//	//AABBData aabbData = aabb->operator SSB::AABBData();
	//	//return kDefaultCollisionCalculator.GetIntersections(obbData, aabbData);
	//	return std::vector<Vector3>();
	//}

	bool OBBToOBBCollisionDetector::IsCollide(CollisionSystemVolume* obb1, CollisionSystemVolume* obb2)
	{
		OBBData obb1Data = obb1->operator SSB::OBBData();
		OBBData obb2Data = obb2->operator SSB::OBBData();
		return kDefaultCollisionCalculator.IsCollide(obb1Data, obb2Data);
	}
	bool OBBToOBBCollisionDetector::IsIn(CollisionSystemVolume* obb1, CollisionSystemVolume* obb2)
	{
		//OBBData obb1Data = obb1->operator SSB::OBBData();
		//OBBData obb2Data = obb2->operator SSB::OBBData();
		//return kDefaultCollisionCalculator.IsIn(obb1Data, obb2Data);
		return false;
	}
	std::vector<Vector3> OBBToOBBCollisionDetector::GetIntersections(CollisionSystemVolume* obb1, CollisionSystemVolume* obb2)
	{
		//OBBData obb1Data = obb1->operator SSB::OBBData();
		//OBBData obb2Data = obb2->operator SSB::OBBData();
		//return kDefaultCollisionCalculator.GetIntersections(obb1Data, obb2Data);
		return std::vector<Vector3>();
	}
	//bool SphereToTriangleCollisionDetector::IsCollide(CollisionSystemVolume* sphere, CollisionSystemVolume* triangle)
	//{
	//	//SphereData sphereData = sphere->operator SSB::SphereData();
	//	//std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
	//	//for (auto triangleData : triangles)
	//	//{
	//	//	if (kDefaultCollisionCalculator.IsCollide(sphereData, triangleData))
	//	//	{
	//	//		return true;
	//	//	}
	//	//}
	//	return false;
	//}

	//bool SphereToTriangleCollisionDetector::IsIn(CollisionSystemVolume* sphere, CollisionSystemVolume* triangle)
	//{
	//	//SphereData sphereData = sphere->operator SSB::SphereData();
	//	//std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
	//	//for (auto triangleData : triangles)
	//	//{
	//	//	if (kDefaultCollisionCalculator.IsIn(sphereData, triangleData))
	//	//	{
	//	//		return true;
	//	//	}
	//	//}
	//	return false;
	//}

	//std::vector<Vector3> SphereToTriangleCollisionDetector::GetIntersections(CollisionSystemVolume* sphere, CollisionSystemVolume* triangle)
	//{
	//	std::vector<Vector3> ret;
	//	//SphereData sphereData = sphere->operator SSB::SphereData();
	//	//std::vector<TriangleData> triangles = triangle->GetWorldBaseTriangles();
	//	//for (auto triangleData : triangles)
	//	//{
	//	//	std::vector<Vector3> tmp = kDefaultCollisionCalculator.GetIntersections(sphereData, triangleData);
	//	//	ret.insert(ret.end(), tmp.begin(), tmp.end());
	//	//}
	//	return ret;
	//}

	//bool SphereToAABBCollisionDetector::IsCollide(CollisionSystemVolume* sphere, CollisionSystemVolume* aabb)
	//{
	//	SphereData sphereData = sphere->operator SSB::SphereData();
	//	AABBData aabbData = aabb->operator SSB::AABBData();
	//	return kDefaultCollisionCalculator.IsCollide(sphereData, aabbData);
	//}

	//bool SphereToAABBCollisionDetector::IsIn(CollisionSystemVolume* sphere, CollisionSystemVolume* aabb)
	//{
	//	SphereData sphereData = sphere->operator SSB::SphereData();
	//	AABBData aabbData = aabb->operator SSB::AABBData();
	//	return kDefaultCollisionCalculator.IsIn(sphereData, aabbData);
	//}

	//std::vector<Vector3> SphereToAABBCollisionDetector::GetIntersections(CollisionSystemVolume* sphere, CollisionSystemVolume* aabb)
	//{
	//	//SphereData sphereData = sphere->operator SSB::SphereData();
	//	//AABBData aabbData = aabb->operator SSB::AABBData();
	//	//return kDefaultCollisionCalculator.GetIntersections(sphereData, aabbData);
	//	return std::vector<Vector3>();
	//}

	//bool OBBToSphereCollisionDetector::IsCollide(CollisionSystemVolume* obb, CollisionSystemVolume* sphere)
	//{
	//	OBBData obbData = obb->operator SSB::OBBData();
	//	SphereData sphereData = sphere->operator SSB::SphereData();
	//	return kDefaultCollisionCalculator.IsCollide(obbData, sphereData);
	//}

	//bool OBBToSphereCollisionDetector::IsIn(CollisionSystemVolume* obb, CollisionSystemVolume* sphere)
	//{
	//	//OBBData obbData = obb->operator SSB::OBBData();
	//	//SphereData sphereData = sphere->operator SSB::SphereData();
	//	//return kDefaultCollisionCalculator.IsIn(obbData, sphereData);
	//	return false;
	//}

	//std::vector<Vector3> OBBToSphereCollisionDetector::GetIntersections(CollisionSystemVolume* obb, CollisionSystemVolume* sphere)
	//{
	//	//OBBData obbData = obb->operator SSB::OBBData();
	//	//SphereData sphereData = sphere->operator SSB::SphereData();
	//	//return kDefaultCollisionCalculator.GetIntersections(obbData, sphereData);
	//	return std::vector<Vector3>();
	//}

	//bool SphereToOBBCollisionDetector::IsCollide(CollisionSystemVolume* sphere, CollisionSystemVolume* obb)
	//{
	//	//SphereData sphereData = sphere->operator SSB::SphereData();
	//	//OBBData obbData = obb->operator SSB::OBBData();
	//	//return kDefaultCollisionCalculator.IsCollide(sphereData, obbData);
	//	return false;
	//}

	//bool SphereToOBBCollisionDetector::IsIn(CollisionSystemVolume* sphere, CollisionSystemVolume* obb)
	//{
	//	//SphereData sphereData = sphere->operator SSB::SphereData();
	//	//OBBData obbData = obb->operator SSB::OBBData();
	//	//return kDefaultCollisionCalculator.IsIn(sphereData, obbData);
	//	return false;
	//}

bool BoxToBoxCollisionDetector::IsCollide(CollisionSystemVolume* box1, CollisionSystemVolume* box2)
{
	OBBData obb1Data = box1->operator SSB::OBBData();
	OBBData obb2Data = box2->operator SSB::OBBData();
	return kDefaultCollisionCalculator.IsCollide(obb1Data, obb2Data);
}

bool BoxToBoxCollisionDetector::IsIn(CollisionSystemVolume* box1, CollisionSystemVolume* box2)
{
	return false;
}

std::vector<Vector3> BoxToBoxCollisionDetector::GetIntersections(CollisionSystemVolume* box1, CollisionSystemVolume* box2)
{
	return std::vector<Vector3>();
}

bool BoxToRayCollisionDetector::IsCollide(CollisionSystemVolume* box, CollisionSystemVolume* ray)
{
	OBBData obbData = box->operator SSB::OBBData();
	RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
	return kDefaultCollisionCalculator.IsCollide(obbData, rayData);
}

bool BoxToRayCollisionDetector::IsIn(CollisionSystemVolume* box, CollisionSystemVolume* ray)
{
	OBBData obbData = box->operator SSB::OBBData();
	RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
	return kDefaultCollisionCalculator.IsIn(obbData, rayData);
}

std::vector<Vector3> BoxToRayCollisionDetector::GetIntersections(CollisionSystemVolume* box, CollisionSystemVolume* ray)
{
	OBBData obbData = box->operator SSB::OBBData();
	RayData rayData = ((CollisionSystemRayVolume*)ray)->operator SSB::RayData();
	return { kDefaultCollisionCalculator.GetIntersections(obbData, rayData) };
}

bool BoxToSphereCollisionDetector::IsCollide(CollisionSystemVolume* box, CollisionSystemVolume* sphere)
{
	OBBData obbData = box->operator SSB::OBBData();
	SphereData sphereData = sphere->operator SSB::SphereData();
	return kDefaultCollisionCalculator.IsCollide(obbData, sphereData);
}

bool BoxToSphereCollisionDetector::IsIn(CollisionSystemVolume* box, CollisionSystemVolume* sphere)
{
	//OBBData obbData = obb->operator SSB::OBBData();
	//SphereData sphereData = sphere->operator SSB::SphereData();
	//return kDefaultCollisionCalculator.IsIn(obbData, sphereData);
	return false;
}

std::vector<Vector3> BoxToSphereCollisionDetector::GetIntersections(CollisionSystemVolume* box, CollisionSystemVolume* sphere)
{
	//OBBData obbData = obb->operator SSB::OBBData();
	//SphereData sphereData = sphere->operator SSB::SphereData();
	//return kDefaultCollisionCalculator.GetIntersections(obbData, sphereData);
	return std::vector<Vector3>();
}

//std::vector<Vector3> SphereToOBBCollisionDetector::GetIntersections(CollisionSystemVolume* sphere, CollisionSystemVolume* obb)
	//{
	//	//SphereData sphereData = sphere->operator SSB::SphereData();
	//	//OBBData obbData = obb->operator SSB::OBBData();
	//	//return kDefaultCollisionCalculator.GetIntersections(sphereData, obbData);
	//	return std::vector<Vector3>();
	//}
}