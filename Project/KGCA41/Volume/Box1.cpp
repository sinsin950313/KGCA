#include "Box1.h"
#include "HCCalculator.h"
#include <climits>

namespace SSB
{
	std::vector<Vector3> Box1Volume::GetVertices(Vector3 center, Matrix33 rotation, Vector3 scale)
	{
		float dx[8] = { -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f };
		float dy[8] = { -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f };
		float dz[8] = { -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

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
	std::vector<PlaneData> Box1Volume::GetPlanes(Vector3 center, Matrix33 rotation, Vector3 scale)
	{
		std::vector<HVector4> planes;
		planes.resize(6);

		float width = scale.GetX();
		float height = scale.GetY();
		float depth = scale.GetZ();
		
		planes[0] = { 1, 0, 0, -depth / 2 };
		planes[1] = { -1, 0, 0, -depth / 2 };
		planes[2] = { 0, 1, 0, -height / 2 };
		planes[3] = { 0, -1, 0, -height / 2 };
		planes[4] = { 0, 0, 1, -width / 2 };
		planes[5] = { 0, 0, -1, -width / 2 };

		HMatrix44 matrix(rotation, center);

		std::vector<PlaneData> ret;
		ret.resize(6);
		for (int i = 0; i < 6; ++i)
		{
			Vector3 direction = planes[i];
			direction = direction * rotation;
			direction.Normalize();

			float distance = 
				direction.GetX() * center.GetX() +
				direction.GetY() * center.GetY() +
				direction.GetZ() * center.GetZ();
			distance = -distance;

			ret[i] = { direction.GetX(), direction.GetY(), direction.GetZ(), distance + planes[i].GetW() };
		}

		return ret;
	}
	std::vector<Vector3> Box1Volume::GetWorldVertices()
	{
		return GetVertices(GetWorldPosition(), GetWorldRotation(), GetWorldScale());
	}
	std::vector<PlaneData> Box1Volume::GetWorldPlanes()
	{
		return GetPlanes(GetWorldPosition(), GetWorldRotation(), GetWorldScale());
	}
	std::vector<Vector3> Box1Volume::GetLocalVertices()
	{
		return GetVertices(GetLocalPosition(), GetLocalRotation(), GetLocalScale());
	}
	std::vector<PlaneData> Box1Volume::GetLocalPlanes()
	{
		return GetPlanes(GetLocalPosition(), GetLocalRotation(), GetLocalScale());
	}
	std::vector<Vector3> Box1Volume::GetWorldBaseVertices()
	{
		return GetWorldVertices();
	}
	std::vector<TriangleData> Box1Volume::GetWorldBaseTriangles()
	{
		std::vector<TriangleData> ret;
		auto vertice = GetWorldVertices();
		auto planes = GetWorldPlanes();

		ret.resize(12);
		ret[0] = { /*{planes[1]}, */vertice[0], vertice[1], vertice[2] };
		ret[1] = { /*{planes[1]}, */vertice[2], vertice[1], vertice[3] };
		ret[2] = { /*{planes[4]}, */vertice[2], vertice[3], vertice[6] };
		ret[3] = { /*{planes[4]}, */vertice[6], vertice[3], vertice[7] };
		ret[4] = { /*{planes[2]}, */vertice[1], vertice[5], vertice[3] };
		ret[5] = { /*{planes[2]}, */vertice[3], vertice[5], vertice[7] };
		ret[6] = { /*{planes[5]}, */vertice[4], vertice[5], vertice[0] };
		ret[7] = { /*{planes[5]}, */vertice[0], vertice[5], vertice[1] };
		ret[8] = { /*{planes[3]}, */vertice[4], vertice[0], vertice[6] };
		ret[9] = { /*{planes[3]}, */vertice[6], vertice[0], vertice[2] };
		ret[10] = { /*{planes[0]}, */vertice[6], vertice[7], vertice[4] };
		ret[11] = { /*{planes[0]}, */vertice[4], vertice[7], vertice[5] };

		return ret;
	}
	Box1Volume::Box1Volume(float width, float height, float depth)
	{
		SetScale(width, height, depth);
	}
	Box1Volume::operator BoxData()
	{
		auto vertices = GetWorldVertices();
		auto planes = GetWorldPlanes();

		return BoxData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(), 
			vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5], vertices[6], vertices[7],
			planes[0], planes[1], planes[2], planes[3], planes[4], planes[5]
		};
	}
	Box1Volume::operator AABBData()
	{
		auto vertice = GetWorldVertices();
		float minX = std::numeric_limits<float>::max();
		float minY = std::numeric_limits<float>::max();
		float minZ = std::numeric_limits<float>::max();
		float maxX = -std::numeric_limits<float>::max();
		float maxY = -std::numeric_limits<float>::max();
		float maxZ = -std::numeric_limits<float>::max();

		for(auto vertex : vertice)
		{
			minX = std::min(minX, vertex.GetX());
			minY = std::min(minY, vertex.GetY());
			minZ = std::min(minZ, vertex.GetZ());

			maxX = std::max(maxX, vertex.GetX());
			maxY = std::max(maxY, vertex.GetY());
			maxZ = std::max(maxZ, vertex.GetZ());
		}
		return AABBData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			{ minX, minY, minZ },
			{ maxX, maxY, maxZ }
		};
	}
	Box1Volume::operator OBBData()
	{
		auto scale = GetWorldScale() * 2;
		return OBBData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			scale.GetX(), scale.GetY(), scale.GetZ()
		};
	}
	Box1Volume::operator SphereData()
	{
		auto scale = GetWorldScale();
		float radius = scale.Length();
		return SphereData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			radius
		};
	}
	//AABB1Volume::AABB1Volume(float width, float height, float depth)
	//{
	//	SetScale(width, height, depth);
	//}
	//std::vector<Vector3> AABB1Volume::GetVertices(Vector3 center, Matrix33 rotation, Vector3 scale)
	//{
	//	float dx[8] = { -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f };
	//	float dy[8] = { -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f };
	//	float dz[8] = { -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

	//	std::vector<Vector3> vertexList;
	//	vertexList.resize(8);
	//	for (int i = 0; i < 8; ++i)
	//	{
	//		vertexList[i] = 
	//		{ 
	//			dx[i] * scale.GetX(), 
	//			dy[i] * scale.GetY(), 
	//			dz[i] * scale.GetZ() 
	//		};
	//		vertexList[i] = vertexList[i] * rotation;
	//		vertexList[i] = vertexList[i] + center;
	//	}

	//	return vertexList;
	//}
	//std::vector<PlaneData> AABB1Volume::GetPlanes(Vector3 center, Matrix33 rotation, Vector3 scale)
	//{
	//	std::vector<HVector4> planes;
	//	planes.resize(6);

	//	float width = scale.GetX();
	//	float height = scale.GetY();
	//	float depth = scale.GetZ();
	//	
	//	planes[0] = { 1, 0, 0, -depth / 2 };
	//	planes[1] = { -1, 0, 0, -depth / 2 };
	//	planes[2] = { 0, 1, 0, -height / 2 };
	//	planes[3] = { 0, -1, 0, -height / 2 };
	//	planes[4] = { 0, 0, 1, -width / 2 };
	//	planes[5] = { 0, 0, -1, -width / 2 };

	//	HMatrix44 matrix(rotation, center);

	//	std::vector<PlaneData> ret;
	//	ret.resize(6);
	//	for (int i = 0; i < 6; ++i)
	//	{
	//		Vector3 direction = planes[i];
	//		direction = direction * rotation;
	//		direction.Normalize();

	//		float distance = 
	//			direction.GetX() * center.GetX() +
	//			direction.GetY() * center.GetY() +
	//			direction.GetZ() * center.GetZ();
	//		distance = -distance;

	//		ret[i] = { direction.GetX(), direction.GetY(), direction.GetZ(), distance + planes[i].GetW() };
	//	}

	//	return ret;
	//}
	//std::vector<Vector3> AABB1Volume::GetWorldVertices()
	//{
	//	return GetVertices(GetWorldPosition(), GetWorldRotation(), GetWorldScale());
	//}
	//std::vector<PlaneData> AABB1Volume::GetWorldPlanes()
	//{
	//	return GetPlanes(GetWorldPosition(), GetWorldRotation(), GetWorldScale());
	//}
	//std::vector<Vector3> AABB1Volume::GetLocalVertices()
	//{
	//	return GetVertices(GetLocalPosition(), GetLocalRotation(), GetLocalScale());
	//}
	//std::vector<PlaneData> AABB1Volume::GetLocalPlanes()
	//{
	//	return GetPlanes(GetLocalPosition(), GetLocalRotation(), GetLocalScale());
	//}
	//AABB1Volume::operator AABBData()
	//{
	//	auto vertice = GetWorldVertices();
	//	float minX = std::numeric_limits<float>::min();
	//	float minY = std::numeric_limits<float>::min();
	//	float minZ = std::numeric_limits<float>::min();
	//	float maxX = std::numeric_limits<float>::max();
	//	float maxY = std::numeric_limits<float>::max();
	//	float maxZ = std::numeric_limits<float>::max();

	//	for(auto vertex : vertice)
	//	{
	//		minX = std::min(minX, vertex.GetX());
	//		minY = std::min(minY, vertex.GetY());
	//		minZ = std::min(minZ, vertex.GetZ());

	//		maxX = std::max(maxX, vertex.GetX());
	//		maxY = std::max(maxY, vertex.GetY());
	//		maxZ = std::max(maxZ, vertex.GetZ());
	//	}
	//	return AABBData{
	//		GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
	//		{ minX, minY, minZ },
	//		{ maxX, maxY, maxZ }
	//	};
	//}
	//AABB1Volume::operator OBBData()
	//{
	//	auto scale = GetWorldScale() * 2;
	//	return OBBData{
	//		GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
	//		scale.GetX(), scale.GetY(), scale.GetZ()
	//	};
	//}
	//AABB1Volume::operator SphereData()
	//{
	//	auto scale = GetWorldScale();
	//	float radius = scale.Length();
	//	return SphereData{
	//		GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
	//		sqrt(radius * radius)
	//	};
	//}
}
