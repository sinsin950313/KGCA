#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

namespace SSB
{
	Vector2 operator*(Vector2 vec, Matrix22 mat);
	Vector3 operator*(Vector3 vec, Matrix33 mat);
	HVector3 operator*(HVector3 vec, HMatrix33 mat);
	HVector4 operator*(HVector4 vec, HMatrix44 mat);
	Vector3 operator*(Vector3 vec, Quaternion quat);
	Vector3 operator*(Quaternion quat, Vector3 vec);
	Vector3 Rotate(Vector3 vec, Vector3 axis, float radian);
	Vector3 Lerp(Vector3 a, Vector3 b, float t);
	Quaternion SLerp(Quaternion a, Quaternion b, float t);
	void Decompose(HMatrix44 matrix, Vector3& scale, Quaternion& rotation, Vector3 translation);
}
