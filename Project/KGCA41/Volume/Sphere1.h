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
			//bool IsCollide(PlaneData data) override;
			bool IsCollide(BoxData boxData) override;
			bool IsCollide(SphereData sphereData) override;
			//bool IsCollide(FrustumData frustumData) override;
		};

	private:
		float _radius;

	public:
		Sphere(float radius = 1.0f);

	public:
		bool IsCollide(Volume1* volume) override { return volume->IsCollideToSphere(*this); }
		// Resize radius to sqrt(width * width + height * height + depth * depth);
		void Resize(float width, float height, float depth) override;

	public:
		operator SphereData();
	};
}
