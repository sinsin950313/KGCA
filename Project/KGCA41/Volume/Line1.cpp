#include "Line1.h"
#include <limits>
#include "HCCalculator.h"

namespace SSB
{
	Line1Volume::Line1Volume(Vector3 vertex, Vector3 direction)
	{
		SetPosition(vertex);
		LookAt(direction);
	}
	Vector3 Line1Volume::GetDirection(Matrix33 rotation)
	{
		return rotation.GetRow(0);
	}
	Vector3 Line1Volume::GetWorldDirection()
	{
		return GetDirection(GetWorldRotation());
	}
	Vector3 Line1Volume::GetLocalDirection()
	{
		return GetDirection(GetLocalRotation());
	}
	Line1Volume::operator LineData()
	{
		return LineData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			GetWorldPosition(), GetWorldDirection()
		};
	}
	Line1Volume::operator SphereData()
	{
		return SphereData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			std::numeric_limits<float>::max()
		};
	}
	Ray1Volume::Ray1Volume(Vector3 origin, Vector3 dir) : Line1Volume(origin, dir)
	{
	}
	Ray1Volume::operator RayData()
	{
		return RayData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			GetWorldPosition(), GetWorldDirection()
		};
	}
	Ray1Volume::operator SphereData()
	{
		return SphereData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			std::numeric_limits<float>::max()
		};
	}
	Segment1Volume::Segment1Volume(Vector3 leftVertex, Vector3 rightVertex)
	{
		Vector3 center = (leftVertex + rightVertex) / 2;
		SetPosition(center);

		Vector3 rightDirection = rightVertex - center;
		rightDirection.Normalize();
		Vector3 upDirection{ 0, 1, 0 };
		{
			Vector3 tmp = rightDirection;
			if (abs(tmp.GetY()) == upDirection.GetY())
			{
				upDirection = { -1, 0, 0 };
			}
		}
		Vector3 forwardDirection = upDirection.Cross(rightDirection);
		LookAt(forwardDirection);

		SetScale((rightVertex - center).Length(), 1, 1);
	}
	float Segment1Volume::GetLength(Vector3 scale)
	{
		return scale.GetX() * 2;
	}
	Vector3 Segment1Volume::GetLeftVertex(Vector3 center, Matrix33 rotation, Vector3 scale)
	{
		Vector3 leftDirection = rotation.GetRow(0) * -1 * scale.GetX();
		return center + leftDirection;
	}
	Vector3 Segment1Volume::GetRightVertex(Vector3 center, Matrix33 rotation, Vector3 scale)
	{
		Vector3 rightDirection = rotation.GetRow(0) * 1 * scale.GetX();
		return center + rightDirection;
	}
	float Segment1Volume::GetWorldLength()
	{
		return GetLength(GetWorldScale());
	}
	float Segment1Volume::GetLocalLength()
	{
		return GetLength(GetLocalScale());
	}
	Vector3 Segment1Volume::GetWorldLeftVertex()
	{
		return GetLeftVertex(GetWorldPosition(), GetWorldRotation(), GetWorldScale());
	}
	Vector3 Segment1Volume::GetWorldRightVertex()
	{
		return GetRightVertex(GetWorldPosition(), GetWorldRotation(), GetWorldScale());
	}
	Vector3 Segment1Volume::GetLocalLeftVertex()
	{
		return GetLeftVertex(GetLocalPosition(), GetLocalRotation(), GetLocalScale());
	}
	Vector3 Segment1Volume::GetLocalRightVertex()
	{
		return GetRightVertex(GetLocalPosition(), GetLocalRotation(), GetLocalScale());
	}
	Segment1Volume::operator SegmentData()
	{
		return SegmentData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			GetWorldLeftVertex(), GetWorldRightVertex()
		};
	}
	Segment1Volume::operator SphereData()
	{
		return SphereData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			GetWorldLength() / 2
		};
	}
}
