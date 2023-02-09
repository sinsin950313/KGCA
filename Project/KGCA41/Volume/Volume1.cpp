#include "Volume1.h"
#include "HCCalculator.h"
#include "Common.h"

namespace SSB
{
	const VolumeInterface1 Volume1::DefaultVolume;

	void Volume1::SetScale(float x, float y, float z)
	{
		_data.Scale = { x, y, z };
	}
	void Volume1::SetRotation(float yaw, float pitch, float roll)
	{
		Quaternion yawQuaternion = Quaternion::GetRotateQuaternion({ 0, 1, 0 }, yaw);
		Quaternion pitchQuaternion = Quaternion::GetRotateQuaternion({ 1, 0, 0 }, pitch);
		Quaternion rollQuaternion = Quaternion::GetRotateQuaternion({ 0, 0, 1 }, roll);
		Quaternion totalQuaternionRotate = yawQuaternion * pitchQuaternion * rollQuaternion;

		Rotate(totalQuaternionRotate);
	}
	void Volume1::LookAt(Vector3 direction)
	{
		direction.Normalize();
		Vector3 up{ 0, 1, 0 };
		{
			Vector3 tmp = direction;
			if (ZeroFloat(abs(tmp.GetY() - up.GetY())))
			{
				up = { -1, 0, 0 };
			}
		}
		Vector3 right = up.Cross(direction);
		up = direction.Cross(right);
		_data.Rotation = 
		{
			right.GetX(), right.GetY(), right.GetZ(),
			up.GetX(), up.GetY(), up.GetZ(),
			direction.GetX(), direction.GetY(), direction.GetZ()
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
	VolumeData Volume1::GetLocalVolumeData()
	{
		return _data;
	}
	void Volume1::SetPosition(Vector3 position)
	{
		_data.Position = position;
	}
	void Volume1::AddPosition(Vector3 vector)
	{
		_data.Position = _data.Position + vector;
	}
	Volume1::Volume1() : _data{Vector3(), Matrix33(), { 1, 1, 1 }}
	{
	}
	void Volume1::SetParent(VolumeInterface1* parent)
	{
		VolumeData worldData;
		worldData.Position = GetWorldPosition();
		worldData.Rotation = GetWorldRotation();
		worldData.Scale = GetWorldScale();

		_parent = parent;
		_data.Position = worldData.Position - _parent->GetWorldPosition();
		_data.Rotation = worldData.Rotation * _parent->GetWorldRotation().Transpose();

		Vector3 parentScale = _parent->GetWorldScale();
		float width = worldData.Scale.GetX() / parentScale.GetX();
		float height = worldData.Scale.GetY() / parentScale.GetY();
		float depth = worldData.Scale.GetZ() / parentScale.GetZ();
		_data.Scale = { width, height, depth };
	}
	Vector3 Volume1::GetWorldPosition() const
	{
		Vector3 delta = GetLocalPosition();

		Vector3 parentScale = _parent->GetWorldScale();
		float x = delta.GetX() * parentScale.GetX();
		float y = delta.GetY() * parentScale.GetY();
		float z = delta.GetZ() * parentScale.GetZ();
		Vector3 local { x, y, z };

		return _parent->GetWorldPosition() + local * _parent->GetWorldRotation();
	}
	Matrix33 Volume1::GetWorldRotation() const
	{
		return _parent->GetWorldRotation() * GetLocalRotation();
	}
	Vector3 Volume1::GetWorldScale() const
	{
		auto parentScale = _parent->GetWorldScale();
		auto localScale = GetLocalScale();
		return { parentScale.GetX() * localScale.GetX(), parentScale.GetY() * localScale.GetY(), parentScale.GetZ() * localScale.GetZ() };
	}
	Vector3 Volume1::GetLocalPosition() const
	{
		return _data.Position;
	}
	Matrix33 Volume1::GetLocalRotation() const
	{
		return _data.Rotation;
	}
	Vector3 Volume1::GetLocalScale() const
	{
		return _data.Scale;
	}
	std::vector<Vector3> Vertex1Volume::GetWorldBaseVertices()
	{
		return { GetWorldPosition() };
	}
	std::vector<TriangleData> Vertex1Volume::GetWorldBaseTriangles()
	{
		return std::vector<TriangleData>();
	}
	Vertex1Volume::operator VolumeData()
	{
		return VolumeData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale()
		};
	}
	Vertex1Volume::operator AABBData()
	{
		return AABBData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			GetWorldPosition(), GetWorldPosition()
		};
	}
	Vertex1Volume::operator OBBData()
	{
		return OBBData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			FDelta, FDelta, FDelta
		};
	}
	Vertex1Volume::operator SphereData()
	{
		return SphereData{
			GetWorldPosition(), GetWorldRotation(), GetWorldScale(),
			FDelta
		};
	}
}
