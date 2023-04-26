#include "CollisionSystemVolume.h"
#include "CollisionTree1.h"

namespace SSB
{
	extern CollisionTree1* kCollisionSystem;

	CollisionSystemVolume::CollisionSystemVolume(VolumeType type, Volume1* volume, bool isStatic) : _type(type), _volume(volume), _isStatic(isStatic)
	{
		kCollisionSystem->AddCollider(this);
	}
	void CollisionSystemVolume::UpdateToCollisionSystem()
	{
		kCollisionSystem->Remove(this);
		kCollisionSystem->AddCollider(this);
	}
	void CollisionSystemVolume::SetParent(VolumeInterface1* parent)
	{
		_volume->SetParent(parent);
	}
	void CollisionSystemVolume::SetParent(CollisionSystemVolume* parent)
	{
		_volume->SetParent(parent->_volume);
	}
	void CollisionSystemVolume::SetPosition(Vector3 position)
	{
		_volume->SetPosition(position);
		UpdateToCollisionSystem();
	}
	void CollisionSystemVolume::AddPosition(Vector3 vector)
	{
		_volume->AddPosition(vector);
		UpdateToCollisionSystem();
	}
	void CollisionSystemVolume::SetRotation(float yaw, float pitch, float roll)
	{
		_volume->SetRotation(yaw, pitch, roll);
		UpdateToCollisionSystem();
	}
	void CollisionSystemVolume::LookAt(Vector3 direction)
	{
		_volume->LookAt(direction);
		UpdateToCollisionSystem();
	}
	void CollisionSystemVolume::Rotate(HMatrix44 rotate)
	{
		_volume->Rotate(rotate);
		UpdateToCollisionSystem();
	}
	void CollisionSystemVolume::Rotate(Quaternion quaternion)
	{
		_volume->Rotate(quaternion);
		UpdateToCollisionSystem();
	}
	void CollisionSystemVolume::SetScale(float x, float y, float z)
	{
		_volume->SetScale(x, y, z);
		UpdateToCollisionSystem();
	}
	void CollisionSystemVolume::SetStatic()
	{
		kCollisionSystem->Remove(this);
		_isStatic = true;
		kCollisionSystem->AddCollider(this);
	}
	void CollisionSystemVolume::SetDynamic()
	{
		kCollisionSystem->Remove(this);
		_isStatic = false;
		kCollisionSystem->AddCollider(this);
	}
	VolumeType CollisionSystemVolume::GetType()
	{
		return _type;
	}
	bool CollisionSystemVolume::IsStatic()
	{
		return _isStatic;
	}
	std::vector<Vector3> CollisionSystemVolume::GetWorldBaseVertices()
	{
		return _volume->GetWorldBaseVertices();
	}
	std::vector<TriangleData> CollisionSystemVolume::GetWorldBaseTriangles()
	{
		return _volume->GetWorldBaseTriangles();
	}
	CollisionSystemVolume::operator AABBData()
	{
		return _volume->operator SSB::AABBData();
	}
	CollisionSystemVolume::operator OBBData()
	{
		return _volume->operator SSB::OBBData();
	}
	CollisionSystemVolume::operator SphereData()
	{
		return _volume->operator SSB::SphereData();
	}
	Volume1* CollisionSystemVolume::GetVolumeOrigin()
	{
		return _volume;
	}
}
