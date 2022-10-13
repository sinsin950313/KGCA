#pragma once

template<typename T>
class VectorInterface
{
public:
	virtual float LengthSquare() const = 0;
	virtual float Length() const = 0;
	virtual float Dot(const T vec) = 0;
	virtual T Cross(const T vec) = 0;

	virtual T operator+(const T vec) const = 0;
	virtual void operator+=(const T vec) = 0;
	virtual T operator-(const T vec) const = 0;
	virtual void operator-=(const T vec) = 0;
	virtual T operator*(float scalar) const = 0;
	virtual T operator/(float scalar) const = 0;
	//virtual void operator=(const T& copy) = 0;
	//virtual void operator=(T&& move) = 0;

public:
	virtual void Normalize() = 0;
	virtual T Identity() = 0;
	virtual void Clear() = 0;
};

struct Float2
{
	union
	{
		struct
		{
			float x;
			float y;
		};
		float f[2];
	};
};

class Vector2 : protected Float2, public VectorInterface<Vector2>
{

};

struct Float3 : public Float2
{
	union
	{
		struct
		{
			float z;
		};
	};
};

class Vector3 : protected Float3, public VectorInterface<Vector3>
{

};

struct Float4 : public Float3
{
	union
	{
		struct
		{
			float w;
		};
	};
};

class Vector4 : protected Float4, public VectorInterface<Vector4>
{

};
