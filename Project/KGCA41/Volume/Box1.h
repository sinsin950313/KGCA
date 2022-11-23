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
			BoxCollideDelegate(Box* owner);

		public:
			//bool IsCollide(PlaneData data) override;
			bool IsCollide(BoxData boxData) override;
			bool IsCollide(SphereData sphereData) override;
			//bool IsCollide(FrustumData frustum) override;
		};

	private:
		float _width;
		float _height;
		float _depth;
	private:
		std::vector<Vector3> GetVertices();
		std::vector<FaceData> GetPlanes();

	public:
		Box(float width = 1.0f, float height = 1.0f, float depth = 1.0f);

	public:
		bool IsCollide(Volume1* volume) override { volume->IsCollideToBox(*this); }
		void Resize(float width, float height, float depth) override;

	public:
		operator BoxData();
	};
}
