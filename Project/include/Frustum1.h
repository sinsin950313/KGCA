#pragma once

#include "Volume1.h"

namespace SSB
{
	//class Frustum : public Volume1
	//{
	//private:
	//	class FrustumCollideDelegate : public CollideCheckDelegate
	//	{
	//		FrustumData _data;

	//	public:
	//		FrustumCollideDelegate(FrustumData data);

	//	public:
	//		bool IsCollide(PlaneData data) override;
	//		bool IsCollide(BoxData boxData) override;
	//		bool IsCollide(SphereData sphereData) override;
	//		bool IsCollide(FrustumData frustum) override;
	//	};
	//	FrustumData _data;

	//public:
	//	Frustum();
	//	Frustum(HMatrix44 viewMatrix, HMatrix44 projectionMatrix);

	//public:
	//	bool IsCollide(Volume1* volume) override { volume->IsCollideToFrustum(*this); }
	//	void Resize(float width, float height, float depth) override;

	//public:
	//	operator FrustumData();
	//};
}
