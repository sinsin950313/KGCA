#include "Box1.h"

namespace SSB
{
	Box::BoxCollideDelegate::BoxCollideDelegate(BoxData data)
	{
		_data = data;
		GetPlaneVectorList(GetVertexList(data), _plane);
	}
	std::vector<Vector3> Box::BoxCollideDelegate::GetVertexList(BoxData boxData)
	{
		Vector3 center = boxData._matrix.GetRow(3);

		int dx[8] = { -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f };
		int dy[8] = { -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f };
		int dz[8] = { -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f };

		std::vector<Vector3> vertexList;
		vertexList.resize(8);
		for (int i = 0; i < 8; ++i)
		{
			vertexList[i] = center
				+ ((Vector3)boxData._matrix.GetRow(0)) * boxData._width * dx[i]
				+ ((Vector3)boxData._matrix.GetRow(1)) * boxData._height * dy[i]
				+ ((Vector3)boxData._matrix.GetRow(2)) * boxData._depth * dz[i];
		}
		return vertexList;
	}
	void Box::BoxCollideDelegate::GetPlaneVectorList(std::vector<Vector3> vertexList, Float4 retPlaneVector[6])
	{
	}
	bool Box::BoxCollideDelegate::IsCollide(PlaneData data)
	{
		return false;
	}
	bool Box::BoxCollideDelegate::IsCollide(BoxData boxData)
	{
	}
	bool Box::BoxCollideDelegate::IsCollide(SphereData sphereData)
	{
		return false;
	}
	bool Box::BoxCollideDelegate::IsCollide(FrustumData frustum)
	{
		return false;
	}
	Box::Box(BoxData data)
	{
	}
	Box::operator BoxData()
	{
	}
}
