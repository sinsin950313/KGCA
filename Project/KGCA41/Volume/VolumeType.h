#pragma once

#include "Matrix.h"

namespace SSB
{
	 //World Data

	struct VolumeData
	{
		Vector3 Position;
		Matrix33 Rotation;
		Vector3 Scale;
	};

	struct LineData : public VolumeData
	{
		Vector3 Vertex;
		Vector3 Direction;
	};

	struct RayData : public VolumeData
	{
		Vector3 Origin;
		Vector3 Direction;
	};

	struct SegmentData : public VolumeData
	{
		Vector3 A;
		Vector3 B;
	};

	struct PlaneData
	{
		union
		{
			Float4 NormalVector;

			struct
			{
				float A;
				float B;
				float C;
				float D;
			};
		};
	};

	struct TriangleData
	{
		Vector3 Vertice[3];
	};

	struct AABBData : public VolumeData
	{
		Vector3 Min;
		Vector3 Max;
	};

	struct OBBData : public VolumeData
	{
		float Width;
		float Height;
		float Depth;
	};

	struct BoxData : public VolumeData
	{
		Vector3 Vertices[8];
		PlaneData Plane[6];
	};

	 //Same as Box
	//struct FrustumData : public VolumeData
	//{
	//	Vector3 Vertices[6];
	//	PlaneData Plane[6];
	//};

	struct SphereData : public VolumeData
	{
		float Radius;
	};
}
