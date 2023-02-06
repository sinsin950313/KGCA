#include "VolumeFactory.h"
#include "CollisionTree1.h"
#include "Line1.h"

namespace SSB
{
	extern CollisionTree1* kCollisionSystem;

	VolumeFactoryInterface::VolumeFactoryInterface(VolumeType fromType, std::vector<DetectorRegisterData> registerData)
	{
		for(auto data : registerData)
		{
			kCollisionSystem->Register(fromType, data.Detector, data.ToType);
		}
	}
	CollisionSystemVolume* VolumeFactoryInterface::New()
	{
		return new CollisionSystemVolume(GetType(), Create(), true);
	}

	RayVolumeFactory::RayVolumeFactory() : VolumeFactoryInterface(Ray, {
			{ new RayToSphereCollisionDetector, Sphere},
			{ new RayToTriangleCollisionDetector, Triangle},
			{ new RayToAABBCollisionDetector, AABB},
			{ new RayToOBBCollisionDetector, OBB} })
	{
	}

	void RayVolumeFactory::Set(Vector3 origin, Vector3 direction)
	{
		_origin = origin;
		_direction = direction;
	}
	Volume1* RayVolumeFactory::Create()
	{
		return new Ray1Volume(_origin, _direction);
	}
	VolumeType RayVolumeFactory::GetType()
	{
		return Ray;
	}
	AABBVolumeFactory::AABBVolumeFactory() : VolumeFactoryInterface(AABB, {
		{ new AABBToTriangleCollisionDetector, Triangle},
		{ new AABBToOBBCollisionDetector, OBB},
		{ new AABBToSphereCollisionDetector, Sphere}
		})
	{
	}
	void AABBVolumeFactory::Set(float width, float height, float depth)
	{
		_width = width;
		_height = height;
		_depth = depth;
	}
	Volume1* AABBVolumeFactory::Create()
	{
		return new AABB1Volume(_width, _height, _depth);
	}
	VolumeType AABBVolumeFactory::GetType()
	{
		return AABB;
	}
}
