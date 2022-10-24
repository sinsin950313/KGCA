#pragma once

#include "Volume1.h"

namespace SSB
{
	class Plane : public Volume1
	{
	private:
		class PlaneCollideDelegate : public CollideCheckDelegate
		{
		public:
			PlaneCollideDelegate(Plane* owner);

		private:
			bool IsZero(float val) { return val < 0.0001f; }
			float GetDistance(Vector3 point);

		public:
			bool IsCollide(PlaneData planeData) override;
			bool IsCollide(BoxData boxData) override;
			bool IsCollide(SphereData sphereData) override;
			bool IsCollide(FrustumData frustum) override;
		};
		PlaneData _data;

	public:
		Plane(Vector3 normal, Vector3 point);

	public:
		bool IsCollide(Volume1* volume) { volume->IsCollideToPlane(*this); }

	public:
		operator PlaneData();
	};
}
