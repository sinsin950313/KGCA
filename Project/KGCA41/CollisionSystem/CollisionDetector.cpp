#include "CollisionDetector.h"
#include "CollisionCalculator.h"
#include "Line1.h"
#include "Sphere1.h"

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
}