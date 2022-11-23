#pragma once

#include "VolumeInterface1.h"
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

	struct FaceData : public VolumeData
	{
		union
		{
			Float4 NormalVector;

			float A;
			float B;
			float C;
			float D;
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
		FaceData Plane[6];
		float Width;
		float Height;
		float Depth;
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

	class Volume1
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
		};

	private:
		static Volume1 DefaultVolume;

	private:
		VolumeData _data;
		CollideCheckDelegate* _collideDelegate;
		Volume1* _parent;

	public:
		Volume1(CollideCheckDelegate* collideDelegate);

	public:
		virtual bool IsCollide(Volume1* volume) = 0;
		virtual void Resize(float width, float height, float depth) = 0;

	public:
		void SetParent(Volume1* parent = &DefaultVolume);
		VolumeData GetLocalVolumeData() { return _data; }
		void SetPosition(Vector3 position);
		void AddPosition(Vector3 vector);
		Vector3 GetPosition();
		// Radian
		void SetRotation(float yaw, float pitch, float roll);
		void Rotate(HMatrix44 rotate);
		void Rotate(Quaternion quaternion);
		Matrix33 GetRotation();
		void SetScale(float width, float height, float depth);
		Vector3 GetScale();

	public:
		//bool IsCollideToVolume(VolumeData data) { return _collideDelegate->IsCollide(data); }
		//bool IsCollideToPlane(PlaneData data) { return _collideDelegate->IsCollide(data); }
		bool IsCollideToBox(BoxData data) { return _collideDelegate->IsCollide(data); }
		bool IsCollideToSphere(SphereData data) { return _collideDelegate->IsCollide(data); }
		//bool IsCollideToFrustum(FrustumData data) { return _collideDelegate->IsCollide(data); }
	};
}
