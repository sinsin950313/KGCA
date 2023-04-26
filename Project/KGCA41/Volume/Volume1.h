#pragma once

#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"

namespace SSB
{
	// World
	struct VolumeData
	{
		Vector3 Position;
		Matrix33 Rotation;
		Vector3 Scale;
	};

	struct FaceData
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

	//struct PlaneData : public FaceData
	//{
	//	// commendted, not erased
	//	float Width;
	//	float Height;
	//};

	struct BoxData : public VolumeData
	{
		Vector3 Vertices[8];
		FaceData Plane[6];
	};

	struct SphereData : public VolumeData
	{
		float Radius;
	};

	//struct FrustumData : public VolumeData
	//{
	//	// commendted, not erased
	//	//PlaneData Plane[6];
	//	Vector3 Vertices[6];
	//};

	class VolumeInterface1
	{
	public:
		virtual Vector3 GetPosition() { return Vector3(); }
		virtual Matrix33 GetRotation() { return Matrix33(); }
		virtual Vector3 GetScale() { return Vector3(); }
	};

	class Volume1 : public VolumeInterface1
	{
	protected:
		class CollideCheckDelegate
		{
		private:
			Volume1* _owner;

		public:
			CollideCheckDelegate(Volume1* owner) : _owner(owner) { }

		public:
			Volume1* GetOwner() { return _owner; }

		public:
			//virtual bool IsCollide(VolumeData data) { return false; }
			//virtual bool IsCollide(PlaneData planeData) = 0;
			virtual bool IsCollide(BoxData boxData) = 0;
			virtual bool IsCollide(SphereData sphereData) = 0;
			//virtual bool IsCollide(FrustumData frustum) = 0;

		public:
			virtual bool IsIn(BoxData data) = 0;
			virtual bool IsIn(SphereData data) = 0;
		};

	private:
		static VolumeInterface1 DefaultVolume;

	private:
		VolumeData _data;
		CollideCheckDelegate* _collideDelegate;
		VolumeInterface1* _parent;

	public:
		Volume1(CollideCheckDelegate* collideDelegate);

	public:
		virtual bool IsCollide(Volume1* volume) { return false; }
		virtual bool IsIn(Volume1* volume) { return false; }
		//virtual void Resize(float width, float height, float depth) { }

	public:
		void SetParent(VolumeInterface1* parent = &DefaultVolume);
		VolumeData GetLocalVolumeData() { return _data; }
		void SetPosition(Vector3 position);
		void AddPosition(Vector3 vector);
		// Radian
		void SetRotation(float yaw, float pitch, float roll);
		void Rotate(HMatrix44 rotate);
		void Rotate(Quaternion quaternion);
		void SetScale(float width, float height, float depth);

	public:
		//bool IsCollideToVolume(VolumeData data) { return _collideDelegate->IsCollide(data); }
		//bool IsCollideToPlane(PlaneData data) { return _collideDelegate->IsCollide(data); }
		bool IsCollideToBox(BoxData data) { return _collideDelegate->IsCollide(data); }
		bool IsCollideToSphere(SphereData data) { return _collideDelegate->IsCollide(data); }
		//bool IsCollideToFrustum(FrustumData data) { return _collideDelegate->IsCollide(data); }

	public:
		bool IsInBox(BoxData data) { return _collideDelegate->IsIn(data); }
		bool IsInSphere(SphereData data) { return _collideDelegate->IsIn(data); }

	public:
		Vector3 GetPosition() override final;
		Matrix33 GetRotation() override final;
		Vector3 GetScale() override final;
	};
}
