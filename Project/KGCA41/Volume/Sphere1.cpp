#include "Sphere1.h"
#include "Common.h"

namespace SSB
{
	const int Sphere1Volume::PI = 3;

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
	std::vector<Vector3> Sphere1Volume::GetWorldBaseVertices()
	{
		std::vector<Vector3> ret;

		float radius = GetWorldRadius();
		int stack = PI * radius;
		int sector = 2 * PI * radius;
		ret.resize((stack + 1) * (sector + 1));

		float sectorAngleUnit = 2.0f * ((float)PI) / sector;
		float stackAngleUnit = ((float)PI) / stack;
		for (int i = 0; i <= stack; ++i)
		{
			float stackAngle = (((float)PI) / 2) - (i * stackAngleUnit);
			float xz = radius * cosf(stackAngle);
			float y = radius * sinf(stackAngle);
			for (int j = 0; j <= sector; ++j)
			{
				float sectorAngle = sectorAngleUnit * j;
				float x = xz * cosf(sectorAngle);
				float z = xz * sinf(sectorAngle);
				ret[(i * (sector + 1)) + j] = { x, y, z };
			}
		}

		return ret;
	}
	std::vector<TriangleData> Sphere1Volume::GetWorldBaseTriangles()
	{
		std::vector<TriangleData> ret;
		auto vertice = GetWorldBaseVertices();

		float radius = GetWorldRadius();
		int stack = PI * radius;
		int sector = 2 * PI * radius;
		//ret.resize();

		for (int i = 0; i < stack; ++i)
		{
			int k1 = i * (sector + 1);
			int k2 = k1 + sector + 1;
			for (int j = 0; j < sector; ++j)
			{
				if (i != 0)
				{
					ret.push_back({ vertice[k2], vertice[k1], vertice[k1 + 1] });
				}
				if (i != (stack - 1))
				{
					ret.push_back({ vertice[k2], vertice[k1 + 1], vertice[k2 + 1] });
				}
			}
		}

		return ret;
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
