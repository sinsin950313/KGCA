#include "Vector.h"
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

	SSB::Vector2 SSB::Vector2::Normal()
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
	Vector3 Vector3::Normal()
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

	const float HVector3::_fThreshold = 0.0001f;

	float HVector3::LengthSquare() const
	{
		return x * x + y * y;
	}
	float HVector3::Length() const
	{
		return sqrt(LengthSquare());
	}
	float HVector3::Dot(const HVector3 vec)
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}
	HVector3 HVector3::Cross(const HVector3 vec)
	{
		class UnableCrossException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require HVector3 Cross Operation";
			}
		};

		throw UnableCrossException();

		return HVector3();
	}
	void HVector3::Normalize()
	{
		float invLength = 1.0f / Length();
		x = x * invLength;
		y = y * invLength;
		if (IsVector())
		{
			z = 1.0f;
		}
		else
		{
			z = 0.0f;
		}
	}
	HVector3 HVector3::Normal()
	{
		float invLength = 1.0f / Length();
		return HVector3(x * invLength, y * invLength, IsVector() ? 0.0f : 1.0f);
	}
	void HVector3::Clear()
	{
		x = y = 0.0f;
		z = IsVector() ? 0.0f : 1.0f;
	}
	HVector3 HVector3::operator+(const HVector3 vec) const
	{
		if (!IsVector() && !vec.IsVector())
		{
			class UnableVertexAddVertexException : public std::exception
			{
			public:
				const char* what() const noexcept override
				{
					return "Require HVector3 Vertex Add Vertex Operation";
				}
			};

			throw UnableVertexAddVertexException();

			return HVector3();
		}
		else
		{
			return HVector3(x + vec.x, y + vec.y, z + vec.z);
		}
	}
	void HVector3::operator+=(const HVector3 vec)
	{
		if (!IsVector() && !vec.IsVector())
		{
			class UnableVertexAddVertexException : public std::exception
			{
			public:
				const char* what() const noexcept override
				{
					return "Require HVector3 Vertex Add Vertex Operation";
				}
			};

			throw UnableVertexAddVertexException();
		}
		else
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
		}
	}
	HVector3 HVector3::operator-(const HVector3 vec) const
	{
		return HVector3(x - vec.x, y - vec.y, z - vec.z);
	}
	void HVector3::operator-=(const HVector3 vec)
	{
		x = x - vec.x;
		y = y - vec.y;
		z = z - vec.z;
	}
	HVector3 HVector3::operator*(float scalar) const
	{
		return HVector3(x * scalar, y * scalar, z * scalar);
	}
	HVector3 HVector3::operator/(float scalar) const
	{
		float invScalar = 1.0f / scalar;
		return operator*(invScalar);
	}

	float Vector4::LengthSquare() const
	{
		return x * x + y * y + z * z + w * w;
	}
	float Vector4::Length() const
	{
		return sqrt(LengthSquare());
	}
	float Vector4::Dot(const Vector4 vec)
	{
		return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
	}
	Vector4 Vector4::Cross(const Vector4 vec)
	{
		class UnableCrossException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require Vector4 Cross Operation";
			}
		};

		throw UnableCrossException();

		return Vector4();
	}
	void Vector4::Normalize()
	{
		float invLength = 1.0f / Length();
		x /= invLength;
		y /= invLength;
		z /= invLength;
		w /= invLength;
	}
	Vector4 Vector4::Normal()
	{
		float invLength = 1.0f / Length();
		return Vector4(x * invLength, y * invLength, z * invLength, w * invLength);
	}
	void Vector4::Clear()
	{
		x = y = z = w = 0.0f;
	}
	Vector4 Vector4::operator+(const Vector4 vec) const
	{
		return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}
	void Vector4::operator+=(const Vector4 vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
	}
	Vector4 Vector4::operator-(const Vector4 vec) const
	{
		return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	}
	void Vector4::operator-=(const Vector4 vec)
	{
		x = x - vec.x;
		y = y - vec.y;
		z = z - vec.z;
		w = w - vec.w;
	}
	Vector4 Vector4::operator*(float scalar) const
	{
		return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
	}
	Vector4 Vector4::operator/(float scalar) const
	{
		float invScalar = 1.0f / scalar;
		return operator*(invScalar);
	}

	const float HVector4::_fThreshold = 0.0001f;

	float HVector4::LengthSquare() const
	{
		return x * x + y * y + z * z;
	}
	float HVector4::Length() const
	{
		return sqrt(LengthSquare());
	}
	float HVector4::Dot(const HVector4 vec)
	{
		return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
	}
	HVector4 HVector4::Cross(const HVector4 vec)
	{
		return HVector4(y * vec.z - vec.y * z, z * vec.x - x * vec.z, x * vec.y - vec.x * y, 0);
	}
	void HVector4::Normalize()
	{
		if (IsVector())
		{
			float invLength = 1.0f / Length();
			x = x * invLength;
			y = y * invLength;
			z = z * invLength;
			w = 0.0f;
		}
		else
		{
			w = 0.0f;
			Normalize();
			w = 1.0f;
		}
	}
	HVector4 HVector4::Normal()
	{
		if (IsVector())
		{
			float invLength = 1.0f / Length();
			return HVector4(x * invLength, y * invLength, z * invLength, w);
		}
		else
		{
			HVector4 v = *this;
			v.w = 0.0f;
			v = v.Normal();
			v.w = 1.0f;
			return v;
		}
	}
	void HVector4::Clear()
	{
		x = y = z = 0.0f;
		if (IsVector())
		{
			w = 0.0f;
		}
		else
		{
			w = 1.0f;
		}
	}
	HVector4 HVector4::operator+(const HVector4 vec) const
	{
		class DotAddDotException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require Dot Add Dot Operation";
			}
		};

		if (!IsVector() && !vec.IsVector())
		{
			throw DotAddDotException();
			return HVector4();
		}
		else
		{
			return HVector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
		}
	}
	void HVector4::operator+=(const HVector4 vec)
	{
		class DotAddDotException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require Dot Add Dot Operation";
			}
		};

		if (!IsVector() && !vec.IsVector())
		{
			throw DotAddDotException();
		}
		else
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
			w += vec.w;
		}
	}
	HVector4 HVector4::operator-(const HVector4 vec) const
	{
		return HVector4(x - vec.x, y - vec.y, z - vec.z, 0.0f);
	}
	void HVector4::operator-=(const HVector4 vec)
	{
		x = x - vec.x;
		y = y - vec.y;
		z = z - vec.z;
		w = 0.0f;
	}
	HVector4 HVector4::operator*(float scalar) const
	{
		return HVector4(x * scalar, y * scalar, z * scalar, w * scalar);
	}
	HVector4 HVector4::operator/(float scalar) const
	{
		float invScalar = 1.0f / scalar;
		return operator*(invScalar);
	}
}
