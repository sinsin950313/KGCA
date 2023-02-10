#include "VolumeFactory.h"
#include "CollisionTree1.h"
#include "Line1.h"
#include "Sphere1.h"
#include "Box1.h"

namespace SSB
{
	extern CollisionTree1* kCollisionSystem;

	VolumeFactoryInterface::VolumeFactoryInterface(std::vector<DetectorRegisterData> registerData)
	{
		for(auto data : registerData)
		{
			kCollisionSystem->Register(data.FromType, data.Detector, data.ToType);
		}
	}
	CollisionSystemVolume* VolumeFactoryInterface::New()
	{
		return new CollisionSystemVolume(GetType(), Create(), true);
	}

	RayVolumeFactory::RayVolumeFactory() : VolumeFactoryInterface({
		{ RayType, new RayToSphereCollisionDetector, SphereType},
		//{ RayType, new RayToAABBCollisionDetector, AABBType},
		//{ RayType, new RayToOBBCollisionDetector, OBBType},
		{ RayType, new RayToTriangleCollisionDetector, TriangleType},
		})
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
		return RayType;
	}
	BoxVolumeFactory::BoxVolumeFactory() : VolumeFactoryInterface({
		//{ AABBType, new AABBToSphereCollisionDetector, SphereType},
		{ AABBType, new AABBToAABBCollisionDetector, AABBType},
		//{ AABBType, new AABBToOBBCollisionDetector, OBBType},
		//{ AABBType, new AABBToTriangleCollisionDetector, TriangleType},

		//{ OBBType, new OBBToSphereCollisionDetector, SphereType},
		//{ OBBType, new OBBToAABBCollisionDetector, AABBType},
		{ OBBType, new OBBToOBBCollisionDetector, OBBType},
		//{ OBBType, new OBBToTriangleCollisionDetector, TriangleType},

		// For custom volume collision detector part
		{ BoxType, new BoxToSphereCollisionDetector, SphereType},
		{ BoxType, new BoxToRayCollisionDetector, RayType},
		{ BoxType, new BoxToBoxCollisionDetector, BoxType},
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
		return BoxType;
	}
	SphereVolumeFactory::SphereVolumeFactory() : VolumeFactoryInterface({
		{ SphereType, new SphereToSphereCollisionDetector, SphereType},
		//{ SphereType, new SphereToAABBCollisionDetector, AABBType},
		//{ SphereType, new SphereToOBBCollisionDetector, OBBType},
		//{ SphereType, new SphereToTriangleCollisionDetector, TriangleType}
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
		return SphereType;
	}
	CollisionSystemRayVolume::operator RayData()
	{
		return ((Ray1Volume*)_volume)->operator SSB::RayData();
	}
}
