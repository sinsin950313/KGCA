#pragma once

#include "Volume1.h"
#include "CollisionSystemVolumeType.h"

namespace SSB
{
	// For static dynamic system
	class CollisionSystemVolume
	{
	private:
		VolumeType _type;
		Volume1* _volume;
		bool _isStatic;

	public:
		CollisionSystemVolume(VolumeType type, Volume1* volume, bool isStatic = true);

	public:
		void SetParent(VolumeInterface1* parent);
		void SetParent(CollisionSystemVolume* parent);
		void SetPosition(Vector3 position);
		void AddPosition(Vector3 vector);
		void SetRotation(float yaw, float pitch, float roll); // Radian
		void LookAt(Vector3 direction);
		void Rotate(HMatrix44 rotate);
		void Rotate(Quaternion quaternion);
		void SetScale(float x, float y, float z);
		void SetStatic();
		void SetDynamic();
		VolumeType GetType();
	};
}
