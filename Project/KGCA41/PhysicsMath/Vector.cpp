#include "Vector.h"
#include <exception>

namespace SSB
{
	float SSB::Vector2::LengthSquare() const
	{
		return _f.x * _f.x + _f.y * _f.y;
	}

	float SSB::Vector2::Length() const
	{
		return sqrt(LengthSquare());
	}

	float SSB::Vector2::Dot(const Vector2 vec)
	{
		return _f.x * vec._f.x + _f.y * vec._f.y;
	}

	//SSB::Vector2 SSB::Vector2::Cross(const Vector2 vec)
	//{
	//	class UnableOperationE_f.xception : public std::e_f.xception
	//	{
	//	public:
	//		const char* _f.what() const noe_f.xcept override
	//		{
	//			return "Require Vector2 Cross Operation";
	//		}
	//	};

	//	thro_f.w UnableOperationE_f.xception();

	//	return Vector2();
	//}

	void SSB::Vector2::Normalize()
	{
		float invLength = 1.0f / Length();
		_f.x = _f.x * invLength;
		_f.y = _f.y * invLength;
	}

	SSB::Vector2 SSB::Vector2::Normal()
	{
		float invLength = 1.0f / Length();
		return Vector2(_f.x * invLength, _f.y * invLength);
	}

	void SSB::Vector2::Clear()
	{
		_f.x = _f.y = 0;
	}

	SSB::Vector2 SSB::Vector2::operator+(const Vector2 vec) const
	{
		return Vector2(_f.x + vec._f.x, _f.y + vec._f.y);
	}

	void SSB::Vector2::operator+=(const Vector2 vec)
	{
		_f.x += vec._f.x;
		_f.y += vec._f.y;
	}

	SSB::Vector2 SSB::Vector2::operator-(const Vector2 vec) const
	{
		return Vector2(_f.x - vec._f.x, _f.y - vec._f.y);
	}
	void Vector2::operator-=(const Vector2 vec)
	{
		_f.x = _f.x - vec._f.x;
		_f.y = _f.y - vec._f.y;
	}
	Vector2 Vector2::operator*(float scalar) const
	{
		return Vector2(_f.x * scalar, _f.y * scalar);
	}
	Vector2 Vector2::operator/(float scalar) const
	{
		float invScalar = 1.0f / scalar;
		return operator*(invScalar);
	}

	Vector3::Vector3(DirectX::XMFLOAT3 data)
	{
		_f.x = data.x;
		_f.y = data.y;
		_f.z = data.z;
	}

	float Vector3::LengthSquare() const
	{
		return _f.x * _f.x + _f.y * _f.y + _f.z * _f.z;
	}
	float Vector3::Length() const
	{
		return sqrt(LengthSquare());
	}
	float Vector3::Dot(const Vector3 vec)
	{
		return _f.x * vec._f.x + _f.y * vec._f.y + _f.z * vec._f.z;
	}
	Vector3 Vector3::Cross(const Vector3 vec)
	{
		return Vector3(_f.y * vec._f.z - vec._f.y * _f.z, _f.z * vec._f.x - _f.x * vec._f.z, _f.x * vec._f.y - vec._f.x * _f.y);
	}
	void Vector3::Normalize()
	{
		float invLength = 1.0f / Length();
		_f.x = _f.x * invLength;
		_f.y = _f.y * invLength;
		_f.z = _f.z * invLength;
	}
	Vector3 Vector3::Normal()
	{
		float invLength = 1.0f / Length();
		return Vector3(_f.x * invLength, _f.y * invLength, _f.z * invLength);
	}
	void Vector3::Clear()
	{
		_f.x = _f.y = _f.z = 0.0f;
	}
	Vector3 Vector3::operator+(const Vector3 vec) const
	{
		return Vector3(_f.x + vec._f.x, _f.y + vec._f.y, _f.z + vec._f.z);
	}
	void Vector3::operator+=(const Vector3 vec)
	{
		_f.x += vec._f.x;
		_f.y += vec._f.y;
		_f.z += vec._f.z;
	}
	Vector3 Vector3::operator-(const Vector3 vec) const
	{
		return Vector3(_f.x - vec._f.x, _f.y - vec._f.y, _f.z - vec._f.z);
	}
	void Vector3::operator-=(const Vector3 vec)
	{
		_f.x = _f.x - vec._f.x;
		_f.y = _f.y - vec._f.y;
		_f.z = _f.z - vec._f.z;
	}
	Vector3 Vector3::operator*(float scalar) const
	{
		return Vector3(_f.x * scalar, _f.y * scalar, _f.z * scalar);
	}
	Vector3 Vector3::operator/(float scalar) const
	{
		float invScalar = 1.0f / scalar;
		return operator*(invScalar);
	}

	Vector3::operator DirectX::XMFLOAT3()
	{
		return DirectX::XMFLOAT3(_f.x, _f.y, _f.z);
	}

	const float HVector3::_fThreshold = 0.0001f;

	//float HVector3::LengthSquare() const
	//{
	//	return _f.x * _f.x + _f.y * _f.y;
	//}
	//float HVector3::Length() const
	//{
	//	return sqrt(LengthSquare());
	//}
	float HVector3::Dot(const HVector3 vec)
	{
		return _f.x * vec._f.x + _f.y * vec._f.y + _f.z * vec._f.z;
	}
	//HVector3 HVector3::Cross(const HVector3 vec)
	//{
	//	class UnableOperationE_f.xception : public std::e_f.xception
	//	{
	//	public:
	//		const char* _f.what() const noe_f.xcept override
	//		{
	//			return "Require HVector3 Cross Operation";
	//		}
	//	};

	//	thro_f.w UnableOperationE_f.xception();

	//	return HVector3();
	//}
	void HVector3::Normalize()
	{
		if (IsVector())
		{
			Vector2 v = *this;
			float invLength = 1.0f / v.Length();
			_f.x *= invLength;
			_f.y *= invLength;
			_f.z = 0.0f;
		}
		else
		{
			_f.x /= _f.z;
			_f.y /= _f.z;
			_f.z = 1.0f;
		}
	}
	HVector3 HVector3::Normal()
	{
		float xVal, yVal, zVal;
		if (IsVector())
		{
			Vector2 v = *this;
			float invLength = 1.0f / v.Length();
			xVal = _f.x * invLength;
			yVal = _f.y * invLength;
			zVal = 0.0f;
		}
		else
		{
			xVal = _f.x / _f.z;
			yVal = _f.y / _f.z;
			zVal = 1.0f;
		}
		return HVector3(xVal, yVal, zVal);
	}
	HVector3::operator Float2() const
	{
		return IsVector() ? (Float2)(Vector2{ _f.x, _f.y }.Normal()) : Float2{ _f.x / _f.z, _f.y / _f.z };
	}
	HVector3::operator Vector2() const
	{
		return IsVector() ? Vector2{ _f.x, _f.y }.Normal() : Vector2{ _f.x / _f.z, _f.y / _f.z };
	}
	//void HVector3::Clear()
	//{
	//	_f.x = _f.y = 0.0f;
	//	_f.z = IsVector() ? 0.0f : 1.0f;
	//}
	//HVector3 HVector3::operator+(const HVector3 vec) const
	//{
	//	if (!IsVector() && !vec.IsVector())
	//	{
	//		class UnableVerte_f.xAddVerte_f.xE_f.xception : public std::e_f.xception
	//		{
	//		public:
	//			const char* _f.what() const noe_f.xcept override
	//			{
	//				return "Require HVector3 Verte_f.x Add Verte_f.x Operation";
	//			}
	//		};

	//		thro_f.w UnableVerte_f.xAddVerte_f.xE_f.xception();

	//		return HVector3();
	//	}
	//	else
	//	{
	//		return HVector3(_f.x + vec._f.x, _f.y + vec._f.y, _f.z + vec._f.z);
	//	}
	//}
	//void HVector3::operator+=(const HVector3 vec)
	//{
	//	if (!IsVector() && !vec.IsVector())
	//	{
	//		class UnableVerte_f.xAddVerte_f.xE_f.xception : public std::e_f.xception
	//		{
	//		public:
	//			const char* _f.what() const noe_f.xcept override
	//			{
	//				return "Require HVector3 Verte_f.x Add Verte_f.x Operation";
	//			}
	//		};

	//		thro_f.w UnableVerte_f.xAddVerte_f.xE_f.xception();
	//	}
	//	else
	//	{
	//		_f.x += vec._f.x;
	//		_f.y += vec._f.y;
	//		_f.z += vec._f.z;
	//	}
	//}
	//HVector3 HVector3::operator-(const HVector3 vec) const
	//{
	//	return HVector3(_f.x - vec._f.x, _f.y - vec._f.y, _f.z - vec._f.z);
	//}
	//void HVector3::operator-=(const HVector3 vec)
	//{
	//	_f.x = _f.x - vec._f.x;
	//	_f.y = _f.y - vec._f.y;
	//	_f.z = _f.z - vec._f.z;
	//}
	//HVector3 HVector3::operator*(float scalar) const
	//{
	//	return HVector3(_f.x * scalar, _f.y * scalar, _f.z * scalar);
	//}
	//HVector3 HVector3::operator/(float scalar) const
	//{
	//	float invScalar = 1.0f / scalar;
	//	return operator*(invScalar);
	//}

	float Vector4::LengthSquare() const
	{
		return _f.x * _f.x + _f.y * _f.y + _f.z * _f.z + _f.w * _f.w;
	}
	float Vector4::Length() const
	{
		return sqrt(LengthSquare());
	}
	//float Vector4::Dot(const Vector4 vec)
	//{
	//	return _f.x * vec._f.x + _f.y * vec._f.y + _f.z * vec._f.z + _f.w * vec._f.w;
	//}
	void Vector4::Normalize()
	{
		float invLength = 1.0f / Length();
		_f.x /= invLength;
		_f.y /= invLength;
		_f.z /= invLength;
		_f.w /= invLength;
	}
	Vector4 Vector4::Normal()
	{
		float invLength = 1.0f / Length();
		return Vector4(_f.x * invLength, _f.y * invLength, _f.z * invLength, _f.w * invLength);
	}
	void Vector4::Clear()
	{
		_f.x = _f.y = _f.z = _f.w = 0.0f;
	}
	Vector4 Vector4::operator+(const Vector4 vec) const
	{
		return Vector4(_f.x + vec._f.x, _f.y + vec._f.y, _f.z + vec._f.z, _f.w + vec._f.w);
	}
	void Vector4::operator+=(const Vector4 vec)
	{
		_f.x += vec._f.x;
		_f.y += vec._f.y;
		_f.z += vec._f.z;
		_f.w += vec._f.w;
	}
	Vector4 Vector4::operator-(const Vector4 vec) const
	{
		return Vector4(_f.x - vec._f.x, _f.y - vec._f.y, _f.z - vec._f.z, _f.w - vec._f.w);
	}
	void Vector4::operator-=(const Vector4 vec)
	{
		_f.x = _f.x - vec._f.x;
		_f.y = _f.y - vec._f.y;
		_f.z = _f.z - vec._f.z;
		_f.w = _f.w - vec._f.w;
	}
	Vector4 Vector4::operator*(float scalar) const
	{
		return Vector4(_f.x * scalar, _f.y * scalar, _f.z * scalar, _f.w * scalar);
	}
	Vector4 Vector4::operator/(float scalar) const
	{
		float invScalar = 1.0f / scalar;
		return operator*(invScalar);
	}

	const float HVector4::_fThreshold = 0.0001f;

	//float HVector4::LengthSquare() const
	//{
	//	return _f.x * _f.x + _f.y * _f.y + _f.z * _f.z;
	//}
	//float HVector4::Length() const
	//{
	//	return sqrt(LengthSquare());
	//}
	float HVector4::Dot(const HVector4 vec)
	{
		return _f.x * vec._f.x + _f.y * vec._f.y + _f.z * vec._f.z + _f.w * vec._f.w;
	}
	//HVector4 HVector4::Cross(const HVector4 vec)
	//{
	//	return HVector4(_f.y * vec._f.z - vec._f.y * _f.z, _f.z * vec._f.x - _f.x * vec._f.z, _f.x * vec._f.y - vec._f.x * _f.y, 0);
	//}
	void HVector4::Normalize()
	{
		if (IsVector())
		{
			Vector3 v = *this;
			float invLength = 1.0f / v.Length();
			_f.x *= invLength;
			_f.y *= invLength;
			_f.z *= invLength;
			_f.w = 0.0f;
		}
		else
		{
			_f.x /= _f.w;
			_f.y /= _f.w;
			_f.z /= _f.w;
			_f.w = 1.0f;
		}
	}
	HVector4 HVector4::Normal()
	{
		float xVal, yVal, zVal, wVal;
		if (IsVector())
		{
			Vector3 v = *this;
			float invLength = 1.0f / v.Length();
			xVal = _f.x * invLength;
			yVal = _f.y * invLength;
			zVal = _f.z * invLength;
			wVal = 0.0f;
		}
		else
		{
			xVal = _f.x / _f.w;
			yVal = _f.y / _f.w;
			zVal = _f.z / _f.w;
			wVal = 1.0f;
		}
		return HVector4(xVal, yVal, zVal, wVal);
	}
	//void HVector4::Clear()
	//{
	//	_f.x = _f.y = _f.z = 0.0f;
	//	if (IsVector())
	//	{
	//		_f.w = 0.0f;
	//	}
	//	else
	//	{
	//		_f.w = 1.0f;
	//	}
	//}
	//HVector4 HVector4::operator+(const HVector4 vec) const
	//{
	//	class DotAddDotE_f.xception : public std::e_f.xception
	//	{
	//	public:
	//		const char* _f.what() const noe_f.xcept override
	//		{
	//			return "Require Dot Add Dot Operation";
	//		}
	//	};

	//	if (!IsVector() && !vec.IsVector())
	//	{
	//		thro_f.w DotAddDotE_f.xception();
	//		return HVector4();
	//	}
	//	else
	//	{
	//		return HVector4(_f.x + vec._f.x, _f.y + vec._f.y, _f.z + vec._f.z, _f.w + vec._f.w);
	//	}
	//}
	//void HVector4::operator+=(const HVector4 vec)
	//{
	//	class DotAddDotE_f.xception : public std::e_f.xception
	//	{
	//	public:
	//		const char* _f.what() const noe_f.xcept override
	//		{
	//			return "Require Dot Add Dot Operation";
	//		}
	//	};

	//	if (!IsVector() && !vec.IsVector())
	//	{
	//		thro_f.w DotAddDotE_f.xception();
	//	}
	//	else
	//	{
	//		_f.x += vec._f.x;
	//		_f.y += vec._f.y;
	//		_f.z += vec._f.z;
	//		_f.w += vec._f.w;
	//	}
	//}
	//HVector4 HVector4::operator-(const HVector4 vec) const
	//{
	//	return HVector4(_f.x - vec._f.x, _f.y - vec._f.y, _f.z - vec._f.z, 0.0f);
	//}
	//void HVector4::operator-=(const HVector4 vec)
	//{
	//	_f.x = _f.x - vec._f.x;
	//	_f.y = _f.y - vec._f.y;
	//	_f.z = _f.z - vec._f.z;
	//	_f.w = 0.0f;
	//}
	//HVector4 HVector4::operator*(float scalar) const
	//{
	//	return HVector4(_f.x * scalar, _f.y * scalar, _f.z * scalar, _f.w * scalar);
	//}
	//HVector4 HVector4::operator/(float scalar) const
	//{
	//	float invScalar = 1.0f / scalar;
	//	return operator*(invScalar);
	//}

	HVector4::operator Float3() const
	{
		return IsVector() ? (Float3)(Vector3{ _f.x, _f.y, _f.z }.Normal()) : Float3{ _f.x / _f.w, _f.y / _f.w, _f.z / _f.w };
	}
	HVector4::operator Vector3() const
	{
		return IsVector() ? Vector3{ _f.x, _f.y, _f.z }.Normal() : Vector3{ _f.x / _f.w, _f.y / _f.w, _f.z / _f.w };
	}
	Float4::operator DirectX::FXMVECTOR()
	{
		DirectX::XMFLOAT4 tmp(x, y, z, w);
		return DirectX::XMLoadFloat4(&tmp);
	}
}
