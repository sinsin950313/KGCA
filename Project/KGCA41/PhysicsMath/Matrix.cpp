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
		_f.row[0].x = e11; _f.row[0].y = e12;
		_f.row[1].x = e21; _f.row[1].y = e22;
	}
	Matrix22::Matrix22(Float22 data)
	{
		_f.row[0].x = data.e11; _f.row[0].y = data.e12;
		_f.row[1].x = data.e21; _f.row[1].y = data.e22;
	}
	void SSB::Matrix22::Identity()
	{
		_f.e11 = 1; _f.e12 = 0;
		_f.e21 = 0; _f.e22 = 1;
	}

	Matrix22 SSB::Matrix22::Transpose()
	{
		return Matrix22(
			_f.e11, _f.e21,
			_f.e12, _f.e22);
	}
	Matrix22 Matrix22::Inverse()
	{
		return Matrix22(
			_f.e22, -_f.e12,
			-_f.e21, _f.e11).operator*(1.0f / (_f.e11 * _f.e22 - _f.e12 * _f.e21));
	}
	Vector2 Matrix22::GetRow(int i) const
	{
		return Vector2(_f.row[i].x, _f.row[i].y);
	}
	Vector2 Matrix22::GetColumn(int i) const
	{
		return Vector2(_f.row[0].e[i], _f.row[1].e[i]);
	}
	Matrix22 Matrix22::operator+(const Matrix22 matrix) const
	{
		return Matrix22(
			_f.e11 + matrix._f.e11, _f.e12 + matrix._f.e12, 
			_f.e21 + matrix._f.e21, _f.e22 + matrix._f.e22);
	}
	void Matrix22::operator+=(const Matrix22 matrix)
	{
		_f.e11 += matrix._f.e11; _f.e12 += matrix._f.e12;
		_f.e21 += matrix._f.e21; _f.e22 += matrix._f.e22;
	}
	Matrix22 Matrix22::operator-(const Matrix22 matrix) const
	{
		return Matrix22(
			_f.e11 - matrix._f.e11, _f.e12 - matrix._f.e12, 
			_f.e21 - matrix._f.e21, _f.e22 - matrix._f.e22);
	}
	void Matrix22::operator-=(const Matrix22 matrix)
	{
		_f.e11 -= matrix._f.e11; _f.e12 -= matrix._f.e12;
		_f.e21 -= matrix._f.e21; _f.e22 -= matrix._f.e22;
	}
	Matrix22 Matrix22::operator*(float scalar) const
	{
		return Matrix22(
			_f.e11 * scalar, _f.e12 * scalar, 
			_f.e21 * scalar, _f.e22 * scalar);
	}
	Matrix22 Matrix22::operator*(Matrix22 matrix) const
	{
		Matrix22 m;
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				m._f.row[i].e[j] = GetRow(i).Dot(matrix.GetColumn(j));
			}
		}
		return m;
	}

	Matrix22::operator Float22()
	{
		return Float22{
			_f.e11, _f.e12,
			_f.e21, _f.e22
		};
	}

	Matrix33::Matrix33()
	{
		Identity();
	}
	Matrix33::Matrix33(float e11, float e12, float e13, float e21, float e22, float e23, float e31, float e32, float e33)
	{
		_f.row[0].x = e11; _f.row[0].y = e12; _f.row[0].z = e13;
		_f.row[1].x = e21; _f.row[1].y = e22; _f.row[1].z = e23;
		_f.row[2].x = e31; _f.row[2].y = e32; _f.row[2].z = e33;
	}
	Matrix33::Matrix33(Float33 data)
	{
		_f.row[0].x = data.e11; _f.row[0].y = data.e12; _f.row[0].z = data.e13;
		_f.row[1].x = data.e21; _f.row[1].y = data.e22; _f.row[1].z = data.e23;
		_f.row[2].x = data.e31; _f.row[2].y = data.e32; _f.row[2].z = data.e33;
	}
	void Matrix33::Identity()
	{
		_f.e11 = 1; _f.e12 = 0; _f.e13 = 0;
		_f.e21 = 0; _f.e22 = 1; _f.e23 = 0;
		_f.e31 = 0; _f.e32 = 0; _f.e33 = 1;
	}
	Matrix33 Matrix33::Transpose()
	{
		return Matrix33(
			_f.e11, _f.e21, _f.e31,
			_f.e12, _f.e22, _f.e32,
			_f.e13, _f.e23, _f.e33);
	}
	//Matrix33 Matrix33::Inverse()
	//{
	//	class UnableCalculateException : public std::exception
	//	{
	//	public:
	//		const char* what() const noexcept override
	//		{
	//			return "Require Matrix33 Inverse Operation";
	//		}
	//	};

	//	th_f.row UnableCalculateException();
	//	return Matrix33();
	//}
	Vector3 Matrix33::GetRow(int i) const
	{
		return Vector3(_f.row[i].x, _f.row[i].y, _f.row[i].z);
	}
	Vector3 Matrix33::GetColumn(int i) const
	{
		return Vector3(_f.row[0].e[i], _f.row[1].e[i], _f.row[2].e[i]);
	}
	Matrix33 Matrix33::operator+(const Matrix33 matrix) const
	{
		return Matrix33(
			_f.e11 + matrix._f.e11, _f.e12 + matrix._f.e12, _f.e13 + matrix._f.e13,
			_f.e21 + matrix._f.e21, _f.e22 + matrix._f.e22, _f.e23 + matrix._f.e23,
			_f.e31 + matrix._f.e31, _f.e32 + matrix._f.e32, _f.e33 + matrix._f.e33);
	}
	void Matrix33::operator+=(const Matrix33 matrix)
	{
		_f.e11 += matrix._f.e11; _f.e12 += matrix._f.e12; _f.e13 += matrix._f.e13;
		_f.e21 += matrix._f.e21; _f.e22 += matrix._f.e22; _f.e23 += matrix._f.e23;
		_f.e31 += matrix._f.e31; _f.e32 += matrix._f.e32; _f.e33 += matrix._f.e33;
	}
	Matrix33 Matrix33::operator-(const Matrix33 matrix) const
	{
		return Matrix33(
			_f.e11 - matrix._f.e11, _f.e12 - matrix._f.e12, _f.e13 - matrix._f.e13,
			_f.e21 - matrix._f.e21, _f.e22 - matrix._f.e22, _f.e23 - matrix._f.e23,
			_f.e31 - matrix._f.e31, _f.e32 - matrix._f.e32, _f.e33 - matrix._f.e33);
	}
	void Matrix33::operator-=(const Matrix33 matrix)
	{
		_f.e11 -= matrix._f.e11; _f.e12 -= matrix._f.e12; _f.e13 -= matrix._f.e13;
		_f.e21 -= matrix._f.e21; _f.e22 -= matrix._f.e22; _f.e23 -= matrix._f.e23;
		_f.e31 -= matrix._f.e31; _f.e32 -= matrix._f.e32; _f.e33 -= matrix._f.e33;
	}
	Matrix33 Matrix33::operator*(float scalar) const
	{
		return Matrix33(
			_f.e11 * scalar, _f.e12 * scalar, _f.e13 * scalar,
			_f.e21 * scalar, _f.e22 * scalar, _f.e23 * scalar,
			_f.e31 * scalar, _f.e32 * scalar, _f.e33 * scalar);
	}
	Matrix33 Matrix33::operator*(Matrix33 matrix) const
	{
		Matrix33 m;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				m._f.row[i].e[j] = GetRow(i).Dot(matrix.GetColumn(j));
			}
		}
		return m;
	}

	Matrix33::operator Float33()
	{
		return Float33{
			_f.e11, _f.e12, _f.e13,
			_f.e21, _f.e22, _f.e23,
			_f.e31, _f.e32, _f.e33
		};
	}

	const float HMatrix33::_fThreshold = 0.0001f;

	HMatrix33::HMatrix33()
	{
		Identity();
	}
	HMatrix33::HMatrix33(float e11, float e12, float e13, float e21, float e22, float e23, float e31, float e32, float e33)
	{
		_f.row[0].x = e11; _f.row[0].y = e12; _f.row[0].z = e13;
		_f.row[1].x = e21; _f.row[1].y = e22; _f.row[1].z = e23;
		_f.row[2].x = e31; _f.row[2].y = e32; _f.row[2].z = e33;
	}
	HMatrix33::HMatrix33(Float22 srData, Float2 tData)
	{
		_f.row[0].x = srData.e11; _f.row[0].y = srData.e12; _f.row[0].z = 0;
		_f.row[1].x = srData.e21; _f.row[1].y = srData.e22; _f.row[1].z = 0;
		_f.row[2].x = tData.x; _f.row[2].y = tData.y; _f.row[2].z = 1;
	}
	void HMatrix33::Identity()
	{
		_f.e11 = 1; _f.e12 = 0; _f.e13 = 0;
		_f.e21 = 0; _f.e22 = 1; _f.e23 = 0;
		_f.e31 = 0; _f.e32 = 0; _f.e33 = 1;
	}
	HMatrix33 HMatrix33::Transpose()
	{
		HMatrix33 m;
		m._f.e11 = _f.e11; m._f.e12 = _f.e21; m._f.e13 = _f.e31;
		m._f.e21 = _f.e12; m._f.e22 = _f.e22; m._f.e23 = _f.e32;
		m._f.e31 = _f.e13; m._f.e32 = _f.e23; m._f.e33 = _f.e33;
		return m;
	}
	HMatrix33 HMatrix33::Inverse()
	{
		HMatrix33 srInverse
		{
			_f.e11, _f.e21, 0,
			_f.e12, _f.e22, 0,
			0, 0, 1
		};
		HMatrix33 tInverse
		{
			1, 0, 0,
			0, 1, 0,
			-_f.e31, -_f.e32, 1
		};
		return tInverse * srInverse;
	}
	HVector3 HMatrix33::GetRow(int i) const
	{
		return HVector3(_f.row[i].x, _f.row[i].y, _f.row[i].z);
	}
	HVector3 HMatrix33::GetColumn(int i) const
	{
		return HVector3(_f.row[0].e[i], _f.row[1].e[i], _f.row[2].e[i]);
	}
	//HMatrix33 HMatrix33::operator+(const HMatrix33 matrix) const
	//{
	//	class UnableCalculateException : public std::exception
	//	{
	//	public:
	//		const char* what() const noexcept override
	//		{
	//			return "Require HMatrix44 Add Operation";
	//		}
	//	};

	//	th_f.row UnableCalculateException();
	//	return HMatrix33();
	//}
	//void HMatrix33::operator+=(const HMatrix33 matrix)
	//{
	//	class UnableCalculateException : public std::exception
	//	{
	//	public:
	//		const char* what() const noexcept override
	//		{
	//			return "Require Matrix44 Add Operation";
	//		}
	//	};

	//	th_f.row UnableCalculateException();
	//}
	//HMatrix33 HMatrix33::operator-(const HMatrix33 matrix) const
	//{
	//	class UnableCalculateException : public std::exception
	//	{
	//	public:
	//		const char* what() const noexcept override
	//		{
	//			return "Require Matrix44 Sub Operation";
	//		}
	//	};

	//	th_f.row UnableCalculateException();
	//	return HMatrix33();
	//}
	//void HMatrix33::operator-=(const HMatrix33 matrix)
	//{
	//	class UnableCalculateException : public std::exception
	//	{
	//	public:
	//		const char* what() const noexcept override
	//		{
	//			return "Require Matrix44 Sub Operation";
	//		}
	//	};

	//	th_f.row UnableCalculateException();
	//}
	//HMatrix33 HMatrix33::operator*(float scalar) const
	//{
	//	class UnableCalculateException : public std::exception
	//	{
	//	public:
	//		const char* what() const noexcept override
	//		{
	//			return "Require Matrix44 Mul Operation";
	//		}
	//	};

	//	th_f.row UnableCalculateException();
	//	return HMatrix33();
	//}
	HMatrix33 HMatrix33::operator*(HMatrix33 matrix) const
	{
		HMatrix33 m;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				m._f.row[i].e[j] = GetRow(i).Dot(matrix.GetColumn(j));
			}
		}
		return m;
	}
	HMatrix33::operator Float22()
	{
		return Float22{
			_f.e11, _f.e12,
			_f.e21, _f.e22
		};
	}
	HMatrix33::operator Matrix22()
	{
		return Matrix22{
			_f.e11, _f.e12,
			_f.e21, _f.e22
		};
	}
	HMatrix33::operator Float33()
	{
		return Matrix33{
			_f.e11, _f.e12, _f.e13,
			_f.e21, _f.e22, _f.e23,
			_f.e31, _f.e32, _f.e33
		};
	}
	HMatrix33::operator Float2()
	{
		return Float2{ _f.e31 / _f.e33, _f.e32 / _f.e33 };
	}
	HMatrix33::operator Vector2()
	{
		return Vector2{ _f.e31 / _f.e33, _f.e32 / _f.e33 };
	}
	HMatrix33 HMatrix33::Translate(Vector2 vector)
	{
		return HMatrix33(
			1, 0, 0,
			0, 1, 0,
			vector.GetX(), vector.GetY(), 1);
	}
	HMatrix33 HMatrix33::Rotate(float radian)
	{
		return HMatrix33(
			cos(radian), sin(radian), 0,
			-sin(radian), cos(radian), 0,
			0, 0, 1);
	}
	HMatrix33 HMatrix33::Scale(Vector2 data)
	{
		return HMatrix33(
			data.GetX(), 0, 0,
			0, data.GetY(), 0,
			0, 0, 1);
	}

	//Matrix44::Matrix44()
	//{
	//	Identity();
	//}
	//Matrix44::Matrix44(float _f.e11, float _f.e12, float _f.e13, float _f.e14, float _f.e21, float _f.e22, float _f.e23, float _f.e24, float _f.e31, float _f.e32, float _f.e33, float _f.e34, float _f.e41, float _f.e42, float _f.e43, float _f.e44)
	//{
	//	_f.row[0].x = _f.e11; _f.row[0].y = _f.e12; _f.row[0].z = _f.e13; _f.row[0].w = _f.e14;
	//	_f.row[1].x = _f.e21; _f.row[1].y = _f.e22; _f.row[1].z = _f.e23; _f.row[1].w = _f.e24;
	//	_f.row[2].x = _f.e31; _f.row[2].y = _f.e32; _f.row[2].z = _f.e33; _f.row[2].w = _f.e34;
	//	_f.row[3].x = _f.e41; _f.row[3].y = _f.e42; _f.row[3].z = _f.e43; _f.row[3].w = _f.e44;
	//}
	//void Matrix44::Identity()
	//{
	//	_f.e11 = 1; _f.e12 = 0; _f.e13 = 0; _f.e14 = 0;
	//	_f.e21 = 0; _f.e22 = 1; _f.e23 = 0; _f.e24 = 0;
	//	_f.e31 = 0; _f.e32 = 0; _f.e33 = 1; _f.e34 = 0;
	//	_f.e41 = 0; _f.e42 = 0; _f.e43 = 0; _f.e44 = 1;
	//}
	//Matrix44::HMatrix44()
	//{
	//}
	//Matrix44::HMatrix44(float _f.e11, float _f.e12, float _f.e13, float _f.e21, float _f.e14, float _f.e22, float _f.e23, float _f.e31, float _f.e32, float _f.e24, float _f.e33, float _f.e41, float _f.e42, float _f.e43, float _f.e34, float _f.e44)
	//{
	//}
	//Matrix44 Matrix44::Transpose()
	//{
	//	return Matrix44(
	//		_f.e11, _f.e21, _f.e31, _f.e41,
	//		_f.e12, _f.e22, _f.e32, _f.e42,
	//		_f.e13, _f.e23, _f.e33, _f.e43,
	//		_f.e14, _f.e24, _f.e34, _f.e44);
	//}
	//Matrix44 Matrix44::Inverse()
	//{
	//	class UnableCalculateException : public std::exception
	//	{
	//	public:
	//		const char* what() const noexcept override
	//		{
	//			return "Require Matrix44 Inverse Operation";
	//		}
	//	};

	//	th_f.row UnableCalculateException();
	//	return Matrix44();
	//}
	//Matrix44::operator Float33()
	//{
	//}
	//Matrix44::operator Matrix33()
	//{
	//}
	//Matrix44::operator Float3()
	//{
	//}
	//Matrix44::operator Vector3()
	//{
	//}
	//Vector4 Matrix44::Get_f.row(int i) const
	//{
	//	return Vector4(_f.row[i].x, _f.row[i].y, _f.row[i].z, _f.row[i].w);
	//}
	//Vector4 Matrix44::GetColumn(int i) const
	//{
	//	return Vector4(_f.row[0].e[i], _f.row[1].e[i], _f.row[2].e[i], _f.row[3].e[i]);
	//}
	//Matrix44 Matrix44::operator+(const Matrix44 matrix) const
	//{
	//	return Matrix44(
	//		_f.e11 + matrix._f.e11, _f.e12 + matrix._f.e12, _f.e13 + matrix._f.e13, _f.e14 + matrix._f.e14,
	//		_f.e21 + matrix._f.e21, _f.e22 + matrix._f.e22, _f.e23 + matrix._f.e23, _f.e24 + matrix._f.e24,
	//		_f.e31 + matrix._f.e31, _f.e32 + matrix._f.e32, _f.e33 + matrix._f.e33, _f.e34 + matrix._f.e34,
	//		_f.e41 + matrix._f.e41, _f.e42 + matrix._f.e42, _f.e43 + matrix._f.e43, _f.e44 + matrix._f.e44);
	//}
	//void Matrix44::operator+=(const Matrix44 matrix)
	//{
	//	_f.e11 += matrix._f.e11; _f.e12 += matrix._f.e12; _f.e13 += matrix._f.e13; _f.e14 += matrix._f.e14;
	//	_f.e21 += matrix._f.e21; _f.e22 += matrix._f.e22; _f.e23 += matrix._f.e23; _f.e24 += matrix._f.e24;
	//	_f.e31 += matrix._f.e31; _f.e32 += matrix._f.e32; _f.e33 += matrix._f.e33; _f.e34 += matrix._f.e34;
	//	_f.e41 += matrix._f.e41; _f.e42 += matrix._f.e42; _f.e43 += matrix._f.e43; _f.e44 += matrix._f.e44;
	//}
	//Matrix44 Matrix44::operator-(const Matrix44 matrix) const
	//{
	//	return Matrix44(
	//		_f.e11 - matrix._f.e11, _f.e12 - matrix._f.e12, _f.e13 - matrix._f.e13, _f.e14 - matrix._f.e14,
	//		_f.e21 - matrix._f.e21, _f.e22 - matrix._f.e22, _f.e23 - matrix._f.e23, _f.e24 - matrix._f.e24,
	//		_f.e31 - matrix._f.e31, _f.e32 - matrix._f.e32, _f.e33 - matrix._f.e33, _f.e34 - matrix._f.e34,
	//		_f.e41 - matrix._f.e41, _f.e42 - matrix._f.e42, _f.e43 - matrix._f.e43, _f.e44 - matrix._f.e44);
	//}
	//void Matrix44::operator-=(const Matrix44 matrix)
	//{
	//	_f.e11 -= matrix._f.e11; _f.e12 -= matrix._f.e12; _f.e13 -= matrix._f.e13; _f.e14 -= matrix._f.e14;
	//	_f.e21 -= matrix._f.e21; _f.e22 -= matrix._f.e22; _f.e23 -= matrix._f.e23; _f.e24 -= matrix._f.e24;
	//	_f.e31 -= matrix._f.e31; _f.e32 -= matrix._f.e32; _f.e33 -= matrix._f.e33; _f.e34 -= matrix._f.e34;
	//	_f.e41 -= matrix._f.e41; _f.e42 -= matrix._f.e42; _f.e43 -= matrix._f.e43; _f.e44 -= matrix._f.e44;
	//}
	//Matrix44 Matrix44::operator*(float scalar) const
	//{
	//	return Matrix44(
	//		_f.e11 * scalar, _f.e12 * scalar, _f.e13 * scalar, _f.e14 * scalar,
	//		_f.e21 * scalar, _f.e22 * scalar, _f.e23 * scalar, _f.e24 * scalar,
	//		_f.e31 * scalar, _f.e32 * scalar, _f.e33 * scalar, _f.e34 * scalar,
	//		_f.e41 * scalar, _f.e42 * scalar, _f.e43 * scalar, _f.e44 * scalar);
	//}
	//Matrix44 Matrix44::operator*(Matrix44 matrix) const
	//{
	//	Matrix44 m{
	//		0, 0, 0, 0,
	//		0, 0, 0, 0,
	//		0, 0, 0, 0,
	//		0, 0, 0, 0};
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		for (int j = 0; j < 4; ++j)
	//		{
	//			m._f.row[i].e[j] += (_f.row[i].e[j] * matrix._f.row[j].e[i]);
	//		}
	//	}
	//	return m;
	//}

	const float HMatrix44::_fThreshold = 0.0001f;

	HMatrix44::HMatrix44()
	{
		Identity();
	}
	HMatrix44::HMatrix44(float e11, float e12, float e13, float e14, float e21, float e22, float e23, float e24, float e31, float e32, float e33, float e34, float e41, float e42, float e43, float e44)
	{
		_f.row[0].x = e11; _f.row[0].y = e12; _f.row[0].z = e13; _f.row[0].w = e14;
		_f.row[1].x = e21; _f.row[1].y = e22; _f.row[1].z = e23; _f.row[1].w = e24;
		_f.row[2].x = e31; _f.row[2].y = e32; _f.row[2].z = e33; _f.row[2].w = e34;
		_f.row[3].x = e41; _f.row[3].y = e42; _f.row[3].z = e43; _f.row[3].w = e44;
	}
	HMatrix44::HMatrix44(Float33 srData, Float3 tData)
	{
		_f.row[0].x = srData.e11; _f.row[0].y = srData.e12; _f.row[0].z = srData.e13; _f.row[0].w = 0;
		_f.row[1].x = srData.e21; _f.row[1].y = srData.e22; _f.row[1].z = srData.e23; _f.row[1].w = 0;
		_f.row[2].x = srData.e31; _f.row[2].y = srData.e32; _f.row[2].z = srData.e33; _f.row[2].w = 0;
		_f.row[3].x = tData.x; _f.row[3].y = tData.y; _f.row[3].z = tData.z; _f.row[3].w = 1;
	}
	void HMatrix44::Identity()
	{
		_f.e11 = 1; _f.e12 = 0; _f.e13 = 0; _f.e14 = 0;
		_f.e21 = 0; _f.e22 = 1; _f.e23 = 0; _f.e24 = 0;
		_f.e31 = 0; _f.e32 = 0; _f.e33 = 1; _f.e34 = 0;
		_f.e41 = 0; _f.e42 = 0; _f.e43 = 0; _f.e44 = 1;
	}
	HMatrix44 HMatrix44::Transpose()
	{
		HMatrix44 m;
		m._f.e11 = _f.e11; m._f.e12 = _f.e21; m._f.e13 = _f.e31; m._f.e14 = _f.e41;
		m._f.e21 = _f.e12; m._f.e22 = _f.e22; m._f.e23 = _f.e32; m._f.e24 = _f.e42;
		m._f.e31 = _f.e13; m._f.e32 = _f.e23; m._f.e33 = _f.e33; m._f.e34 = _f.e43;
		m._f.e41 = _f.e14; m._f.e42 = _f.e24; m._f.e43 = _f.e34; m._f.e44 = _f.e44;
		return m;
	}
	HMatrix44 HMatrix44::Inverse()
	{
		HMatrix44 srInverse
		{
			_f.e11, _f.e21, _f.e31, 0,
			_f.e12, _f.e22, _f.e32, 0,
			_f.e13, _f.e23, _f.e33, 0,
			0, 0, 0, 1
		};
		HMatrix44 tInverse
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			-_f.e41, -_f.e42, -_f.e43, 1
		};
		return tInverse * srInverse;
	}
	HVector4 HMatrix44::GetRow(int i) const
	{
		return HVector4(_f.row[i].x, _f.row[i].y, _f.row[i].z, _f.row[i].w);
	}
	HVector4 HMatrix44::GetColumn(int i) const
	{
		return HVector4(_f.row[0].e[i], _f.row[1].e[i], _f.row[2].e[i], _f.row[3].e[i]);
	}
	//HMatrix44 HMatrix44::operator+(const HMatrix44 matrix) const
	//{
	//	class UnableCalculateException : public std::exception
	//	{
	//	public:
	//		const char* what() const noexcept override
	//		{
	//			return "Require HMatrix44 Add Operation";
	//		}
	//	};

	//	th_f.row UnableCalculateException();
	//	return HMatrix44();
	//}
	//void HMatrix44::operator+=(const HMatrix44 matrix)
	//{
	//	class UnableCalculateException : public std::exception
	//	{
	//	public:
	//		const char* what() const noexcept override
	//		{
	//			return "Require HMatrix44 Add Operation";
	//		}
	//	};

	//	th_f.row UnableCalculateException();
	//}
	//HMatrix44 HMatrix44::operator-(const HMatrix44 matrix) const
	//{
	//	class UnableCalculateException : public std::exception
	//	{
	//	public:
	//		const char* what() const noexcept override
	//		{
	//			return "Require HMatrix44 Sub Operation";
	//		}
	//	};

	//	th_f.row UnableCalculateException();
	//	return HMatrix44();
	//}
	//void HMatrix44::operator-=(const HMatrix44 matrix)
	//{
	//	class UnableCalculateException : public std::exception
	//	{
	//	public:
	//		const char* what() const noexcept override
	//		{
	//			return "Require HMatrix44 Sub Operation";
	//		}
	//	};

	//	th_f.row UnableCalculateException();
	//}
	//HMatrix44 HMatrix44::operator*(float scalar) const
	//{
	//	class UnableCalculateException : public std::exception
	//	{
	//	public:
	//		const char* what() const noexcept override
	//		{
	//			return "Require HMatrix44 Mul Scalar Operation";
	//		}
	//	};

	//	th_f.row UnableCalculateException();
	//	return HMatrix44();
	//}
	HMatrix44 HMatrix44::LookAtMatrix(Vector3 position, Vector3 target, Vector3 up)
	{
		Vector3 zVector = target - position;
		zVector.Normalize();
		Vector3 xVector = up.Cross(zVector);
		xVector.Normalize();
		Vector3 yVector = zVector.Cross(xVector);
		yVector.Normalize();
		return HMatrix44(
			xVector.GetX(), xVector.GetY(), xVector.GetZ(), 0,
			yVector.GetX(), yVector.GetY(), yVector.GetZ(), 0,
			zVector.GetX(), zVector.GetY(), zVector.GetZ(), 0,
			position.GetX(), position.GetY(), position.GetZ(), 1);
	}
	HMatrix44 HMatrix44::operator*(HMatrix44 matrix) const
	{
		HMatrix44 m;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m._f.row[i].e[j] = GetRow(i).Dot(matrix.GetColumn(j));
			}
		}
		return m;
	}
	//HMatrix44 HMatrix44::RelativeMatrix(HMatrix44 standard)
	//{
	//	HMatrix44 rotateMatrix{
	//		standard._f.e11, standard._f.e12, standard._f.e13, 0,
	//		standard._f.e21, standard._f.e22, standard._f.e23, 0,
	//		standard._f.e31, standard._f.e32, standard._f.e33, 0,
	//		0, 0, 0, 1
	//	};
	//	HMatrix44 translateMatrix{
	//		1, 0, 0, 0,
	//		0, 1, 0, 0,
	//		0, 0, 1, 0,
	//		standard._f.e41, standard._f.e42, standard._f.e42 ,1
	//	};
	//	return translateMatrix.Inverse() * rotateMatrix.Inverse();;
	//}
	HMatrix44 HMatrix44::Translate(Vector3 vector)
	{
		return HMatrix44 {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			vector.GetX(), vector.GetY(), vector.GetZ(), 1};
	}
	HMatrix44 HMatrix44::RotateFromXAxis(float radian)
	{
		return HMatrix44 {
			1, 0, 0, 0,
			0, cos(radian), sin(radian), 0,
			0, -sin(radian), cos(radian), 0,
			0, 0, 0, 1};
	}
	HMatrix44 HMatrix44::RotateFromYAxis(float radian)
	{
		return HMatrix44 {
			cos(radian), 0, -sin(radian), 0,
			0, 1, 0, 0,
			sin(radian), 0, cos(radian), 0,
			0, 0, 0, 1};
	}
	HMatrix44 HMatrix44::RotateFromZAxis(float radian)
	{
		return HMatrix44 {
			cos(radian), sin(radian), 0, 0,
			-sin(radian), cos(radian), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1};
	}
	HMatrix44 HMatrix44::Scale(Vector3 data)
	{
		return HMatrix44(
			data.GetX(), 0, 0, 0,
			0, data.GetY(), 0, 0,
			0, 0, data.GetZ(), 0,
			0, 0, 0, 1);
	}
	HMatrix44::operator Float33()
	{
		return Float33{
			_f.e11, _f.e12, _f.e13,
			_f.e21, _f.e22, _f.e23,
			_f.e31, _f.e32, _f.e33,
		};
	}
	HMatrix44::operator Float44()
	{
		return Float44{
			_f.e11, _f.e12, _f.e13, _f.e14,
			_f.e21, _f.e22, _f.e23, _f.e24,
			_f.e31, _f.e32, _f.e33, _f.e34,
			_f.e41, _f.e42, _f.e43, _f.e44
		};
	}
	HMatrix44::operator Matrix33()
	{
		return Matrix33{
			_f.e11, _f.e12, _f.e13,
			_f.e21, _f.e22, _f.e23,
			_f.e31, _f.e32, _f.e33,
		};
	}
	HMatrix44::operator Float3()
	{
		return Float3{ _f.e41 / _f.e44, _f.e42 / _f.e44, _f.e43 / _f.e44 };
	}
}
