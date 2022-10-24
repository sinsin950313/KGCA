#include "Plane1.h"

namespace SSB
{
	//SSB::Plane::PlaneCollideDelegate::PlaneCollideDelegate(Plane* owner) : CollideCheckDelegate(owner)
	//{
	//}
	//
	//float SSB::Plane::PlaneCollideDelegate::GetDistance(Vector3 point)
	//{
	//	Plane* owner = (Plane*)GetOwner();
	//	return owner->_data.A * point.GetX() + owner->_data.B * point.GetY() + owner->_data.C * point.GetZ() + owner->_data.D;
	//}
	//
	//bool SSB::Plane::PlaneCollideDelegate::IsCollide(PlaneData planeData)
	//{
	//	Plane* owner = (Plane*)GetOwner();
	//	if (IsZero(owner->_data.A - planeData.A) && IsZero(owner->_data.B - planeData.B) && IsZero(owner->_data.C - planeData.C))
	//	{
	//		if (IsZero(owner->_data.D - planeData.D))
	//		{
	//			return true;
	//		}
	//		else
	//		{
	//			return false;
	//		}
	//	}
	//	return true;
	//}
	//
	//bool SSB::Plane::PlaneCollideDelegate::IsCollide(BoxData boxData)
	//{
	//	// Need to more Check
	//	return true;
	//}
	//
	//bool SSB::Plane::PlaneCollideDelegate::IsCollide(SphereData sphereData)
	//{
	//	Plane* owner = (Plane*)GetOwner();
	//	float distance = GetDistance(sphereData.Matrix.GetRow(3));
	//	float radius = sphereData.Radius;
	//	return abs(distance) < radius;
	//}
	//
	//bool SSB::Plane::PlaneCollideDelegate::IsCollide(FrustumData frustum)
	//{
	//	// Need to more check
	//	return true;
	//}
	//
	//SSB::Plane::Plane(Vector3 normal, Vector3 point) : Volume1(new PlaneCollideDelegate(this))
	//{
	//	normal.Normalize();
	//	_data.A = normal.GetX();
	//	_data.B = normal.GetY();
	//	_data.C = normal.GetZ();
	//	_data.D = -(normal.GetX() * point.GetX() + normal.GetY() * point.GetY() + normal.GetZ() * point.GetZ());
	//}
	//
	//SSB::Plane::operator PlaneData()
	//{
	//	//return _data;
	//}
}
