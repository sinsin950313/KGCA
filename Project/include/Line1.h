#pragma once

#include "Vector.h"
#include "Volume1.h"

namespace SSB
{
	class Line1Volume : public Volume1
	{
	public:
		Line1Volume(Vector3 vertex, Vector3 direction);

	private:
		Vector3 GetDirection(Matrix33 rotation);

	protected:
		Vector3 GetWorldDirection();
		Vector3 GetLocalDirection();

	public:
		operator LineData();
		operator AABBData() override;
		operator OBBData() override;
		operator SphereData() override;
	};

	class Ray1Volume : public Volume1
	{
	public:
		Ray1Volume(Vector3 origin, Vector3 dir);

	private:
		Vector3 GetDirection(Matrix33 rotation);

	protected:
		Vector3 GetWorldDirection();
		Vector3 GetLocalDirection();

	public:
		operator RayData();
		operator AABBData() override;
		operator OBBData() override;
		operator SphereData() override;
	};

	class Segment1Volume : public Volume1
	{
	public:
		Segment1Volume(Vector3 leftVertex, Vector3 rightVertex);

	private:
		float GetLength(Vector3 scale);
		Vector3 GetLeftVertex(Vector3 center, Matrix33 rotation, Vector3 scale);
		Vector3 GetRightVertex(Vector3 center, Matrix33 rotation, Vector3 scale);

	public:
		float GetWorldLength();
		float GetLocalLength();
		Vector3 GetWorldLeftVertex();
		Vector3 GetWorldRightVertex();
		Vector3 GetLocalLeftVertex();
		Vector3 GetLocalRightVertex();

	public:
		operator SegmentData();
		operator AABBData() override;
		operator OBBData() override;
		operator SphereData() override;
	};
}
