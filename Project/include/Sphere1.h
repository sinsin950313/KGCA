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

		public:
			bool IsIn(BoxData data) override;
			bool IsIn(SphereData data) override;
		};

	//private:
	//	float _radius;

	public:
		Sphere(float radius = 1.0f);

	public:
		bool IsCollide(Volume1* volume) override { return volume->IsCollideToSphere(*this); }
		virtual bool IsIn(Volume1* volume) override { return volume->IsInSphere(*this); }
		// Resize radius to sqrt(width * width + height * height + depth * depth);
		float GetRadius();
		//void Resize(float width, float height, float depth) override;

	public:
		operator SphereData();
	};
}
