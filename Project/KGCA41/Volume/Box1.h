#pragma once

#include "Volume1.h"

namespace SSB
{
	class Box : public Volume1
	{
	private:
		class BoxCollideDelegate : public CollideCheckDelegate
		{
		public:
			BoxCollideDelegate(BoxData data);

		private:
			std::vector<Vector3> GetVertexList(BoxData boxData);
			void GetPlaneVectorList(std::vector<Vector3> vertexList, Float4 retPlaneVector[6]);

		public:
			bool IsCollide(PlaneData data) override;
			bool IsCollide(BoxData boxData) override;
			bool IsCollide(SphereData sphereData) override;
			bool IsCollide(FrustumData frustum) override;
		};

	public:
		Box(float width, float height, float depth, HMatrix44 matrix = HMatrix44());

	public:
		bool IsCollide(Volume1* volume) { volume->IsCollideToBox(*this); }

	public:
		operator BoxData();
	};
}
