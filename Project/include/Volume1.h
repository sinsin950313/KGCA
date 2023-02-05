#pragma once

#include "VolumeType.h"
#include "Quaternion.h"

namespace SSB
{
	class VolumeInterface1
	{
	public:
		virtual Vector3 GetWorldPosition() const { return Vector3(); }
		virtual Matrix33 GetWorldRotation() const { return Matrix33(); }
		virtual Vector3 GetWorldScale() const { return Vector3(); }
		virtual Vector3 GetLocalPosition() const { return Vector3(); }
		virtual Matrix33 GetLocalRotation() const { return Matrix33(); }
		virtual Vector3 GetLocalScale() const { return Vector3(); }
	};

	class Volume1 : public VolumeInterface1
	{
	private:
		static const VolumeInterface1 DefaultVolume;

	private:
		VolumeData _data;
		const VolumeInterface1* _parent = &DefaultVolume;

	public:
		void SetParent(VolumeInterface1* parent);
		void SetPosition(Vector3 position);
		void AddPosition(Vector3 vector);
		void SetRotation(float yaw, float pitch, float roll); // Radian
		void LookAt(Vector3 direction);
		void Rotate(HMatrix44 rotate);
		void Rotate(Quaternion quaternion);
		void SetScale(float x, float y, float z);

	public:
		VolumeData GetLocalVolumeData();
		Vector3 GetWorldPosition() const override final;
		Matrix33 GetWorldRotation() const override final;
		Vector3 GetWorldScale() const override final;
		Vector3 GetLocalPosition() const override final;
		Matrix33 GetLocalRotation() const override final;
		Vector3 GetLocalScale() const override final;

	public:
		virtual operator AABBData() = 0;
		virtual operator OBBData() = 0;
		virtual operator SphereData() = 0;
	};
}
