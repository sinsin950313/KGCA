#include "HCCalculator.h"

namespace SSB
{
	Vector2 SSB::operator*(Vector2 vec, Matrix22 mat)
	{
		return Vector2(vec.Dot(mat.GetColumn(0)), vec.Dot(mat.GetColumn(1)));
	}

	Vector3 SSB::operator*(Vector3 vec, Matrix33 mat)
	{
		return Vector3(vec.Dot(mat.GetColumn(0)), vec.Dot(mat.GetColumn(1)), vec.Dot(mat.GetColumn(2)));
	}

	HVector3 SSB::operator*(HVector3 vec, HMatrix33 mat)
	{
		return HVector3(vec.Dot(mat.GetColumn(0)), vec.Dot(mat.GetColumn(1)), vec.Dot(mat.GetColumn(2)));
	}

	HVector4 SSB::operator*(HVector4 vec, HMatrix44 mat)
	{
		return HVector4(vec.Dot(mat.GetColumn(0)), vec.Dot(mat.GetColumn(1)), vec.Dot(mat.GetColumn(2)), vec.Dot(mat.GetColumn(3)));
	}
	Vector3 operator*(Vector3 vec, Quaternion quat)
	{
		Quaternion tmp{ vec.GetX(), vec.GetY(), vec.GetZ(), 0 };
		Vector3 result = tmp * quat;
		return result;
	}
	Vector3 operator*(Quaternion quat, Vector3 vec)
	{
		Quaternion qVec{ vec.GetX(), vec.GetY(),vec.GetZ(), 0 };
		return quat * qVec;
	}
	Vector3 Rotate(Vector3 vec, Vector3 axis, float radian)
	{
		Quaternion q = Quaternion::GetRotateQuaternion(axis, radian);
		return q * vec * q.Conjugate();
	}
}
