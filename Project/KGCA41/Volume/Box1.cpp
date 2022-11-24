#include "Box1.h"
#include "HCCalculator.h"
#include "Common.h"

namespace SSB
{
	Box::BoxCollideDelegate::BoxCollideDelegate(Box* owner) : CollideCheckDelegate(owner)
	{
	}
	//std::vector<Vector3> Box::GetVertexList()
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
	//void Box::GetPlaneVectorList(std::vector<Vector3> vertexList, Float4 retPlaneVector[6])
	//{
	//	implement;
	//}
	//bool Box::BoxCollideDelegate::IsCollide(PlaneData data)
	//{
	//	return false;
	//}
	bool Box::BoxCollideDelegate::IsCollide(BoxData boxData)
	{
		auto planes = ((Box*)GetOwner())->GetPlanes();

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
	bool Box::BoxCollideDelegate::IsCollide(SphereData sphereData)
	{
		auto planes = ((Box*)GetOwner())->GetPlanes();

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
	std::vector<Vector3> Box::GetVertices()
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
	std::vector<FaceData> Box::GetPlanes()
	{
		Vector3 scale = GetScale();
		std::vector<HVector4> planes;
		planes.resize(6);

		float width = GetScale().GetX();
		float height = GetScale().GetY();
		float depth = GetScale().GetZ();
		
		planes[0] = { 1, 0, 0, -depth / 2  * scale.GetZ() };
		planes[1] = { -1, 0, 0, -depth / 2 * scale.GetZ() };
		planes[2] = { 0, 1, 0, -height / 2 * scale.GetY() };
		planes[3] = { 0, -1, 0, -height / 2 * scale.GetY() };
		planes[4] = { 0, 0, 1, -width / 2 * scale.GetX() };
		planes[5] = { 0, 0, -1, -width / 2 * scale.GetX() };

		HMatrix44 matrix(GetRotation(), GetPosition());
		std::vector<FaceData> ret;
		ret.resize(6);
		for (int i = 0; i < 6; ++i)
		{
			auto result = planes[i] * matrix;
			ret[i] = { result.GetX(), result.GetY(), result.GetZ(), result.GetW() };
		}

		return ret;
	}
  //  void Box::Resize(float width, float height, float depth)
  //  {
		//SetScale(width, height, depth);
  //  }
	//bool Box::BoxCollideDelegate::IsCollide(FrustumData frustum)
	//{
	//	return false;
	//}
	Box::Box(float width, float height, float depth)
		: Volume1(new BoxCollideDelegate(this))
	{
		SetScale(width, height, depth);
	}
	Box::operator BoxData()
	{
		auto vertices = GetVertices();
		auto planes = GetPlanes();

		return BoxData{GetPosition(), GetRotation(), GetScale(), 
			vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5], vertices[6], vertices[7],
			planes[0], planes[1], planes[2], planes[3], planes[4], planes[5]};
	}
}
