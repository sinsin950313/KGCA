#include "Volume1.h"
#include "HCCalculator.h"

namespace SSB
{
	void Volume1::SetScale(float width, float height, float depth)
	{
		_data.Scale = { width, height, depth };
	}
	void Volume1::SetRotation(float yaw, float pitch, float roll)
	{
		Quaternion yawQuaternion = Quaternion::GetRotateQuaternion({ 0, 1, 0 }, yaw);
		Quaternion pitchQuaternion = Quaternion::GetRotateQuaternion({ 1, 0, 0 }, pitch);
		Quaternion rollQuaternion = Quaternion::GetRotateQuaternion({ 0, 0, 1 }, roll);

		Vector3 front = { 0, 0, 1 };
		front = front * yawQuaternion * pitchQuaternion * rollQuaternion;
		front.Normalize();

		Vector3 up = { 0, 1, 0 };
		up = up * yawQuaternion * pitchQuaternion * rollQuaternion;
		up.Normalize();

		Vector3 right = { 1, 0, 0 };
		right = right * yawQuaternion * pitchQuaternion * rollQuaternion;
		right.Normalize();

		_data.Rotation = 
		{ 
			right.GetX(), right.GetY(), right.GetZ(),
			up.GetX(), up.GetY(), up.GetZ(), 
			front.GetX(), front.GetY(), front.GetZ() 
		};
	}
	void SSB::Volume1::Rotate(HMatrix44 rotate)
	{
		_data.Rotation = _data.Rotation * rotate;
	}
	void SSB::Volume1::Rotate(Quaternion quaternion)
	{
		HMatrix44 rot{ (Float33)quaternion.GetRotateMatrix(), Float3{ 0, 0, 0} };
		_data.Rotation = _data.Rotation * rot;
	}
	void Volume1::SetPosition(Vector3 position)
	{
		_data.Position = position;
	}
	void Volume1::AddPosition(Vector3 vector)
	{
		_data.Position = _data.Position + vector;
	}
	Volume1::Volume1(CollideCheckDelegate* collideDelegate) : _collideDelegate(collideDelegate), _parent(&DefaultVolume)
	{
	}
	void Volume1::SetParent(Volume1* parent)
	{
		VolumeData worldData;
		worldData.Position = GetPosition();
		worldData.Rotation = GetRotation();
		worldData.Scale = GetScale();

		_parent = parent;
		_data.Position = worldData.Position - _parent->GetPosition();
		_data.Rotation = worldData.Rotation * _parent->GetRotation().Transpose();

		Vector3 parentScale = _parent->GetScale();
		float width = worldData.Scale.GetX() / parentScale.GetX();
		float height = worldData.Scale.GetY() / parentScale.GetY();
		float depth = worldData.Scale.GetZ() / parentScale.GetZ();
		_data.Scale = { width, height, depth };
	}
	Vector3 Volume1::GetPosition()
	{
		return _parent->GetPosition() + _data.Position * _parent->GetRotation();
	}
	Matrix33 Volume1::GetRotation()
	{
		return _parent->GetRotation() * _data.Rotation;
	}
	Vector3 Volume1::GetScale()
	{
		return _parent->GetScale() + _data.Scale;
	}
}
