#include "HCCalculator.h"
#include <DirectXMath.h>

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
	Vector3 Lerp(Vector3 a, Vector3 b, float t)
	{
		DirectX::XMFLOAT3 aXmData = a;
		DirectX::XMFLOAT3 bXmData = b;

		DirectX::XMVECTOR aVec = DirectX::XMLoadFloat3(&aXmData);
		DirectX::XMVECTOR bVec = DirectX::XMLoadFloat3(&bXmData);
		DirectX::XMVECTOR x = DirectX::XMVectorLerp(aVec, bVec, t);

		DirectX::XMFLOAT3 resXm;
		DirectX::XMStoreFloat3(&resXm, x);

		return Vector3(resXm);
	}
	Quaternion SLerp(Quaternion a, Quaternion b, float t)
	{
		Float4 aData = a;
		Float4 bData = b;

		DirectX::FXMVECTOR q0 = aData;
		DirectX::FXMVECTOR q1 = bData;

		DirectX::XMVECTOR res = DirectX::XMQuaternionSlerp(q0, q1, t);

		return Quaternion(res);
	}
	void Decompose(HMatrix44 matrix, Vector3& scale, Quaternion& rotation, Vector3& translation)
	{
		DirectX::XMVECTOR s, r, t;
		DirectX::FXMMATRIX mat = matrix;
		DirectX::XMMatrixDecompose(&s, &r, &t, mat);

		DirectX::XMFLOAT4 sData;
		DirectX::XMStoreFloat4(&sData, s);
		scale = Vector3(sData.x, sData.y, sData.z);

		rotation = r;

		DirectX::XMFLOAT4 tData;
		DirectX::XMStoreFloat4(&tData, t);
		translation = Vector3(tData.x, tData.y, tData.z);
	}
}
