#include "Vector.h"
#include <math.h>
#include <exception>

namespace SSB
{
	float SSB::Vector2::LengthSquare() const
	{
		return x * x + y * y;
	}

	float SSB::Vector2::Length() const
	{
		return sqrt(LengthSquare());
	}

	float SSB::Vector2::Dot(const Vector2 vec)
	{
		return x * vec.x + y * vec.y;
	}

	SSB::Vector2 SSB::Vector2::Cross(const Vector2 vec)
	{
		class UnableCrossException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require Vector2 Cross Operation";
			}
		};

		throw UnableCrossException();

		return Vector2();
	}

	void SSB::Vector2::Normalize()
	{
		float invLength = 1.0f / Length();
		x = x * invLength;
		y = y * invLength;
	}

	SSB::Vector2 SSB::Vector2::Identity()
	{
		float invLength = 1.0f / Length();
		return Vector2(x * invLength, y * invLength);
	}

	void SSB::Vector2::Clear()
	{
		x = y = 0;
	}

	SSB::Vector2 SSB::Vector2::operator+(const Vector2 vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	void SSB::Vector2::operator+=(const Vector2 vec)
	{
		x += vec.x;
		y += vec.y;
	}

	SSB::Vector2 SSB::Vector2::operator-(const Vector2 vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}
	void Vector2::operator-=(const Vector2 vec)
	{
		x = x - vec.x;
		y = y - vec.y;
	}
	Vector2 Vector2::operator*(float scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}
	Vector2 Vector2::operator/(float scalar) const
	{
		float invScalar = 1.0f / scalar;
		return operator*(invScalar);
	}
	float Vector3::LengthSquare() const
	{
		return x * x + y * y + z * z;
	}
	float Vector3::Length() const
	{
		return sqrt(LengthSquare());
	}
	float Vector3::Dot(const Vector3 vec)
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}
	Vector3 Vector3::Cross(const Vector3 vec)
	{
		return Vector3(y * vec.z - vec.y * z, z * vec.x - x * vec.z, x * vec.y - vec.x * y);
	}
	void Vector3::Normalize()
	{
		float invLength = 1.0f / Length();
		x = x * invLength;
		y = y * invLength;
		z = z * invLength;
	}
	Vector3 Vector3::Identity()
	{
		float invLength = 1.0f / Length();
		return Vector3(x * invLength, y * invLength, z * invLength);
	}
	void Vector3::Clear()
	{
		x = y = z = 0.0f;
	}
	Vector3 Vector3::operator+(const Vector3 vec) const
	{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}
	void Vector3::operator+=(const Vector3 vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}
	Vector3 Vector3::operator-(const Vector3 vec) const
	{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}
	void Vector3::operator-=(const Vector3 vec)
	{
		x = x - vec.x;
		y = y - vec.y;
		z = z - vec.z;
	}
	Vector3 Vector3::operator*(float scalar) const
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}
	Vector3 Vector3::operator/(float scalar) const
	{
		float invScalar = 1.0f / scalar;
		return operator*(invScalar);
	}
	float Vector4::LengthSquare() const
	{
		return x * x + y * y + z * z;
	}
	float Vector4::Length() const
	{
		return sqrt(LengthSquare());
	}
	float Vector4::Dot(const Vector4 vec)
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}
	Vector4 Vector4::Cross(const Vector4 vec)
	{
		return Vector4(y * vec.z - vec.y * z, z * vec.x - x * vec.z, x * vec.y - vec.x * y, 0);
	}
	void Vector4::Normalize()
	{
		float invLength = 1.0f / Length();
		x = x * invLength;
		y = y * invLength;
		z = z * invLength;
	}
	Vector4 Vector4::Identity()
	{
		float invLength = 1.0f / Length();
		return Vector4(x * invLength, y * invLength, z * invLength, w);
	}
	void Vector4::Clear()
	{
		x = y = z = 0.0f;
	}
	Vector4 Vector4::operator+(const Vector4 vec) const
	{
		return Vector4(x + vec.x, y + vec.y, z + vec.z, w);
	}
	void Vector4::operator+=(const Vector4 vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}
	Vector4 Vector4::operator-(const Vector4 vec) const
	{
		return Vector4(x - vec.x, y - vec.y, z - vec.z, w);
	}
	void Vector4::operator-=(const Vector4 vec)
	{
		x = x - vec.x;
		y = y - vec.y;
		z = z - vec.z;
	}
	Vector4 Vector4::operator*(float scalar) const
	{
		return Vector4(x * scalar, y * scalar, z * scalar, w);
	}
	Vector4 Vector4::operator/(float scalar) const
	{
		float invScalar = 1.0f / scalar;
		return operator*(invScalar);
	}
}
