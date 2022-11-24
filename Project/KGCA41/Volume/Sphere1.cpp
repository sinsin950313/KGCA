#include "Sphere1.h"
#include "Common.h"

namespace SSB
{
	Sphere::SphereCollideDelegate::SphereCollideDelegate(Sphere* owner) : CollideCheckDelegate(owner)
	{
	}
	//bool Sphere::SphereCollideDelegate::IsCollide(PlaneData data)
	//{
	//	Sphere* owner = (Sphere*)GetOwner();
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
	//			// make sphere to circle at plane space
	//			// make it checking collision with rectangle and circle problem
	//			// check projection length at each rectangle axis with circle center position
	//			implement;
	//		}
	//	}
	//	return false;
	//}
	bool Sphere::SphereCollideDelegate::IsCollide(BoxData boxData)
	{
		Sphere* owner = (Sphere*)GetOwner();
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
	bool Sphere::SphereCollideDelegate::IsCollide(SphereData sphereData)
	{
		Sphere* owner = (Sphere*)GetOwner();
		Vector3 ownerPosition = owner->GetPosition();
		Vector3 targetPosition = sphereData.Position;
		float length = (ownerPosition - targetPosition).Length();
		return length <= (owner->GetRadius() + sphereData.Radius);
	}
	//bool Sphere::SphereCollideDelegate::IsCollide(FrustumData frustumData)
	//{
	//	Sphere* owner = (Sphere*)GetOwner();
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
	Sphere::Sphere(float radius) : Volume1(new SphereCollideDelegate(this))
	{
		SetScale(radius, 0, 0);
	}
	float Sphere::GetRadius()
	{
		auto scale = GetScale();
		return sqrt(scale.GetX() * scale.GetX() + scale.GetY() * scale.GetY() + scale.GetZ() * scale.GetZ());
	}
	//void Sphere::Resize(float width, float height, float depth)
	//{
	//	_radius = sqrt(width * width + height * height + depth * depth);
	//}
	Sphere::operator SphereData()
	{
		return SphereData{GetPosition(), GetRotation(), GetScale(), GetRadius()};
	}
}
