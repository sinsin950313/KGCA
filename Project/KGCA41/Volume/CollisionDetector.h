#pragma once

#include "VolumeType.h"
#include <vector>

namespace SSB
{
	class CollisionDetector
	{
	public:
		bool IsCollide(BoxData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, BoxData rData);
		bool IsCollide(BoxData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, AABBData rData);
		bool IsCollide(BoxData lData, OBBData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, OBBData rData);
		bool IsCollide(BoxData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, SphereData rData);

	public:
		bool IsCollide(SphereData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, BoxData rData);
		bool IsCollide(SphereData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, SphereData rData);
		bool IsCollide(SphereData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, AABBData rData);
		bool IsCollide(SphereData lData, OBBData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, OBBData rData);

	public:
		bool IsCollide(AABBData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, BoxData rData);
		bool IsCollide(AABBData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, SphereData rData);
		bool IsCollide(AABBData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, AABBData rData);
		bool IsCollide(AABBData Data, OBBData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, OBBData rData);

	public:
		bool IsCollide(OBBData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, BoxData rData);
		bool IsCollide(OBBData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, SphereData rData);
		bool IsCollide(OBBData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, AABBData rData);
		bool IsCollide(OBBData Data, OBBData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, OBBData rData);
	};
}
