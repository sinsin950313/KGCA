#include "Sphere1.h"
#include "Common.h"

namespace SSB
{
	Sphere1Volume::Sphere1Volume(float radius)
	{
		SetScale(radius, 0, 0);
	}
	float Sphere1Volume::GetRadius(Vector3 scale)
	{
		return sqrt(scale.GetX() * scale.GetX() + scale.GetY() * scale.GetY() + scale.GetZ() * scale.GetZ());
	}
	float Sphere1Volume::GetWorldRadius()
	{
		return GetRadius(GetWorldScale());
	}
	float Sphere1Volume::GetLocalRadius()
	{
		return GetRadius(GetLocalScale());
	}
	Sphere1Volume::operator SphereData()
	{
		return SphereData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(), 
			GetWorldRadius()
		};
	}
	Sphere1Volume::operator AABBData()
	{
		auto center = GetWorldPosition();
		auto radius = GetWorldRadius();
		Vector3 minVector{ -radius, -radius, -radius };
		Vector3 maxVector{ radius, radius, radius };

		return AABBData{
			center, GetWorldRotation(), GetWorldScale(),
			center + minVector,
			center + maxVector
		};
	}
	Sphere1Volume::operator OBBData()
	{
		float radius = GetWorldRadius();
		return OBBData{ 
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(), 
			radius * 2, radius * 2, radius * 2 
		};
	}
}
