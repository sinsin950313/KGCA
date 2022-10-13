#include "Matrix.h"

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
		return Transpose();
	}
	Vector3 Matrix33::GetRow(int i)
	{
		return Vector3(row[i].x, row[i].y, row[i].z);
	}
	Vector3 Matrix33::GetColumn(int i)
	{
		return Vector3(row[0].e[i], row[1].e[i], row[2].e[i]);
	}
	//Matrix33 Matrix33::operator+(const Matrix33 matrix) const
	//{
	//	return Matrix33(
	//		e11 + matrix.e11, e12 + matrix.e12, e13 + matrix.e13,
	//		e21 + matrix.e21, e22 + matrix.e22, e23 + matrix.e23,
	//		e31 + matrix.e31, e32 + matrix.e32, e33 + matrix.e33);
	//}
	//void Matrix33::operator+=(const Matrix33 matrix)
	//{
	//	e11 += matrix.e11; e12 += matrix.e12; e13 += matrix.e13;
	//	e21 += matrix.e21; e22 += matrix.e22; e23 += matrix.e23;
	//	e31 += matrix.e31; e32 += matrix.e32; e33 += matrix.e33;
	//}
	//Matrix33 Matrix33::operator-(const Matrix33 matrix) const
	//{
	//	return Matrix33(
	//		e11 - matrix.e11, e12 - matrix.e12, e13 - matrix.e13,
	//		e21 - matrix.e21, e22 - matrix.e22, e23 - matrix.e13,
	//		e31 - matrix.e31, e32 - matrix.e32, e33 - matrix.e33);
	//}
	//void Matrix33::operator-=(const Matrix33 matrix)
	//{
	//	e11 -= matrix.e11; e12 -= matrix.e12; e13 -= matrix.e13;
	//	e21 -= matrix.e21; e22 -= matrix.e22; e23 -= matrix.e23;
	//	e31 -= matrix.e31; e32 -= matrix.e32; e33 -= matrix.e33;
	//}
	//Matrix33 Matrix33::operator*(float scalar) const
	//{
	//	return Matrix33(
	//		e11 * scalar, e12 * scalar, e13 * scalar,
	//		e21 * scalar, e22 * scalar, e23 * scalar,
	//		e31 * scalar, e32 * scalar, e33 * scalar);
	//}
	//Matrix33 Matrix33::Translate(Vector2 vector)
	//{
	//	return Matrix33(
	//		1, 0, 0,
	//		0, 1, 0,
	//		vector.GetX(), vector.GetY(), 1);
	//}
	//Matrix33 Matrix33::Rotate(float radian)
	//{
	//	return Matrix33();
	//}
	Matrix33 Matrix33::Scale(Vector2 data)
	{
		return Matrix33(
			data.GetX(), 0, 0,
			0, data.GetY(), 0,
			0, 0, 1);
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
	//Matrix44 Matrix44::Transpose()
	//{
	//	return Matrix44(
	//		e11, e21, e31, e41
	//		e12, e22, e32, e
	//		e13, e23, e33);
	//}
	Matrix44 Matrix44::Inverse()
	{
		return Transpose();
	}
	Vector4 Matrix44::GetRow(int i)
	{
		return Vector4(row[i].x, row[i].y, row[i].z, row[i].w);
	}
	Vector4 Matrix44::GetColumn(int i)
	{
		return Vector4(row[0].e[i], row[1].e[i], row[2].e[i], row[3].e[i]);
	}
	//Matrix44 Matrix44::operator+(const Matrix44 matrix) const
	//{
	//	return Matrix44(
	//		e11 + matrix.e11, e12 + matrix.e12, e13 + matrix.e13, e14 + matrix.e14,
	//		e21 + matrix.e21, e22 + matrix.e22, e23 + matrix.e23, e24 + matrix.e24,
	//		e31 + matrix.e31, e32 + matrix.e32, e33 + matrix.e33, e34 + matrix.e34,
	//		e41 + matrix.e41, e42 + matrix.e42, e43 + matrix.e43, e44 + matrix.e44);
	//}
	//void Matrix44::operator+=(const Matrix44 matrix)
	//{
	//}
	//Matrix44 Matrix44::operator-(const Matrix44 matrix) const
	//{
	//	return Matrix44();
	//}
	//void Matrix44::operator-=(const Matrix44 matrix)
	//{
	//}
	//Matrix44 Matrix44::operator*(float scalar) const
	//{
	//	return Matrix44();
	//}
	//Matrix44 Matrix44::operator*(Matrix44 matrix) const
	//{
	//	return Matrix44();
	//}
	//Matrix44 Matrix44::Translate(Vector3 vector)
	//{
	//	return Matrix44();
	//}
	//Matrix44 Matrix44::RotateFromXAxis(float radian)
	//{
	//	return Matrix44();
	//}
	//Matrix44 Matrix44::RotateFromYAxis(float radian)
	//{
	//	return Matrix44();
	//}
	//Matrix44 Matrix44::RotateFromZAxis(float radian)
	//{
	//	return Matrix44();
	//}
	Matrix44 Matrix44::Scale(Vector3 data)
	{
		return Matrix44(
			data.GetX(), 0, 0, 0,
			0, data.GetY(), 0, 0,
			0, 0, data.GetZ(), 0,
			0, 0, 0, 1);
	}
}
