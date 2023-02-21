#pragma once

#include "VolumeType.h"
#include <vector>

namespace SSB
{
	class DefaultCollisionCalculator
	{
	public:
		bool IsCollide(VolumeData lData, VolumeData rData);
		bool IsIn(VolumeData lData, VolumeData rData);
		std::vector<Vector3> GetIntersections(VolumeData lData, VolumeData rData);
		bool IsCollide(VolumeData lData, LineData rData);
		bool IsIn(VolumeData lData, LineData rData);
		std::vector<Vector3> GetIntersections(VolumeData lData, LineData rData);
		bool IsCollide(VolumeData lData, RayData rData);
		bool IsIn(VolumeData lData, RayData rData);
		std::vector<Vector3> GetIntersections(VolumeData lData, RayData rData);
		bool IsCollide(VolumeData lData, SegmentData rData);
		bool IsIn(VolumeData lData, SegmentData rData);
		std::vector<Vector3> GetIntersections(VolumeData lData, SegmentData rData);
		bool IsCollide(VolumeData lData, PlaneData rData);
		bool IsIn(VolumeData lData, PlaneData rData);
		std::vector<Vector3> GetIntersections(VolumeData lData, PlaneData rData);
		bool IsCollide(VolumeData lData, TriangleData rData);
		bool IsIn(VolumeData lData, TriangleData rData);
		std::vector<Vector3> GetIntersections(VolumeData lData, TriangleData rData);
		bool IsCollide(VolumeData lData, AABBData rData);
		bool IsIn(VolumeData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(VolumeData lData, AABBData rData);
		bool IsCollide(VolumeData lData, OBBData rData);
		bool IsIn(VolumeData lData, OBBData rData);
		std::vector<Vector3> GetIntersections(VolumeData lData, OBBData rData);
		bool IsCollide(VolumeData lData, BoxData rData);
		bool IsIn(VolumeData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(VolumeData lData, BoxData rData);
		bool IsCollide(VolumeData lData, SphereData rData);
		bool IsIn(VolumeData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(VolumeData lData, SphereData rData);

	public:
		bool IsCollide(LineData lData, VolumeData rData);
		bool IsIn(LineData lData, VolumeData rData);
		std::vector<Vector3> GetIntersections(LineData lData, VolumeData rData);
		bool IsCollide(LineData lData, LineData rData);
		bool IsIn(LineData lData, LineData rData);
		std::vector<Vector3> GetIntersections(LineData lData, LineData rData);
		bool IsCollide(LineData lData, RayData rData);
		bool IsIn(LineData lData, RayData rData);
		std::vector<Vector3> GetIntersections(LineData lData, RayData rData);
		bool IsCollide(LineData lData, SegmentData rData);
		bool IsIn(LineData lData, SegmentData rData);
		std::vector<Vector3> GetIntersections(LineData lData, SegmentData rData);
		bool IsCollide(LineData lData, PlaneData rData);
		bool IsIn(LineData lData, PlaneData rData);
		std::vector<Vector3> GetIntersections(LineData lData, PlaneData rData);
		bool IsCollide(LineData lData, TriangleData rData);
		bool IsIn(LineData lData, TriangleData rData);
		std::vector<Vector3> GetIntersections(LineData lData, TriangleData rData);
		bool IsCollide(LineData lData, AABBData rData);
		bool IsIn(LineData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(LineData lData, AABBData rData);
		bool IsCollide(LineData lData, OBBData rData);
		bool IsIn(LineData lData, OBBData rData);
		std::vector<Vector3> GetIntersections(LineData lData, OBBData rData);
		bool IsCollide(LineData lData, BoxData rData);
		bool IsIn(LineData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(LineData lData, BoxData rData);
		bool IsCollide(LineData lData, SphereData rData);
		bool IsIn(LineData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(LineData lData, SphereData rData);

	public:
		bool IsCollide(RayData lData, VolumeData rData);
		bool IsIn(RayData lData, VolumeData rData);
		std::vector<Vector3> GetIntersections(RayData lData, VolumeData rData);
		bool IsCollide(RayData lData, LineData rData);
		bool IsIn(RayData lData, LineData rData);
		std::vector<Vector3> GetIntersections(RayData lData, LineData rData);
		bool IsCollide(RayData lData, RayData rData);
		bool IsIn(RayData lData, RayData rData);
		std::vector<Vector3> GetIntersections(RayData lData, RayData rData);
		bool IsCollide(RayData lData, SegmentData rData);
		bool IsIn(RayData lData, SegmentData rData);
		std::vector<Vector3> GetIntersections(RayData lData, SegmentData rData);
		bool IsCollide(RayData lData, PlaneData rData);
		bool IsIn(RayData lData, PlaneData rData);
		std::vector<Vector3> GetIntersections(RayData lData, PlaneData rData);
		bool IsCollide(RayData lData, TriangleData rData);
		bool IsIn(RayData lData, TriangleData rData);
		std::vector<Vector3> GetIntersections(RayData lData, TriangleData rData);
		bool IsCollide(RayData lData, AABBData rData);
		bool IsIn(RayData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(RayData lData, AABBData rData);
		bool IsCollide(RayData lData, OBBData rData);
		bool IsIn(RayData lData, OBBData rData);
		std::vector<Vector3> GetIntersections(RayData lData, OBBData rData);
		bool IsCollide(RayData lData, BoxData rData);
		bool IsIn(RayData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(RayData lData, BoxData rData);
		bool IsCollide(RayData lData, SphereData rData);
		bool IsIn(RayData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(RayData lData, SphereData rData);

	public:
		bool IsCollide(SegmentData lData, VolumeData rData);
		bool IsIn(SegmentData lData, VolumeData rData);
		std::vector<Vector3> GetIntersections(SegmentData lData, VolumeData rData);
		bool IsCollide(SegmentData lData, LineData rData);
		bool IsIn(SegmentData lData, LineData rData);
		std::vector<Vector3> GetIntersections(SegmentData lData, LineData rData);
		bool IsCollide(SegmentData lData, RayData rData);
		bool IsIn(SegmentData lData, RayData rData);
		std::vector<Vector3> GetIntersections(SegmentData lData, RayData rData);
		bool IsCollide(SegmentData lData, SegmentData rData);
		bool IsIn(SegmentData lData, SegmentData rData);
		std::vector<Vector3> GetIntersections(SegmentData lData, SegmentData rData);
		bool IsCollide(SegmentData lData, PlaneData rData);
		bool IsIn(SegmentData lData, PlaneData rData);
		std::vector<Vector3> GetIntersections(SegmentData lData, PlaneData rData);
		bool IsCollide(SegmentData lData, TriangleData rData);
		bool IsIn(SegmentData lData, TriangleData rData);
		std::vector<Vector3> GetIntersections(SegmentData lData, TriangleData rData);
		bool IsCollide(SegmentData lData, AABBData rData);
		bool IsIn(SegmentData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(SegmentData lData, AABBData rData);
		bool IsCollide(SegmentData lData, OBBData rData);
		bool IsIn(SegmentData lData, OBBData rData);
		std::vector<Vector3> GetIntersections(SegmentData lData, OBBData rData);
		bool IsCollide(SegmentData lData, BoxData rData);
		bool IsIn(SegmentData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(SegmentData lData, BoxData rData);
		bool IsCollide(SegmentData lData, SphereData rData);
		bool IsIn(SegmentData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(SegmentData lData, SphereData rData);

	public:
		bool IsCollide(PlaneData lData, VolumeData rData);
		bool IsIn(PlaneData lData, VolumeData rData);
		std::vector<Vector3> GetIntersections(PlaneData lData, VolumeData rData);
		bool IsCollide(PlaneData lData, LineData rData);
		bool IsIn(PlaneData lData, LineData rData);
		std::vector<Vector3> GetIntersections(PlaneData lData, LineData rData);
		bool IsCollide(PlaneData lData, RayData rData);
		bool IsIn(PlaneData lData, RayData rData);
		std::vector<Vector3> GetIntersections(PlaneData lData, RayData rData);
		bool IsCollide(PlaneData lData, SegmentData rData);
		bool IsIn(PlaneData lData, SegmentData rData);
		std::vector<Vector3> GetIntersections(PlaneData lData, SegmentData rData);
		bool IsCollide(PlaneData lData, PlaneData rData);
		bool IsIn(PlaneData lData, PlaneData rData);
		std::vector<Vector3> GetIntersections(PlaneData lData, PlaneData rData);
		bool IsCollide(PlaneData lData, TriangleData rData);
		bool IsIn(PlaneData lData, TriangleData rData);
		std::vector<Vector3> GetIntersections(PlaneData lData, TriangleData rData);
		bool IsCollide(PlaneData lData, AABBData rData);
		bool IsIn(PlaneData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(PlaneData lData, AABBData rData);
		bool IsCollide(PlaneData lData, OBBData rData);
		bool IsIn(PlaneData lData, OBBData rData);
		std::vector<Vector3> GetIntersections(PlaneData lData, OBBData rData);
		bool IsCollide(PlaneData lData, BoxData rData);
		bool IsIn(PlaneData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(PlaneData lData, BoxData rData);
		bool IsCollide(PlaneData lData, SphereData rData);
		bool IsIn(PlaneData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(PlaneData lData, SphereData rData);

	public:
		bool IsCollide(TriangleData lData, VolumeData rData);
		bool IsIn(TriangleData lData, VolumeData rData);
		std::vector<Vector3> GetIntersections(TriangleData lData, VolumeData rData);
		bool IsCollide(TriangleData lData, LineData rData);
		bool IsIn(TriangleData lData, LineData rData);
		std::vector<Vector3> GetIntersections(TriangleData lData, LineData rData);
		bool IsCollide(TriangleData lData, RayData rData);
		bool IsIn(TriangleData lData, RayData rData);
		std::vector<Vector3> GetIntersections(TriangleData lData, RayData rData);
		bool IsCollide(TriangleData lData, SegmentData rData);
		bool IsIn(TriangleData lData, SegmentData rData);
		std::vector<Vector3> GetIntersections(TriangleData lData, SegmentData rData);
		bool IsCollide(TriangleData lData, PlaneData rData);
		bool IsIn(TriangleData lData, PlaneData rData);
		std::vector<Vector3> GetIntersections(TriangleData lData, PlaneData rData);
		bool IsCollide(TriangleData lData, TriangleData rData);
		bool IsIn(TriangleData lData, TriangleData rData);
		std::vector<Vector3> GetIntersections(TriangleData lData, TriangleData rData);
		bool IsCollide(TriangleData lData, AABBData rData);
		bool IsIn(TriangleData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(TriangleData lData, AABBData rData);
		bool IsCollide(TriangleData lData, OBBData rData);
		bool IsIn(TriangleData lData, OBBData rData);
		std::vector<Vector3> GetIntersections(TriangleData lData, OBBData rData);
		bool IsCollide(TriangleData lData, BoxData rData);
		bool IsIn(TriangleData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(TriangleData lData, BoxData rData);
		bool IsCollide(TriangleData lData, SphereData rData);
		bool IsIn(TriangleData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(TriangleData lData, SphereData rData);

	public:
		bool IsCollide(AABBData lData, VolumeData rData);
		bool IsIn(AABBData lData, VolumeData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, VolumeData rData);
		bool IsCollide(AABBData lData, LineData rData);
		bool IsIn(AABBData lData, LineData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, LineData rData);
		bool IsCollide(AABBData lData, RayData rData);
		bool IsIn(AABBData lData, RayData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, RayData rData);
		bool IsCollide(AABBData lData, SegmentData rData);
		bool IsIn(AABBData lData, SegmentData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, SegmentData rData);
		bool IsCollide(AABBData lData, PlaneData rData);
		bool IsIn(AABBData lData, PlaneData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, PlaneData rData);
		bool IsCollide(AABBData lData, TriangleData rData);
		bool IsIn(AABBData lData, TriangleData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, TriangleData rData);
		bool IsCollide(AABBData lData, AABBData rData);
		bool IsIn(AABBData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, AABBData rData);
		bool IsCollide(AABBData lData, OBBData rData);
		bool IsIn(AABBData lData, OBBData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, OBBData rData);
		bool IsCollide(AABBData lData, BoxData rData);
		bool IsIn(AABBData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, BoxData rData);
		bool IsCollide(AABBData lData, SphereData rData);
		bool IsIn(AABBData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(AABBData lData, SphereData rData);

	public:
		bool IsCollide(OBBData lData, VolumeData rData);
		bool IsIn(OBBData lData, VolumeData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, VolumeData rData);
		bool IsCollide(OBBData lData, LineData rData);
		bool IsIn(OBBData lData, LineData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, LineData rData);
		bool IsCollide(OBBData lData, RayData rData);
		bool IsIn(OBBData lData, RayData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, RayData rData);
		bool IsCollide(OBBData lData, SegmentData rData);
		bool IsIn(OBBData lData, SegmentData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, SegmentData rData);
		bool IsCollide(OBBData lData, PlaneData rData);
		bool IsIn(OBBData lData, PlaneData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, PlaneData rData);
		bool IsCollide(OBBData lData, TriangleData rData);
		bool IsIn(OBBData lData, TriangleData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, TriangleData rData);
		bool IsCollide(OBBData lData, AABBData rData);
		bool IsIn(OBBData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, AABBData rData);
		bool IsCollide(OBBData lData, OBBData rData);
		bool IsIn(OBBData lData, OBBData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, OBBData rData);
		bool IsCollide(OBBData lData, BoxData rData);
		bool IsIn(OBBData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, BoxData rData);
		bool IsCollide(OBBData lData, SphereData rData);
		bool IsIn(OBBData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(OBBData lData, SphereData rData);

	public:
		bool IsCollide(BoxData lData, VolumeData rData);
		bool IsIn(BoxData lData, VolumeData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, VolumeData rData);
		bool IsCollide(BoxData lData, LineData rData);
		bool IsIn(BoxData lData, LineData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, LineData rData);
		bool IsCollide(BoxData lData, RayData rData);
		bool IsIn(BoxData lData, RayData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, RayData rData);
		bool IsCollide(BoxData lData, SegmentData rData);
		bool IsIn(BoxData lData, SegmentData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, SegmentData rData);
		bool IsCollide(BoxData lData, PlaneData rData);
		bool IsIn(BoxData lData, PlaneData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, PlaneData rData);
		bool IsCollide(BoxData lData, TriangleData rData);
		bool IsIn(BoxData lData, TriangleData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, TriangleData rData);
		bool IsCollide(BoxData lData, AABBData rData);
		bool IsIn(BoxData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, AABBData rData);
		bool IsCollide(BoxData lData, OBBData rData);
		bool IsIn(BoxData lData, OBBData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, OBBData rData);
		bool IsCollide(BoxData lData, BoxData rData);
		bool IsIn(BoxData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, BoxData rData);
		bool IsCollide(BoxData lData, SphereData rData);
		bool IsIn(BoxData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(BoxData lData, SphereData rData);

	public:
		bool IsCollide(SphereData lData, VolumeData rData);
		bool IsIn(SphereData lData, VolumeData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, VolumeData rData);
		bool IsCollide(SphereData lData, LineData rData);
		bool IsIn(SphereData lData, LineData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, LineData rData);
		bool IsCollide(SphereData lData, RayData rData);
		bool IsIn(SphereData lData, RayData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, RayData rData);
		bool IsCollide(SphereData lData, SegmentData rData);
		bool IsIn(SphereData lData, SegmentData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, SegmentData rData);
		bool IsCollide(SphereData lData, PlaneData rData);
		bool IsIn(SphereData lData, PlaneData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, PlaneData rData);
		bool IsCollide(SphereData lData, TriangleData rData);
		bool IsIn(SphereData lData, TriangleData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, TriangleData rData);
		bool IsCollide(SphereData lData, AABBData rData);
		bool IsIn(SphereData lData, AABBData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, AABBData rData);
		bool IsCollide(SphereData lData, OBBData rData);
		bool IsIn(SphereData lData, OBBData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, OBBData rData);
		bool IsCollide(SphereData lData, BoxData rData);
		bool IsIn(SphereData lData, BoxData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, BoxData rData);
		bool IsCollide(SphereData lData, SphereData rData);
		bool IsIn(SphereData lData, SphereData rData);
		std::vector<Vector3> GetIntersections(SphereData lData, SphereData rData);
	};
}
