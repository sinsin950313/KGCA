#include "Line1.h"
#include <limits>
#include "HCCalculator.h"
#include "Common.h"

namespace SSB
{
	//Line1Volume::Line1Volume(Vector3 vertex, Vector3 direction)
	//{
	//	SetPosition(vertex);
	//	LookAt(direction);
	//}
	//Vector3 Line1Volume::GetDirection(Matrix33 rotation)
	//{
	//	return rotation.GetRow(0);
	//}
	//Vector3 Line1Volume::GetWorldDirection()
	//{
	//	return GetDirection(GetWorldRotation());
	//}
	//Vector3 Line1Volume::GetLocalDirection()
	//{
	//	return GetDirection(GetLocalRotation());
	//}
	//Line1Volume::operator LineData()
	//{
	//	return LineData{
	//		GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
	//		GetWorldPosition(), GetWorldDirection()
	//	};
	//}
	//Line1Volume::operator AABBData()
	//{
	//	auto direction = GetWorldDirection();
	//	float xVal = ZeroFloat(direction.GetX()) ? FDelta : (std::numeric_limits<float>::max)();
	//	float yVal = ZeroFloat(direction.GetY()) ? FDelta : (std::numeric_limits<float>::max)();
	//	float zVal = ZeroFloat(direction.GetZ()) ? FDelta : (std::numeric_limits<float>::max)();

	//	return AABBData{
	//		GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
	//		{ -xVal, -yVal, -zVal },
	//		{ xVal, yVal, zVal }
	//	};
	//}
	//Line1Volume::operator OBBData()
	//{
	//	auto direction = GetWorldDirection();
	//	float xVal = ZeroFloat(direction.GetX()) ? FDelta : (std::numeric_limits<float>::max)();
	//	float yVal = ZeroFloat(direction.GetY()) ? FDelta : (std::numeric_limits<float>::max)();
	//	float zVal = ZeroFloat(direction.GetZ()) ? FDelta : (std::numeric_limits<float>::max)();

	//	return OBBData{
	//		GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
	//		xVal, yVal, zVal
	//	};
	//}
	//Line1Volume::operator SphereData()
	//{
	//	return SphereData{
	//		GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
	//		(std::numeric_limits<float>::max)()
	//	};
	//}
	Ray1Volume::Ray1Volume(Vector3 origin, Vector3 dir)
	{
		SetPosition(origin);
		LookAt(dir);
	}
	Vector3 Ray1Volume::GetDirection(Matrix33 rotation)
	{
		return rotation.GetRow(2);
	}
	Vector3 Ray1Volume::GetEnd(Vector3 origin, Vector3 direction)
	{
		float x, y, z;
		if (ZeroFloat(direction.GetX()))
		{
			x = origin.GetX();
		}
		else
		{
			if (direction.GetX() > 0)
			{
				x = (std::numeric_limits<float>::max)();
			}
			else
			{
				x = -(std::numeric_limits<float>::max)();
			}
		}
		if (ZeroFloat(direction.GetY()))
		{
			y = origin.GetY();
		}
		else
		{
			if (direction.GetY() > 0)
			{
				y = (std::numeric_limits<float>::max)();
			}
			else
			{
				y = -(std::numeric_limits<float>::max)();
			}
		}
		if (ZeroFloat(direction.GetZ()))
		{
			z = origin.GetZ();
		}
		else
		{
			if (direction.GetZ() > 0)
			{
				z = (std::numeric_limits<float>::max)();
			}
			else
			{
				z = -(std::numeric_limits<float>::max)();
			}
		}
		return { x, y, z };
	}
	Vector3 Ray1Volume::GetWorldDirection()
	{
		return GetDirection(GetWorldRotation());
	}
	Vector3 Ray1Volume::GetLocalDirection()
	{
		return GetDirection(GetLocalRotation());
	}
	std::vector<Vector3> Ray1Volume::GetWorldBaseVertices()
	{
		auto origin = GetWorldPosition();
		auto direction = GetWorldDirection();

		Vector3 end = GetEnd(origin, direction);
		return { origin , end };
	}
	std::vector<TriangleData> Ray1Volume::GetWorldBaseTriangles()
	{
		return std::vector<TriangleData>();
	}
	Ray1Volume::operator RayData()
	{
		return RayData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			GetWorldPosition(), GetWorldDirection()
		};
	}
	Ray1Volume::operator AABBData()
	{
		auto origin = GetWorldPosition();
		auto direction = GetWorldRotation().GetRow(2);
		auto end = GetEnd(origin, direction);

		return AABBData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			{ min(origin.GetX(), end.GetX()), min(origin.GetY(), end.GetY()), min(origin.GetZ(), end.GetZ()) },
			{ max(origin.GetX(), end.GetX()), max(origin.GetY(), end.GetY()), max(origin.GetZ(), end.GetZ()) }
		};
	}
	Ray1Volume::operator OBBData()
	{
		auto origin = GetWorldPosition();
		auto direction = GetWorldRotation().GetRow(0);

		return OBBData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			FDelta / 2, FDelta / 2, (std::numeric_limits<float>::max)()
		};
	}
	Ray1Volume::operator SphereData()
	{
		return SphereData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			(std::numeric_limits<float>::max)()
		};
	}
	//Segment1Volume::Segment1Volume(Vector3 leftVertex, Vector3 rightVertex)
	//{
	//	Vector3 center = (leftVertex + rightVertex) / 2;
	//	SetPosition(center);

	//	Vector3 rightDirection = rightVertex - center;
	//	rightDirection.Normalize();
	//	Vector3 upDirection{ 0, 1, 0 };
	//	{
	//		Vector3 tmp = rightDirection;
	//		if (ZeroFloat(abs(tmp.GetY()) - upDirection.GetY()))
	//		{
	//			upDirection = { -1, 0, 0 };
	//		}
	//	}
	//	Vector3 forwardDirection = upDirection.Cross(rightDirection);
	//	LookAt(forwardDirection);

	//	SetScale((rightVertex - center).Length(), 1, 1);
	//}
	//float Segment1Volume::GetLength(Vector3 scale)
	//{
	//	return scale.GetX() * 2;
	//}
	//Vector3 Segment1Volume::GetLeftVertex(Vector3 center, Matrix33 rotation, Vector3 scale)
	//{
	//	Vector3 leftDirection = rotation.GetRow(0) * -1 * scale.GetX();
	//	return center + leftDirection;
	//}
	//Vector3 Segment1Volume::GetRightVertex(Vector3 center, Matrix33 rotation, Vector3 scale)
	//{
	//	Vector3 rightDirection = rotation.GetRow(0) * 1 * scale.GetX();
	//	return center + rightDirection;
	//}
	//float Segment1Volume::GetWorldLength()
	//{
	//	return GetLength(GetWorldScale());
	//}
	//float Segment1Volume::GetLocalLength()
	//{
	//	return GetLength(GetLocalScale());
	//}
	//Vector3 Segment1Volume::GetWorldLeftVertex()
	//{
	//	return GetLeftVertex(GetWorldPosition(), GetWorldRotation(), GetWorldScale());
	//}
	//Vector3 Segment1Volume::GetWorldRightVertex()
	//{
	//	return GetRightVertex(GetWorldPosition(), GetWorldRotation(), GetWorldScale());
	//}
	//Vector3 Segment1Volume::GetLocalLeftVertex()
	//{
	//	return GetLeftVertex(GetLocalPosition(), GetLocalRotation(), GetLocalScale());
	//}
	//Vector3 Segment1Volume::GetLocalRightVertex()
	//{
	//	return GetRightVertex(GetLocalPosition(), GetLocalRotation(), GetLocalScale());
	//}
	//Segment1Volume::operator SegmentData()
	//{
	//	return SegmentData{
	//		GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
	//		GetWorldLeftVertex(), GetWorldRightVertex()
	//	};
	//}
	//Segment1Volume::operator AABBData()
	//{
	//	auto leftVertex = GetWorldLeftVertex();
	//	auto rightVertex = GetWorldRightVertex();

	//	float minX = min(leftVertex.GetX(), rightVertex.GetX());
	//	float minY = min(leftVertex.GetY(), rightVertex.GetY());
	//	float minZ = min(leftVertex.GetZ(), rightVertex.GetZ());
	//	float maxX = max(leftVertex.GetX(), rightVertex.GetX());
	//	float maxY = max(leftVertex.GetY(), rightVertex.GetY());
	//	float maxZ = max(leftVertex.GetZ(), rightVertex.GetZ());

	//	return AABBData{
	//		GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
	//		{ minX, minY, minZ },
	//		{ maxX, maxY, maxZ }
	//	};
	//}
	//Segment1Volume::operator OBBData()
	//{
	//	float width = (GetLocalRightVertex() - GetLocalLeftVertex()).Length();
	//	return OBBData{
	//		GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
	//		width, FDelta, FDelta
	//	};
	//}
	//Segment1Volume::operator SphereData()
	//{
	//	return SphereData{
	//		GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
	//		GetWorldLength() / 2
	//	};
	//}
}
