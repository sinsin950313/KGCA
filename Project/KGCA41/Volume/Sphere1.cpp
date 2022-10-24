#include "Sphere1.h"

namespace SSB
{
	//Sphere::SphereCollideDelegate::SphereCollideDelegate(Sphere* owner) : CollideCheckDelegate(owner)
	//{
	//}
	//bool Sphere::SphereCollideDelegate::IsCollide(PlaneData data)
	//{
	//	Sphere* owner = (Sphere*)GetOwner();
	//	auto center = owner->GetMatrix().GetRow(3);
	//	float distance = data.A * center.GetX() + data.B * center.GetY() + data.C * center.GetZ() + data.D;
	//	return  abs(distance) < owner->_radius;
	//}
	//bool Sphere::SphereCollideDelegate::IsCollide(BoxData boxData)
	//{
	//	Sphere* owner = (Sphere*)GetOwner();
	//	auto center = owner->GetMatrix().GetRow(3);
	//	for (int i = 0; i < 6; ++i)
	//	{
	//		PlaneData data = boxData.Plane[i];
	//		float distance = data.A * center.GetX() + data.B * center.GetY() + data.C * center.GetZ() + data.D;
	//		if (distance - owner->_radius > 0)
	//		{
	//			return false;
	//		}
	//	}
	//	return true;
	//}
	//bool Sphere::SphereCollideDelegate::IsCollide(SphereData sphereData)
	//{
	//	Sphere* owner = (Sphere*)GetOwner();
	//	Vector3 ownerPosition = owner->GetMatrix().GetRow(3);
	//	Vector3 targetPosition = sphereData.Matrix.GetRow(3);
	//	float length = (ownerPosition - targetPosition).Length();
	//	return length <= (owner->_radius + sphereData.Radius);
	//}
	//bool Sphere::SphereCollideDelegate::IsCollide(FrustumData frustumData)
	//{
	//	Sphere* owner = (Sphere*)GetOwner();
	//	auto center = owner->GetMatrix().GetRow(3);
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
	//Sphere::Sphere(float radius, HMatrix44 matrix) : Volume1(new SphereCollideDelegate(this), matrix)
	//{
	//	_radius = radius;
	//}
	//Sphere::operator SphereData()
	//{
	//	//return SphereData{GetMatrix(), _radius};
	//}
}
