#include "Matrix.h"
#include <exception>

namespace SSB
{
	Matrix22::Matrix22()
	{
		Identity();
	}
	Matrix22::Matrix22(float e11, float e12, float e21, float e22)
	{
		row[0].x = e11; row[0].y = e12;
		row[1].x = e21; row[1].y = e22;
	}
	void SSB::Matrix22::Identity()
	{
		e11 = 1; e12 = 0;
		e21 = 0; e22 = 1;
	}

	Matrix22 SSB::Matrix22::Transpose()
	{
		return Matrix22(
			e11, e21,
			e12, e22);
	}
	Matrix22 Matrix22::Inverse()
	{
		return Matrix22(
			e22, -e12,
			-e21, e11).operator*(1 / (e11 * e22 - e12 * e21));
	}
	Vector2 Matrix22::GetRow(int i)
	{
		return Vector2(row[i].x, row[i].y);
	}
	Vector2 Matrix22::GetColumn(int i)
	{
		return Vector2(row[0].e[i], row[1].e[i]);
	}
	Matrix22 Matrix22::operator+(const Matrix22 matrix) const
	{
		return Matrix22(
			e11 + matrix.e11, e12 + matrix.e12, 
			e21 + matrix.e21, e22 + matrix.e22);
	}
	void Matrix22::operator+=(const Matrix22 matrix)
	{
		e11 += matrix.e11; e12 += matrix.e12;
		e21 += matrix.e21; e22 += matrix.e22;
	}
	Matrix22 Matrix22::operator-(const Matrix22 matrix) const
	{
		return Matrix22(
			e11 - matrix.e11, e12 - matrix.e12, 
			e21 - matrix.e21, e22 - matrix.e22);
	}
	void Matrix22::operator-=(const Matrix22 matrix)
	{
		e11 -= matrix.e11; e12 -= matrix.e12;
		e21 -= matrix.e21; e22 -= matrix.e22;
	}
	Matrix22 Matrix22::operator*(float scalar) const
	{
		return Matrix22(
			e11 * scalar, e12 * scalar, 
			e21 * scalar, e22 * scalar);
	}
	Matrix22 Matrix22::operator*(Matrix22 matrix) const
	{
		Matrix22 m{
			0, 0,
			0, 0 };
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				m.row[i].e[j] += (row[i].e[j] * matrix.row[j].e[i]);
			}
		}
		return m;
	}

	Matrix33::Matrix33()
	{
		Identity();
	}
	Matrix33::Matrix33(float e11, float e12, float e13, float e21, float e22, float e23, float e31, float e32, float e33)
	{
		row[0].x = e11; row[0].y = e12; row[0].z = e13;
		row[1].x = e21; row[1].y = e22; row[1].z = e23;
		row[2].x = e31; row[2].y = e32; row[2].z = e33;
	}
	void Matrix33::Identity()
	{
		e11 = 1; e12 = 0; e13 = 0;
		e21 = 0; e22 = 1; e23 = 0;
		e31 = 0; e32 = 0; e33 = 1;
	}
	Matrix33 Matrix33::Transpose()
	{
		return Matrix33(
			e11, e21, e31,
			e12, e22, e32,
			e13, e23, e33);
	}
	Matrix33 Matrix33::Inverse()
	{
		class UnableCalculateException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require Matrix33 Inverse Operation";
			}
		};

		throw UnableCalculateException();
		return Matrix33();
	}
	Vector3 Matrix33::GetRow(int i)
	{
		return Vector3(row[i].x, row[i].y, row[i].z);
	}
	Vector3 Matrix33::GetColumn(int i)
	{
		return Vector3(row[0].e[i], row[1].e[i], row[2].e[i]);
	}
	Matrix33 Matrix33::operator+(const Matrix33 matrix) const
	{
		return Matrix33(
			e11 + matrix.e11, e12 + matrix.e12, e13 + matrix.e13,
			e21 + matrix.e21, e22 + matrix.e22, e23 + matrix.e23,
			e31 + matrix.e31, e32 + matrix.e32, e33 + matrix.e33);
	}
	void Matrix33::operator+=(const Matrix33 matrix)
	{
		e11 += matrix.e11; e12 += matrix.e12; e13 += matrix.e13;
		e21 += matrix.e21; e22 += matrix.e22; e23 += matrix.e23;
		e31 += matrix.e31; e32 += matrix.e32; e33 += matrix.e33;
	}
	Matrix33 Matrix33::operator-(const Matrix33 matrix) const
	{
		return Matrix33(
			e11 - matrix.e11, e12 - matrix.e12, e13 - matrix.e13,
			e21 - matrix.e21, e22 - matrix.e22, e23 - matrix.e13,
			e31 - matrix.e31, e32 - matrix.e32, e33 - matrix.e33);
	}
	void Matrix33::operator-=(const Matrix33 matrix)
	{
		e11 -= matrix.e11; e12 -= matrix.e12; e13 -= matrix.e13;
		e21 -= matrix.e21; e22 -= matrix.e22; e23 -= matrix.e23;
		e31 -= matrix.e31; e32 -= matrix.e32; e33 -= matrix.e33;
	}
	Matrix33 Matrix33::operator*(float scalar) const
	{
		return Matrix33(
			e11 * scalar, e12 * scalar, e13 * scalar,
			e21 * scalar, e22 * scalar, e23 * scalar,
			e31 * scalar, e32 * scalar, e33 * scalar);
	}
	Matrix33 Matrix33::operator*(Matrix33 matrix) const
	{
		Matrix33 m{
			0, 0, 0,
			0, 0, 0,
			0, 0, 0};
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				m.row[i].e[j] += (row[i].e[j] * matrix.row[j].e[i]);
			}
		}
		return m;
	}

	const float HMatrix33::_fThreshold = 0.0001f;

	HMatrix33::HMatrix33()
	{
		Identity();
	}
	HMatrix33::HMatrix33(float e11, float e12, float e21, float e22, float e31, float e32)
	{
		row[0].x = e11; row[0].y = e12; row[0].z = 0;
		row[1].x = e21; row[1].y = e22; row[1].z = 0;
		row[2].x = e31; row[2].y = e32; row[2].z = 1;
	}
	void HMatrix33::Identity()
	{
		e11 = 1; e12 = 0; e13 = 0;
		e21 = 0; e22 = 1; e23 = 0;
		e31 = 0; e32 = 0; e33 = 1;
	}
	HMatrix33 HMatrix33::Transpose()
	{
		HMatrix33 m;
		m.e11 = e11; m.e12 = e21; m.e13 = e31;
		m.e21 = e12; m.e22 = e22; m.e23 = e32;
		m.e31 = e13; m.e32 = e23; m.e33 = e33;
		return m;
	}
	HMatrix33 HMatrix33::Inverse()
	{
		if ((!(IsZero(e11) && IsZero(e12) &&
			IsZero(e21) && IsZero(e22))) && 
			(!(IsZero(e31) && IsZero(e32))))
		{
			class MixedHMatrixInverseException : public std::exception
			{
			public:
				const char* what() const noexcept override
				{
					return "HMatrix33 Is Mixed State";
				}
			};

			throw MixedHMatrixInverseException();
		}
		else
		{
			HMatrix33 m;
			m.e11 = e11; m.e12 = e21;
			m.e21 = e12; m.e22 = e22;
			m.e31 = -e31; m.e32 = -e32;
			return m;
		}
	}
	HVector3 HMatrix33::GetRow(int i)
	{
		return HVector3(row[i].x, row[i].y, row[i].z);
	}
	HVector3 HMatrix33::GetColumn(int i)
	{
		return HVector3(row[0].e[i], row[1].e[i], row[2].e[i]);
	}
	HMatrix33 HMatrix33::operator+(const HMatrix33 matrix) const
	{
		class UnableCalculateException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require HMatrix44 Add Operation";
			}
		};

		throw UnableCalculateException();
		return HMatrix33();
	}
	void HMatrix33::operator+=(const HMatrix33 matrix)
	{
		class UnableCalculateException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require Matrix44 Add Operation";
			}
		};

		throw UnableCalculateException();
	}
	HMatrix33 HMatrix33::operator-(const HMatrix33 matrix) const
	{
		class UnableCalculateException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require Matrix44 Sub Operation";
			}
		};

		throw UnableCalculateException();
		return HMatrix33();
	}
	void HMatrix33::operator-=(const HMatrix33 matrix)
	{
		class UnableCalculateException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require Matrix44 Sub Operation";
			}
		};

		throw UnableCalculateException();
	}
	HMatrix33 HMatrix33::operator*(float scalar) const
	{
		class UnableCalculateException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require Matrix44 Mul Operation";
			}
		};

		throw UnableCalculateException();
		return HMatrix33();
	}
	HMatrix33 HMatrix33::operator*(HMatrix33 matrix) const
	{
		HMatrix33 m;
		m.e11 = 0; m.e12 = 0; m.e13 = 0;
		m.e21 = 0; m.e22 = 0; m.e23 = 0;
		m.e31 = 0; m.e32 = 0; m.e33 = 0;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				m.row[i].e[j] += (row[i].e[j] * matrix.row[j].e[i]);
			}
		}
		return m;
	}
	HMatrix33 HMatrix33::Translate(Vector2 vector)
	{
		 HMatrix33 m(
			1, 0,
			0, 1,
			vector.GetX(), vector.GetY());
	}
	HMatrix33 HMatrix33::Rotate(float radian)
	{
		return HMatrix33(
			cos(radian), sin(radian),
			-sin(radian), cos(radian),
			0, 0);
	}
	HMatrix33 HMatrix33::Scale(Vector2 data)
	{
		return HMatrix33(
			data.GetX(), 0,
			0, data.GetY(),
			0, 0);
	}

	Matrix44::Matrix44()
	{
		Identity();
	}
	Matrix44::Matrix44(float e11, float e12, float e13, float e14, float e21, float e22, float e23, float e24, float e31, float e32, float e33, float e34, float e41, float e42, float e43, float e44)
	{
		row[0].x = e11; row[0].y = e12; row[0].z = e13; row[0].w = e14;
		row[1].x = e21; row[1].y = e22; row[1].z = e23; row[1].w = e24;
		row[2].x = e31; row[2].y = e32; row[2].z = e33; row[2].w = e34;
		row[3].x = e41; row[3].y = e42; row[3].z = e43; row[3].w = e44;
	}
	void Matrix44::Identity()
	{
		e11 = 1; e12 = 0; e13 = 0; e14 = 0;
		e21 = 0; e22 = 1; e23 = 0; e24 = 0;
		e31 = 0; e32 = 0; e33 = 1; e34 = 0;
		e41 = 0; e42 = 0; e43 = 0; e44 = 1;
	}
	Matrix44 Matrix44::Transpose()
	{
		return Matrix44(
			e11, e21, e31, e41,
			e12, e22, e32, e42,
			e13, e23, e33, e43,
			e14, e24, e34, e44);
	}
	Matrix44 Matrix44::Inverse()
	{
		class UnableCalculateException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require Matrix44 Inverse Operation";
			}
		};

		throw UnableCalculateException();
		return Matrix44();
	}
	Vector4 Matrix44::GetRow(int i)
	{
		return Vector4(row[i].x, row[i].y, row[i].z, row[i].w);
	}
	Vector4 Matrix44::GetColumn(int i)
	{
		return Vector4(row[0].e[i], row[1].e[i], row[2].e[i], row[3].e[i]);
	}
	Matrix44 Matrix44::operator+(const Matrix44 matrix) const
	{
		return Matrix44(
			e11 + matrix.e11, e12 + matrix.e12, e13 + matrix.e13, e14 + matrix.e14,
			e21 + matrix.e21, e22 + matrix.e22, e23 + matrix.e23, e24 + matrix.e24,
			e31 + matrix.e31, e32 + matrix.e32, e33 + matrix.e33, e34 + matrix.e34,
			e41 + matrix.e41, e42 + matrix.e42, e43 + matrix.e43, e44 + matrix.e44);
	}
	void Matrix44::operator+=(const Matrix44 matrix)
	{
		e11 += matrix.e11; e12 += matrix.e12; e13 += matrix.e13; e14 += matrix.e14;
		e21 += matrix.e21; e22 += matrix.e22; e23 += matrix.e23; e24 += matrix.e24;
		e31 += matrix.e31; e32 += matrix.e32; e33 += matrix.e33; e34 += matrix.e34;
		e41 += matrix.e41; e42 += matrix.e42; e43 += matrix.e43; e44 += matrix.e44;
	}
	Matrix44 Matrix44::operator-(const Matrix44 matrix) const
	{
		return Matrix44(
			e11 - matrix.e11, e12 - matrix.e12, e13 - matrix.e13, e14 - matrix.e14,
			e21 - matrix.e21, e22 - matrix.e22, e23 - matrix.e23, e24 - matrix.e24,
			e31 - matrix.e31, e32 - matrix.e32, e33 - matrix.e33, e34 - matrix.e34,
			e41 - matrix.e41, e42 - matrix.e42, e43 - matrix.e43, e44 - matrix.e44);
	}
	void Matrix44::operator-=(const Matrix44 matrix)
	{
		e11 -= matrix.e11; e12 -= matrix.e12; e13 -= matrix.e13; e14 -= matrix.e14;
		e21 -= matrix.e21; e22 -= matrix.e22; e23 -= matrix.e23; e24 -= matrix.e24;
		e31 -= matrix.e31; e32 -= matrix.e32; e33 -= matrix.e33; e34 -= matrix.e34;
		e41 -= matrix.e41; e42 -= matrix.e42; e43 -= matrix.e43; e44 -= matrix.e44;
	}
	Matrix44 Matrix44::operator*(float scalar) const
	{
		return Matrix44(
			e11 * scalar, e12 * scalar, e13 * scalar, e14 * scalar,
			e21 * scalar, e22 * scalar, e23 * scalar, e24 * scalar,
			e31 * scalar, e32 * scalar, e33 * scalar, e34 * scalar,
			e41 * scalar, e42 * scalar, e43 * scalar, e44 * scalar);
	}
	Matrix44 Matrix44::operator*(Matrix44 matrix) const
	{
		Matrix44 m{
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0};
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m.row[i].e[j] += (row[i].e[j] * matrix.row[j].e[i]);
			}
		}
		return m;
	}

	const float HMatrix44::_fThreshold = 0.0001f;

	HMatrix44::HMatrix44()
	{
		Identity();
	}
	HMatrix44::HMatrix44(float e11, float e12, float e13, float e21, float e22, float e23, float e31, float e32, float e33, float e41, float e42, float e43)
	{
		row[0].x = e11; row[0].y = e12; row[0].z = e13;
		row[1].x = e21; row[1].y = e22; row[1].z = e23;
		row[2].x = e31; row[2].y = e32; row[2].z = e33;
		row[3].x = e41; row[3].y = e42; row[3].z = e43;
	}
	void HMatrix44::Identity()
	{
		e11 = 1; e12 = 0; e13 = 0; e14 = 0;
		e21 = 0; e22 = 1; e23 = 0; e24 = 0;
		e31 = 0; e32 = 0; e33 = 1; e34 = 0;
		e41 = 0; e42 = 0; e43 = 0; e44 = 1;
	}
	HMatrix44 HMatrix44::Transpose()
	{
		HMatrix44 m;
		m.e11 = e11; m.e12 = e21; m.e13 = e31; m.e14 = e41;
		m.e21 = e12; m.e22 = e22; m.e23 = e32; m.e24 = e42;
		m.e31 = e13; m.e32 = e23; m.e33 = e33; m.e34 = e43;
		m.e41 = e14; m.e42 = e24; m.e43 = e34; m.e44 = e44;
		return m;
	}
	HMatrix44 HMatrix44::Inverse()
	{
		if ((!(IsZero(e11) && IsZero(e12) && IsZero(e13) &&
			IsZero(e21) && IsZero(e22) &&  IsZero(e23) &&
			IsZero(e31) && IsZero(e32) &&  IsZero(e33))) &&
			(!(IsZero(e41) && IsZero(e42) && IsZero(e43))))
		{
			class MixedHMatrixInverseException : public std::exception
			{
			public:
				const char* what() const noexcept override
				{
					return "HMatrix44 Is Mixed State";
				}
			};

			throw MixedHMatrixInverseException();
		}
		else
		{
			HMatrix44 m;
			m.e11 = e11; m.e12 = e21; m.e13 = e31;
			m.e21 = e12; m.e22 = e22; m.e23 = e32;
			m.e31 = e13; m.e32 = e23; m.e33 = e33;
			m.e41 = -e41; m.e42 = -e42; m.e43 = -e43;
			return m;
		}
	}
	HVector4 HMatrix44::GetRow(int i)
	{
		return HVector4(row[i].x, row[i].y, row[i].z, row[i].w);
	}
	HVector4 HMatrix44::GetColumn(int i)
	{
		return HVector4(row[0].e[i], row[1].e[i], row[2].e[i], row[3].e[i]);
	}
	HMatrix44 HMatrix44::operator+(const HMatrix44 matrix) const
	{
		class UnableCalculateException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require HMatrix44 Add Operation";
			}
		};

		throw UnableCalculateException();
		return HMatrix44();
	}
	void HMatrix44::operator+=(const HMatrix44 matrix)
	{
		class UnableCalculateException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require HMatrix44 Add Operation";
			}
		};

		throw UnableCalculateException();
	}
	HMatrix44 HMatrix44::operator-(const HMatrix44 matrix) const
	{
		class UnableCalculateException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require HMatrix44 Sub Operation";
			}
		};

		throw UnableCalculateException();
		return HMatrix44();
	}
	void HMatrix44::operator-=(const HMatrix44 matrix)
	{
		class UnableCalculateException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require HMatrix44 Sub Operation";
			}
		};

		throw UnableCalculateException();
	}
	HMatrix44 HMatrix44::operator*(float scalar) const
	{
		class UnableCalculateException : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Require HMatrix44 Mul Scalar Operation";
			}
		};

		throw UnableCalculateException();
		return HMatrix44();
	}
	HMatrix44 HMatrix44::operator*(HMatrix44 matrix) const
	{
		HMatrix44 m;
		m.e11 = 0; m.e12 = 0; m.e13 = 0; m.e14 = 0;
		m.e21 = 0; m.e22 = 0; m.e23 = 0; m.e24 = 0;
		m.e31 = 0; m.e32 = 0; m.e33 = 0; m.e34 = 0;
		m.e41 = 0; m.e42 = 0; m.e43 = 0; m.e44 = 0;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m.row[i].e[j] += (row[i].e[j] * matrix.row[j].e[i]);
			}
		}
		return m;
	}
	HMatrix44 HMatrix44::Translate(Vector3 vector)
	{
		return HMatrix44 {
			1, 0, 0,
			0, 1, 0,
			0, 0, 1,
			vector.GetX(), vector.GetY(), vector.GetZ()};
	}
	HMatrix44 HMatrix44::RotateFromXAxis(float radian)
	{
		return HMatrix44 {
			1, 0, 0,
			0, cos(radian), sin(radian),
			0, -sin(radian), cos(radian),
			0, 0, 0};
	}
	HMatrix44 HMatrix44::RotateFromYAxis(float radian)
	{
		return HMatrix44 {
			cos(radian), 0, -sin(radian),
			0, 1, 0,
			sin(radian), 0, cos(radian),
			0, 0, 0};
	}
	HMatrix44 HMatrix44::RotateFromZAxis(float radian)
	{
		return HMatrix44 {
			cos(radian), sin(radian), 0,
			-sin(radian), cos(radian), 0,
			0, 0, 1,
			0, 0, 0};
	}
	HMatrix44 HMatrix44::Scale(Vector3 data)
	{
		return HMatrix44(
			data.GetX(), 0, 0,
			0, data.GetY(), 0,
			0, 0, data.GetZ(),
			0, 0, 0);
	}
}
