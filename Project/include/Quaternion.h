#pragma once

#include "Vector.h"
#include "Matrix.h"

namespace SSB
{
	class Quaternion
	{
	//private:
	public:
		Float4 _f;

	public:
		Quaternion() { }
		Quaternion(float x, float y, float z, float w);
		Quaternion(DirectX::FXMVECTOR vector);

	public:
		Matrix33 GetRotateMatrix();
		Quaternion Conjugate();
		float Length();
		void Normalize();
		Quaternion Normal();

	public:
		Quaternion operator+(Quaternion quaternion);
		Quaternion operator-(Quaternion quaternion);
		Quaternion operator*(Quaternion quaternion);

	public:
		static Quaternion GetRotateQuaternion(Vector3 axis, float radian);
		static Quaternion GetRotateQuaternion(Vector3 from, Vector3 to);

	public:
		operator Float3();
		operator Vector3();
		operator Float4();
		operator Vector4();
	};
}