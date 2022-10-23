#include "Quaternion.h"

namespace SSB
{
	Quaternion::Quaternion(float x, float y, float z, float w)
	{
		_f.x = x;
		_f.y = y;
		_f.z = z;
		_f.w = w;
	}
	HMatrix33 SSB::Quaternion::GetRotateMatrix()
	{
		float q1 = _f.e[0];
		float q2 = _f.e[1];
		float q3 = _f.e[2];
		float q4 = _f.e[3];
		return HMatrix33{
			1 - 2 * q2 * q2 - 2 * q3 * q3, 2 * q1 * q2 + 2 * q3 * q4, 2 * q1 * q3 - 2 * q2 * q4,
			2 * q1 * q2 - 2 * q3 * q4, 1 - 2 * q1 * q1 - 2 * q3 * q3, 2 * q2 * q3 + 2 * q1 * q4,
			2 * q1 * q3 + 2 * q2 * q4, 2 * q2 * q3 - 2 * q1 * q4, 1 - 2 * q1 * q1 - 2 * q2 * q2
		};
	}

	Quaternion SSB::Quaternion::Conjugate()
	{
		return Quaternion(-_f.x, -_f.y, -_f.z, _f.w);
	}

	float SSB::Quaternion::Length()
	{
		return _f.x * _f.x + _f.y * _f.y + _f.z * _f.z + _f.w * _f.w;
	}

	void SSB::Quaternion::Normalize()
	{
		float invLength  = 1.0f / Length();
		_f.x *= invLength;
		_f.y *= invLength;
		_f.z *= invLength;
		_f.w *= invLength;
	}

	Quaternion SSB::Quaternion::Normal()
	{
		float invLength = 1.0f / Length();
		return Quaternion(_f.x * invLength, _f.y * invLength, _f.z * invLength, _f.w * invLength);
	}

	Quaternion SSB::Quaternion::operator+(Quaternion quaternion)
	{
		return Quaternion(_f.x + quaternion._f.x, _f.y + quaternion._f.y, _f.z + quaternion._f.z, _f.w + quaternion._f.w);
	}

	Quaternion SSB::Quaternion::operator-(Quaternion quaternion)
	{
		return Quaternion(_f.x - quaternion._f.x, _f.y - quaternion._f.y, _f.z - quaternion._f.z, _f.w - quaternion._f.w);
	}

	Quaternion SSB::Quaternion::operator*(Quaternion quaternion)
	{
		float p1 = _f.e[0];
		float p2 = _f.e[1];
		float p3 = _f.e[2];
		float p4 = _f.e[3];

		HVector4 r1{ p4, -p3, p2, p1 };
		HVector4 r2{ p3, p4, -p1, p2 };
		HVector4 r3{ -p2, p1, p4, p3 };
		HVector4 r4{ -p1, -p2, -p3, p4 };

		HVector4 quat{ quaternion._f.x, quaternion._f.y, quaternion._f.z, quaternion._f.w };
		return Quaternion(r1.Dot(quat), r2.Dot(quat), r3.Dot(quat), r4.Dot(quat));
	}

	Quaternion SSB::Quaternion::GetRotateQuaternion(Vector3 axis, float radian)
	{
		radian = radian * 0.5f;
		axis.Normalize();
		float sinVal = sin(radian);
		float cosVal = cos(radian);
		return Quaternion{ axis.GetX() * sinVal, axis.GetY() * sinVal, axis.GetZ() * sinVal, cosVal };
	}
	Quaternion::operator Float3()
	{
		return Float3{ _f.x, _f.y, _f.z };
	}
	Quaternion::operator Vector3()
	{
		return Vector3{ _f.x, _f.y, _f.z };
	}
}
