#include "VolumeFactory.h"
#include "CollisionTree1.h"
#include "Line1.h"
#include "Sphere1.h"
#include "Box1.h"

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
	BoxVolumeFactory::BoxVolumeFactory() : VolumeFactoryInterface(AABB, {
		{ new AABBToTriangleCollisionDetector, Triangle},
		{ new AABBToOBBCollisionDetector, OBB},
		{ new AABBToSphereCollisionDetector, Sphere}
		})
	{
	}
	void BoxVolumeFactory::Set(float width, float height, float depth)
	{
		_width = width;
		_height = height;
		_depth = depth;
	}
	Volume1* BoxVolumeFactory::Create()
	{
		return new Box1Volume(_width, _height, _depth);
	}
	VolumeType BoxVolumeFactory::GetType()
	{
		return Box;
	}
	SphereVolumeFactory::SphereVolumeFactory() : VolumeFactoryInterface(Sphere, {
		{ new SphereToAABBCollisionDetector, AABB},
		{ new SphereToOBBCollisionDetector, OBB},
		{ new SphereToSphereCollisionDetector, Sphere},
		{ new SphereToTriangleCollisionDetector, Triangle}
		})
	{
	}
	void SphereVolumeFactory::Set(float radius)
	{
		_radius = radius;
	}
	Volume1* SphereVolumeFactory::Create()
	{
		return new Sphere1Volume(_radius);
	}
	VolumeType SphereVolumeFactory::GetType()
	{
		return Sphere;
	}
}
