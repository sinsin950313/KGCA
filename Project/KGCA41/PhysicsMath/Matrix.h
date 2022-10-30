#pragma once

#include "Vector.h"

namespace SSB
{
	//template<typename M, typename V>
	//class MatrixInterface
	//{
	//public:
	//	virtual void Identity() = 0;
	//	virtual M Transpose() = 0;
	//	virtual M Inverse() = 0;

	//protected:
	//	virtual V GetRow(int i) const = 0;
	//	virtual V GetColumn(int i) const = 0;

	//public:
	//	virtual M operator+(const M matrix) const = 0;
	//	virtual void operator+=(const M matrix) = 0;
	//	virtual M operator-(const M matrix) const = 0;
	//	virtual void operator-=(const M matrix) = 0;
	//	virtual M operator*(float scalar) const = 0;
	//	virtual M operator*(M matrix) const = 0;
	//	// Matrix need Row and Column, so doesn't implement this.
	//	//virtual V operator[](int i) const = 0;
	//};

	struct Float22
	{
		union
		{
			struct
			{
				float e11, e12;
				float e21, e22;
			};
			Float2 row[2];
		};
	};

	class Matrix22/*, public MatrixInterface<Matrix22, Vector2>*/
	{
	private:
		Float22 _f;

	public:
		Matrix22();
		Matrix22(
			float e11, float e12, 
			float e21, float e22);
		Matrix22(Float22 data);

	public:
		void Identity();
		Matrix22 Transpose();
		Matrix22 Inverse();
		Vector2 GetRow(int i) const;
		Vector2 GetColumn(int i) const;

	public:
		Matrix22 operator+(const Matrix22 matrix) const;
		void operator+=(const Matrix22 matrix);
		Matrix22 operator-(const Matrix22 matrix) const;
		void operator-=(const Matrix22 matrix);
		Matrix22 operator*(float scalar) const;
		Matrix22 operator*(Matrix22 matrix) const;

	public:
		operator Float22();
	};

	struct Float33
	{
		union
		{
			struct
			{
				float e11, e12, e13;
				float e21, e22, e23;
				float e31, e32, e33;
			};
			Float3 row[3];
		};
	};

	class Matrix33/*, public MatrixInterface<Matrix33, Vector3>*/
	{
	private:
		Float33 _f;

	public:
		Matrix33();
		Matrix33(
			float e11, float e12, float e13,
			float e21, float e22, float e23,
			float e31, float e32, float e33);
		Matrix33(Float33 data);

	public:
		void Identity();
		Matrix33 Transpose();
		//Matrix33 Inverse();
		Vector3 GetRow(int i) const;
		Vector3 GetColumn(int i) const;

	public:
		Matrix33 operator+(const Matrix33 matrix) const;
		void operator+=(const Matrix33 matrix);
		Matrix33 operator-(const Matrix33 matrix) const;
		void operator-=(const Matrix33 matrix);
		Matrix33 operator*(float scalar) const;
		Matrix33 operator*(Matrix33 matrix) const;

	public:
		operator Float33();
	};

	class HMatrix33/*, public MatrixInterface<HMatrix33, HVector3>*/
	{
	private:
		static const float _fThreshold;
		Float33 _f;

	public:
		HMatrix33();
		HMatrix33(
			float e11, float e12, float e13,
			float e21, float e22, float e23,
			float e31, float e32, float e33);
		HMatrix33(Float22 srData, Float2 tData);

	private:
		bool IsZero(float val) { return abs(val) < _fThreshold; }

	public:
		void Identity();
		HMatrix33 Transpose();
		HMatrix33 Inverse();
		HVector3 GetRow(int i) const;
		HVector3 GetColumn(int i) const;

	public:
		//HMatrix33 operator+(const HMatrix33 matrix) const;
		//void operator+=(const HMatrix33 matrix);
		//HMatrix33 operator-(const HMatrix33 matrix) const;
		//void operator-=(const HMatrix33 matrix);
		//HMatrix33 operator*(float scalar) const;
		HMatrix33 operator*(HMatrix33 matrix) const;

	public:
		operator Float22();
		operator Matrix22();
		operator Float33();
		operator Float2();
		operator Vector2();

	public:
		static HMatrix33 Translate(Vector2 vector);
		static HMatrix33 Rotate(float radian);
		static HMatrix33 Scale(Vector2 data);
	};

	struct Float44
	{
		union
		{
			struct
			{
				float e11, e12, e13, e14;
				float e21, e22, e23, e24;
				float e31, e32, e33, e34;
				float e41, e42, e43, e44;
			};
			Float4 row[4];
		};
	};

	class Matrix44 : protected Float44
	{
	public:
		Matrix44();
		Matrix44(
			float e11, float e12, float e13, float e14,
			float e21, float e22, float e23, float e24,
			float e31, float e32, float e33, float e34,
			float e41, float e42, float e43, float e44);

	public:
		void Identity();
		Matrix44 Transpose();
		Matrix44 Inverse();
		Vector4 GetRow(int i) const;
		Vector4 GetColumn(int i) const;

	public:
		Matrix44 operator+(const Matrix44 matrix) const;
		void operator+=(const Matrix44 matrix);
		Matrix44 operator-(const Matrix44 matrix) const;
		void operator-=(const Matrix44 matrix);
		Matrix44 operator*(float scalar) const;
		Matrix44 operator*(Matrix44 matrix) const;
	};

	class HMatrix44/*, public MatrixInterface<HMatrix44, HVector4>*/
	{
	private:
		static const float _fThreshold;
		Float44 _f;

	public:
		HMatrix44();
		HMatrix44(
			float e11, float e12, float e13, float e14,
			float e21, float e22, float e23, float e24,
			float e31, float e32, float e33, float e34,
			float e41, float e42, float e43, float e44);
		HMatrix44(Float33 srData, Float3 tData);

	private:
		bool IsZero(float val) { return abs(val) < _fThreshold; }

	public:
		void Identity();
		HMatrix44 Transpose();
		HMatrix44 Inverse();
		HVector4 GetRow(int i) const;
		HVector4 GetColumn(int i) const;

	public:
		//HMatrix44 operator+(const HMatrix44 matrix) const;
		//void operator+=(const HMatrix44 matrix);
		//HMatrix44 operator-(const HMatrix44 matrix) const;
		//void operator-=(const HMatrix44 matrix);
		//HMatrix44 operator*(float scalar) const;
		HMatrix44 operator*(HMatrix44 matrix) const;

	public:
		static HMatrix44 Translate(Vector3 vector);
		static HMatrix44 RotateFromXAxis(float radian);
		static HMatrix44 RotateFromYAxis(float radian);
		static HMatrix44 RotateFromZAxis(float radian);
		static HMatrix44 Scale(Vector3 data);
		static HMatrix44 LookAtMatrix(Vector3 position, Vector3 target, Vector3 up);
		//static HMatrix44 RelativeMatrix(HMatrix44 standard);

	public:
		operator Float33();
		operator Matrix33();
		operator Float44();
		operator Float3();
		operator Vector3();
	};
}
