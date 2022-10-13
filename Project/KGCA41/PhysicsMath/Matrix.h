#pragma once

#include "Vector.h"

namespace SSB
{
	template<typename M, typename V>
	class MatrixInterface
	{
	public:
		virtual void Identity() = 0;
		virtual M Transpose() = 0;
		//virtual M Translate(V vector) = 0;
		virtual M Inverse() = 0;

	protected:
		virtual V GetRow(int i) = 0;
		virtual V GetColumn(int i) = 0;
		//	virtual M Rotate(V angleOfRotationForEachAxis) = 0;
		//	virtual M Scale(V scaleForEachAxis) = 0;

	public:
		virtual M operator+(const M matrix) const = 0;
		virtual void operator+=(const M matrix) = 0;
		virtual M operator-(const M matrix) const = 0;
		virtual void operator-=(const M matrix) = 0;
		virtual M operator*(float scalar) const = 0;
		virtual M operator*(M matrix) const = 0;
		// Matrix need Row and Column, so doesn't implement this.
		//virtual V operator[](int i) const = 0;
	};

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

	class Matrix22 : protected Float22, public MatrixInterface<Matrix22, Vector2>
	{
	public:
		Matrix22();
		Matrix22(
			float e11, float e12, 
			float e21, float e22);

	public:
		void Identity() override;
		Matrix22 Transpose() override;
		Matrix22 Inverse() override;
		Vector2 GetRow(int i) override;
		Vector2 GetColumn(int i) override;

	public:
		Matrix22 operator+(const Matrix22 matrix) const override;
		void operator+=(const Matrix22 matrix) override;
		Matrix22 operator-(const Matrix22 matrix) const override;
		void operator-=(const Matrix22 matrix) override;
		Matrix22 operator*(float scalar) const override;
		Matrix22 operator*(Matrix22 matrix) const override;
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

	class Matrix33 : protected Float33, public MatrixInterface<Matrix33, Vector3>
	{
	public:
		Matrix33();
		Matrix33(
			float e11, float e12, float e13,
			float e21, float e22, float e23,
			float e31, float e32, float e33);

	public:
		void Identity() override;
		Matrix33 Transpose() override;
		Matrix33 Inverse() override;
		Vector3 GetRow(int i) override;
		Vector3 GetColumn(int i) override;

	public:
		Matrix33 operator+(const Matrix33 matrix) const override;
		void operator+=(const Matrix33 matrix) override;
		Matrix33 operator-(const Matrix33 matrix) const override;
		void operator-=(const Matrix33 matrix) override;
		Matrix33 operator*(float scalar) const override;
		Matrix33 operator*(Matrix33 matrix) const override;

	public:
		static Matrix33 Translate(Vector2 vector);
		static Matrix33 Rotate(float radian);
		static Matrix33 Scale(Vector2 data);
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

	class Matrix44 : protected Float44, public MatrixInterface<Matrix44, Vector4>
	{
	public:
		Matrix44();
		Matrix44(
			float e11, float e12, float e13, float e14,
			float e21, float e22, float e23, float e24,
			float e31, float e32, float e33, float e34,
			float e41, float e42, float e43, float e44);

	public:
		void Identity() override;
		Matrix44 Transpose() override;
		Matrix44 Inverse() override;
		Vector4 GetRow(int i) override;
		Vector4 GetColumn(int i) override;

	public:
		Matrix44 operator+(const Matrix44 matrix) const override;
		void operator+=(const Matrix44 matrix) override;
		Matrix44 operator-(const Matrix44 matrix) const override;
		void operator-=(const Matrix44 matrix) override;
		Matrix44 operator*(float scalar) const override;
		Matrix44 operator*(Matrix44 matrix) const override;

	public:
		static Matrix44 Translate(Vector3 vector);
		static Matrix44 RotateFromXAxis(float radian);
		static Matrix44 RotateFromYAxis(float radian);
		static Matrix44 RotateFromZAxis(float radian);
		static Matrix44 Scale(Vector3 data);
	};
}
