#pragma once

#include "Vector.h"

template<typename M>
class MatrixInterface
{
public:
	virtual void Identity() = 0;
	virtual M Transpose() = 0;
	//virtual M Translate(V vector) = 0;
	virtual M operator*(M matrix) = 0;
	virtual M Inverse() = 0;

//protected:
//	virtual M Rotate(V angleOfRotationForEachAxis) = 0;
//	virtual M Scale(V scaleForEachAxis) = 0;
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
		Float2 colum[2];
	};
};

class Matrix22 : public MatrixInterface<Matrix22>
{
public:
	void Identity() override;
	Matrix22 Transpose() override;
	Matrix22 operator*(Matrix22 matrix) override;
	Matrix22 Inverse() override;
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
	};
};

class Matrix33 : public MatrixInterface<Matrix33>
{
public:
	void Identity() override;
	Matrix33 Transpose() override;
	Matrix33 operator*(Matrix33 matrix) override;
	Matrix33 Inverse() override;

public:
	Matrix33 Translate(Vector2 vector);
	Matrix33 Rotate(float radian);
	Matrix33 Scale(Vector2 data);
};

class Matrix44 : public MatrixInterface<Matrix44>
{
public:
	void Identity() override;
	Matrix44 Transpose() override;
	Matrix44 operator*(Matrix44 matrix) override;
	Matrix44 Inverse() override;

public:
	Matrix44 Translate(Vector3 vector);
	Matrix44 RotateFromXAxis(float radian);
	Matrix44 RotateFromYAxis(float radian);
	Matrix44 RotateFromZAxis(float radian);
	Matrix44 Scale(Vector3 data);
};
