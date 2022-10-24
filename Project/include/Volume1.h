#pragma once

#include "VolumeInterface1.h"
#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"

namespace SSB
{
	//template<typename HMatrix, typename Vector>
	//class Volume1 : public VolumeInterface1<HMatrix, Vector>
	//{
	//protected:
	//	Volume1<HMatrix, Vector>* _parent;
	//	float _radius;
	//	HMatrix* _matrix;

	//public:
	//	bool IsIn(const Vector& v) const;
	//	bool IsCollide(const Volume1& volume) const;
	//	const std::vector<Vector*>& GetVertexes() const { return _vertexes; }
	//	const Vector GetCenter() const { return _matrix->GetRow(); }

	//protected:
	//	const Vector& GetCenter() const { return _parent->GetMatrix().GetRow(0); }
	//	float GetRadius() const { return _radius; }

	//public:
	//	virtual void Print() const = 0;
	//	virtual void Resize(float radius) { _radius = radius; }
	//	virtual void Reposition(Vector pos) { _center = pos; }
	//};

	class Volume1
	{
	protected:
		struct PlaneData
		{
			float A;
			float B;
			float C;
			float D;
		};

		struct BoxData
		{
			PlaneData Plane[6];
		};

		struct SphereData
		{
			HMatrix44 Matrix;
			float Radius;
		};

		struct FrustumData
		{
			PlaneData Plane[6];
		};

		class CollideCheckDelegate
		{
		private:
			Volume1* _owner;

		public:
			CollideCheckDelegate(Volume1* owner) : _owner(owner) { }

		public:
			Volume1* GetOwner() { return _owner; }

		public:
			virtual bool IsCollide(PlaneData planeData) = 0;
			virtual bool IsCollide(BoxData boxData) = 0;
			virtual bool IsCollide(SphereData sphereData) = 0;
			virtual bool IsCollide(FrustumData frustum) = 0;
		};

	private:
		HMatrix44 _matrix;
		CollideCheckDelegate* _collideDelegate;

	public:
		Volume1(CollideCheckDelegate* collideDelegate, HMatrix44 matrix = HMatrix44()) : _collideDelegate(collideDelegate), _matrix(matrix) { }

	public:
		virtual bool IsCollide(Volume1* volume) = 0;

	public:
		// Return World Matrix
		HMatrix44 GetMatrix() { return _matrix; }

	public:
		bool IsCollideToPlane(PlaneData data) { return _collideDelegate->IsCollide(data); }
		bool IsCollideToBox(BoxData data) { return _collideDelegate->IsCollide(data); }
		bool IsCollideToSphere(SphereData data) { return _collideDelegate->IsCollide(data); }
		bool IsCollideToFrustum(FrustumData data) { return _collideDelegate->IsCollide(data); }
		void Rotate(HMatrix44 rotate);
		void Rotate(Quaternion quaternion);
	};
}
