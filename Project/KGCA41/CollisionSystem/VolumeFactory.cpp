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

	RayVolumeFactory::RayVolumeFactory() : VolumeFactoryInterface(Ray, { {new RayToSphereCollisionDetector, Sphere} })
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
}
