#include "Box1.h"

namespace SSB
{
	Box::BoxCollideDelegate::BoxCollideDelegate(Box* owner) : CollideCheckDelegate(owner)
	{
	}
	std::vector<Vector3> Box::GetVertexList()
	{
		Vector3 center = GetPosition();

		int dx[8] = { -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f };
		int dy[8] = { -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f };
		int dz[8] = { -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f };

		Matrix33 rotation = GetRotation();
		std::vector<Vector3> vertexList;
		vertexList.resize(8);
		for (int i = 0; i < 8; ++i)
		{
			vertexList[i] = center
				+ (rotation.GetRow(0)) * _width * dx[i]
				+ (rotation.GetRow(1)) * _height * dy[i]
				+ (rotation.GetRow(2)) * _depth * dz[i];
		}
		return vertexList;
	}
	void Box::GetPlaneVectorList(std::vector<Vector3> vertexList, Float4 retPlaneVector[6])
	{
		implement;
	}
	//bool Box::BoxCollideDelegate::IsCollide(PlaneData data)
	//{
	//	return false;
	//}
	bool Box::BoxCollideDelegate::IsCollide(BoxData boxData)
	{
		implement;
	}
	bool Box::BoxCollideDelegate::IsCollide(SphereData sphereData)
	{
		implement;
	}
	//bool Box::BoxCollideDelegate::IsCollide(FrustumData frustum)
	//{
	//	return false;
	//}
	Box::Box(float width, float height, float depth)
		: Volume1(new BoxCollideDelegate(this)), _width(width), _height(height), _depth(depth)
	{
	}
	Box::operator BoxData()
	{
		return BoxData{GetPosition(), GetRotation(), GetScale(), _width, _height, _depth};
	}
}
