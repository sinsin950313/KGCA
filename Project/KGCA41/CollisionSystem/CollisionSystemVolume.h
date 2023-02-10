#pragma once

#include "Volume1.h"
#include "CollisionSystemVolumeType.h"

namespace SSB
{
	// For Static-Dynamic system
	class CollisionSystemVolume
	{
	private:
		VolumeType _type;
		bool _isStatic;

	protected:
		Volume1* _volume;

	public:
		CollisionSystemVolume(VolumeType type, Volume1* volume, bool isStatic = true);

	private:
		void UpdateToCollisionSystem();
		Volume1* GetVolumeOrigin();

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
		bool IsStatic();
		std::vector<Vector3> GetWorldBaseVertices();
		std::vector<TriangleData> GetWorldBaseTriangles();

	public:
		operator AABBData();
		operator OBBData();
		operator SphereData();
	};
}
