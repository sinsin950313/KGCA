#include "Box1.h"
#include "HCCalculator.h"
#include "Common.h"

namespace SSB
{
	Box1Volume::BoxCollideDelegate::BoxCollideDelegate(Box1Volume* owner) : CollideCheckDelegate(owner)
	{
	}
	//std::vector<Vector3> Box1Volume::GetVertexList()
	//{
	//	Vector3 center = GetPosition();

	//	int dx[8] = { -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f };
	//	int dy[8] = { -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f };
	//	int dz[8] = { -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f };

	//	Matrix33 rotation = GetRotation();
	//	std::vector<Vector3> vertexList;
	//	vertexList.resize(8);
	//	for (int i = 0; i < 8; ++i)
	//	{
	//		vertexList[i] = center
	//			+ (rotation.GetRow(0)) * _width * dx[i]
	//			+ (rotation.GetRow(1)) * _height * dy[i]
	//			+ (rotation.GetRow(2)) * _depth * dz[i];
	//	}
	//	return vertexList;
	//}
	//void Box1Volume::GetPlaneVectorList(std::vector<Vector3> vertexList, Float4 retPlaneVector[6])
	//{
	//	implement;
	//}
	//bool Box1Volume::BoxCollideDelegate::IsCollide(PlaneData data)
	//{
	//	return false;
	//}
	bool Box1Volume::BoxCollideDelegate::IsCollide(BoxData boxData)
	{
		auto planes = ((Box1Volume*)GetOwner())->GetPlanes();

		for (int i = 0; i < 8; ++i)
		{
			bool in = true;
			auto vertex = boxData.Vertices[i];
			for (int j = 0; j < 6; ++j)
			{
				float distance = 
					planes[j].A * vertex.GetX() + 
					planes[j].B * vertex.GetY() + 
					planes[j].C * vertex.GetZ() + 
					planes[j].D;

				if (0 < distance)
				{
					in = false;
					break;
				}
			}

			if (in)
			{
				return true;
			}
		}
		return false;
	}
	bool Box1Volume::BoxCollideDelegate::IsCollide(SphereData sphereData)
	{
		auto planes = ((Box1Volume*)GetOwner())->GetPlanes();

		auto center = sphereData.Position;
		for (int i = 0; i < 6; ++i)
		{
			float distance =
				planes[i].A * center.GetX() +
				planes[i].B * center.GetY() +
				planes[i].C * center.GetZ() +
				planes[i].D;

			if (0 < distance - sphereData.Radius)
			{
				return false;
			}
		}

		return true;
	}
	bool Box1Volume::BoxCollideDelegate::IsIn(BoxData data)
	{
		auto planes = ((Box1Volume*)GetOwner())->GetPlanes();
		for (int i = 0; i < sizeof(data.Vertices) / sizeof(data.Vertices[0]); ++i)
		{
			Vector3 vertex = data.Vertices[i];
			for (auto plane : planes)
			{
				float distance = 
					plane.A * vertex.GetX() + 
					plane.B * vertex.GetY() + 
					plane.C * vertex.GetZ() + 
					plane.D;

				if (0 < distance)
				{
					return false;
				}
			}
		}
		return true;
	}
	bool Box1Volume::BoxCollideDelegate::IsIn(SphereData data)
	{
		auto planes = ((Box1Volume*)GetOwner())->GetPlanes();
		Vector3 center = data.Position;
		for (auto plane : planes)
		{
			float distance =
				plane.A * center.GetX() +
				plane.B * center.GetY() +
				plane.C * center.GetZ() +
				plane.D;

			if (0 < distance - data.Radius)
			{
				return false;
			}
		}
		return true;
	}
	std::vector<Vector3> Box1Volume::GetVertices()
	{
		Vector3 center = GetPosition();
		Vector3 scale = GetScale();

		float dx[8] = { -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f };
		float dy[8] = { -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f };
		float dz[8] = { -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f };

		Matrix33 rotation = GetRotation();
		std::vector<Vector3> vertexList;
		vertexList.resize(8);
		for (int i = 0; i < 8; ++i)
		{
			vertexList[i] = 
			{ 
				dx[i] * scale.GetX(), 
				dy[i] * scale.GetY(), 
				dz[i] * scale.GetZ() 
			};
			vertexList[i] = vertexList[i] * rotation;
			vertexList[i] = vertexList[i] + center;
		}

		return vertexList;
	}
	std::vector<FaceData> Box1Volume::GetPlanes()
	{
		Vector3 scale = GetScale();
		std::vector<HVector4> planes;
		planes.resize(6);

		float width = GetScale().GetX();
		float height = GetScale().GetY();
		float depth = GetScale().GetZ();
		
		planes[0] = { 1, 0, 0, -depth / 2 };
		planes[1] = { -1, 0, 0, -depth / 2 };
		planes[2] = { 0, 1, 0, -height / 2 };
		planes[3] = { 0, -1, 0, -height / 2 };
		planes[4] = { 0, 0, 1, -width / 2 };
		planes[5] = { 0, 0, -1, -width / 2 };

		Matrix33 rotation = GetRotation();
		Vector3 translation = GetPosition();
		HMatrix44 matrix(rotation, translation);

		std::vector<FaceData> ret;
		ret.resize(6);
		for (int i = 0; i < 6; ++i)
		{
			Vector3 direction = planes[i];
			direction = direction * rotation;
			direction.Normalize();

			float distance = 
				direction.GetX() * translation.GetX() +
				direction.GetY() * translation.GetY() +
				direction.GetZ() * translation.GetZ();
			distance = -distance;

			ret[i] = { direction.GetX(), direction.GetY(), direction.GetZ(), distance + planes[i].GetW() };
		}

		return ret;
	}
  //  void Box1Volume::Resize(float width, float height, float depth)
  //  {
		//SetScale(width, height, depth);
  //  }
	//bool Box1Volume::BoxCollideDelegate::IsCollide(FrustumData frustum)
	//{
	//	return false;
	//}
	Box1Volume::Box1Volume(float width, float height, float depth)
		: Volume1(new BoxCollideDelegate(this))
	{
		SetScale(width, height, depth);
	}
	Box1Volume::operator BoxData()
	{
		auto vertices = GetVertices();
		auto planes = GetPlanes();

		return BoxData{GetPosition(), GetRotation(), GetScale(), 
			vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5], vertices[6], vertices[7],
			planes[0], planes[1], planes[2], planes[3], planes[4], planes[5]};
	}
}
