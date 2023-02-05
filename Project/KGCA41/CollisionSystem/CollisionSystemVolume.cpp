#include "CollisionSystemVolume.h"
#include "CollisionTree1.h"

namespace SSB
{
	extern CollisionTree1* kCollisionSystem;

	CollisionSystemVolume::CollisionSystemVolume(VolumeType type, Volume1* volume, bool isStatic) : _type(type), _volume(volume), _isStatic(isStatic)
	{
		if (_isStatic)
		{
			kCollisionSystem->AddStaticCollider(_type, _volume);
		}
		else
		{
			kCollisionSystem->AddDynamicCollider(_type, _volume);
		}
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
	}
	void CollisionSystemVolume::AddPosition(Vector3 vector)
	{
		_volume->AddPosition(vector);
	}
	void CollisionSystemVolume::SetRotation(float yaw, float pitch, float roll)
	{
		_volume->SetRotation(yaw, pitch, roll);
	}
	void CollisionSystemVolume::LookAt(Vector3 direction)
	{
		_volume->LookAt(direction);
	}
	void CollisionSystemVolume::Rotate(HMatrix44 rotate)
	{
		_volume->Rotate(rotate);
	}
	void CollisionSystemVolume::Rotate(Quaternion quaternion)
	{
		_volume->Rotate(quaternion);
	}
	void CollisionSystemVolume::SetScale(float x, float y, float z)
	{
		_volume->SetScale(x, y, z);
	}
	void CollisionSystemVolume::SetStatic()
	{
		_isStatic = true;
		kCollisionSystem->Remove(_volume);
		kCollisionSystem->AddStaticCollider(GetType(), _volume);
	}
	void CollisionSystemVolume::SetDynamic()
	{
		_isStatic = true;
		kCollisionSystem->Remove(_volume);
		kCollisionSystem->AddDynamicCollider(GetType(), _volume);
	}
	VolumeType CollisionSystemVolume::GetType()
	{
		return _type;
	}
}
