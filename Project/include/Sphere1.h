#pragma once

#include "Volume1.h"

namespace SSB
{
	class Sphere : public Volume1
	{
	private:
		class SphereCollideDelegate : public CollideCheckDelegate
		{
		public:
			SphereCollideDelegate(Sphere* owner);

		public:
			bool IsCollide(PlaneData data) override;
			bool IsCollide(BoxData boxData) override;
			bool IsCollide(SphereData sphereData) override;
			bool IsCollide(FrustumData frustumData) override;
		};
		float _radius;

	public:
		Sphere(float radius, HMatrix44 matrix = HMatrix44());

	public:
		bool IsCollide(Volume1* volume) { return volume->IsCollideToSphere(*this); }

	public:
		operator SphereData();
	};
}
