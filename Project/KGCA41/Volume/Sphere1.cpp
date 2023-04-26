#include "Sphere1.h"
#include "Common.h"

namespace SSB
{
	Sphere1Volume::SphereCollideDelegate::SphereCollideDelegate(Sphere1Volume* owner) : CollideCheckDelegate(owner)
	{
	}
	//bool Sphere1Volume::SphereCollideDelegate::IsCollide(PlaneData data)
	//{
	//	Sphere1Volume* owner = (Sphere1Volume*)GetOwner();
	//	Vector3 center = owner->GetPosition();
	//	Vector3 planeCenter = data.Position;
	//	Vector3 vec = center - planeCenter;

	//	float radius = ((SphereData)*owner).Radius;
	//	if (vec.Length() < radius)
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		float distance = data.A * center.GetX() + data.B * center.GetY() + data.C * center.GetZ() + data.D;
	//		if (distance < radius)
	//		{
	//			// make Sphere1Volume to circle at plane space
	//			// make it checking collision with rectangle and circle problem
	//			// check projection length at each rectangle axis with circle center position
	//			implement;
	//		}
	//	}
	//	return false;
	//}
	bool Sphere1Volume::SphereCollideDelegate::IsCollide(BoxData boxData)
	{
		Sphere1Volume* owner = (Sphere1Volume*)GetOwner();
		auto center = owner->GetPosition();

		for (int i = 0; i < 6; ++i)
		{
			FaceData data = boxData.Plane[i];
			float distance = data.A * center.GetX() + data.B * center.GetY() + data.C * center.GetZ() + data.D;
			if (distance - owner->GetRadius() > 0)
			{
				return false;
			}
		}
		return true;
	}
	bool Sphere1Volume::SphereCollideDelegate::IsCollide(SphereData sphereData)
	{
		Sphere1Volume* owner = (Sphere1Volume*)GetOwner();
		Vector3 ownerPosition = owner->GetPosition();
		Vector3 targetPosition = sphereData.Position;
		float length = (ownerPosition - targetPosition).Length();
		return length <= (owner->GetRadius() + sphereData.Radius);
	}
	bool Sphere1Volume::SphereCollideDelegate::IsIn(BoxData data)
	{
		for(int i = 0; i < sizeof(data.Vertices) / sizeof(data.Vertices[0]); ++i)
		{
			Vector3 vertex = data.Vertices[i];
			Vector3 center = ((Sphere1Volume*)GetOwner())->GetPosition();
			Vector3 distance = vertex - center;
			if (((Sphere1Volume*)GetOwner())->GetRadius() < distance.Length())
			{
				return false;
			}
		}
		return true;
	}
	bool Sphere1Volume::SphereCollideDelegate::IsIn(SphereData data)
	{
		Sphere1Volume* owner = (Sphere1Volume*)GetOwner();
		Vector3 ownerPosition = owner->GetPosition();
		Vector3 targetPosition = data.Position;
		float length = (ownerPosition - targetPosition).Length();

		return length < owner->GetRadius();
	}
	//bool Sphere1Volume::SphereCollideDelegate::IsCollide(FrustumData frustumData)
	//{
	//	Sphere1Volume* owner = (Sphere1Volume*)GetOwner();
	//	auto center = owner->GetPosition();
	//	for (int i = 0; i < 6; ++i)
	//	{
	//		PlaneData data = frustumData.Plane[i];
	//		float distance = data.A * center.GetX() + data.B * center.GetY() + data.C * center.GetZ() + data.D;
	//		if (distance - owner->_radius > 0)
	//		{
	//			return false;
	//		}
	//	}
	//	return true;
	//}
	Sphere1Volume::Sphere1Volume(float radius) : Volume1(new SphereCollideDelegate(this))
	{
		SetScale(radius, 0, 0);
	}
	float Sphere1Volume::GetRadius()
	{
		auto scale = GetScale();
		return sqrt(scale.GetX() * scale.GetX() + scale.GetY() * scale.GetY() + scale.GetZ() * scale.GetZ());
	}
	//void Sphere1Volume::Resize(float width, float height, float depth)
	//{
	//	_radius = sqrt(width * width + height * height + depth * depth);
	//}
	Sphere1Volume::operator SphereData()
	{
		return SphereData{GetPosition(), GetRotation(), GetScale(), GetRadius()};
	}
}
