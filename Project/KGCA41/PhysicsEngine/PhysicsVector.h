#pragma once

#include <math.h>
#include <exception>

class DimensionMatchException : public std::exception
{
	char const* what() const override { return "PhysicsVector Dimension doesn't match"; }
};

template<int dimension>
class PhysicsVector final
{
private:
	static const int _dimension = dimension;
	float* _coordinate;

public:
	PhysicsVector() { _coordinate = new float[_dimension]; Clear(); }
	virtual ~PhysicsVector() { delete _coordinate; }

private:
	void DimensionCheck(const PhysicsVector& vec) const;
	template<typename UnaryFunction> void RepeatAction(UnaryFunction func) const;
	// Is it possible to lambda const?
	template<typename BinomialFunction> void RepeatAction(const PhysicsVector& vec, BinomialFunction func) const;

public:
	float LengthSquare() const;
	float Length() const { return sqrt(LengthSquare()); }
	float Dot(const PhysicsVector& vec);
	PhysicsVector Cross(const PhysicsVector& vec) = delete;

public:
	PhysicsVector operator+(const PhysicsVector& vec) const;
	void operator+=(const PhysicsVector& vec);
	PhysicsVector operator-(const PhysicsVector& vec) const;
	PhysicsVector operator*(float scalar) const;
	PhysicsVector operator/(float scalar) const;

public:
	void Normalize();
	PhysicsVector Identity();
	void Clear();

public:
	float* operator[](int dimension) { return _coordinate + dimension; }
	float Get(int dimension) const { return _coordinate[dimension]; }
};

using Vector2D = PhysicsVector<2>;
using Vector3D = PhysicsVector<3>;

template<int dimension>
inline void PhysicsVector<dimension>::DimensionCheck(const PhysicsVector& vec) const
{
	if (_dimension != vec._dimension)
	{
		throw DimensionMatchException();
	}
}

template<int dimension>
template<typename UnaryFunction>
inline void PhysicsVector<dimension>::RepeatAction(UnaryFunction func) const
{
	for (int i = 0; i < _dimension; ++i)
	{
		func(i);
	}
}

template<int dimension>
template<typename BinomialFunction>
inline void PhysicsVector<dimension>::RepeatAction(const PhysicsVector& vec, BinomialFunction func) const
{
	DimensionCheck(vec);

	for (int i = 0; i < _dimension; ++i)
	{
		func(i, vec._coordinate[i]);
	}
}

template<int dimension>
inline float PhysicsVector<dimension>::LengthSquare() const
{
	float ret = 0.0f;
	auto lambda = [&ret, this](int dim) -> void { ret += (_coordinate[dim] * _coordinate[dim]); };
	RepeatAction(lambda);
	return ret;
}

template<int dimension>
inline float PhysicsVector<dimension>::Dot(const PhysicsVector& vec)
{
	DimensionCheck(vec);

	float ret = 0.0f;
	auto lambda = [&ret, this](int dim, float val) -> void { ret += (_coordinate[dim] * val); };
	RepeatAction(vec, lambda);
	return ret;
}

template<int dimension>
inline PhysicsVector<dimension> PhysicsVector<dimension>::operator+(const PhysicsVector& vec) const
{
	PhysicsVector<dimension> ret;
	auto lambda = [&ret, this](int dim, float val) -> void { ret[dim] = _coordinate[dim] + val; };
	RepeatAction(lambda, vec);
	return ret;
}

template<int dimension>
inline void PhysicsVector<dimension>::operator+=(const PhysicsVector& vec)
{
	auto lambda = [this](int dim, float val) -> void { _coordinate[dim] += vec[dim]; };
	RepeatAction(lambda, vec);
}

template<int dimension>
inline PhysicsVector<dimension> PhysicsVector<dimension>::operator-(const PhysicsVector& vec) const
{
	PhysicsVector ret;
	auto lambda = [&ret, this](int dim, float val) -> void { ret[dim] = _coordinate[dim] - val; };
	RepeatAction(lambda, vec);
	return ret;
}

template<int dimension>
inline PhysicsVector<dimension> PhysicsVector<dimension>::operator*(float scalar) const
{
	PhysicsVector ret;
	auto lambda = [&ret, this, scalar](int dim) -> void { ret[dim] = _coordinate[dim] * scalar; };
	RepeatAction(lambda);
	return ret;
}

template<int dimension>
inline PhysicsVector<dimension> PhysicsVector<dimension>::operator/(float scalar) const
{
	PhysicsVector ret;
	float invertScalar = 1 / scalar;
	auto lambda = [&ret, this, invertScalar](int dim) -> void { ret[dim] = _coordinate[dim] * invertScalar; };
	RepeatAction(lambda);
	return ret;
}

template<int dimension>
inline void PhysicsVector<dimension>::Normalize()
{
	float length = Length();
	auto lambda = [this, length](int dim) -> void { _coordinate[dim] /= length; };
	RepeatAction(lambda);
}

template<int dimension>
inline PhysicsVector<dimension> PhysicsVector<dimension>::Identity()
{
	PhysicsVector ret;
	float inverseLength = 1.0f / Length();
	auto lambda = [&ret, this, inverseLength](int dim) -> void { ret[dim] = _coordinate[dim] * inverseLength; };
	return ret;
}

template<int dimension>
inline void PhysicsVector<dimension>::Clear()
{
	auto lambda = [this](int dim) -> void { _coordinate[dim] = 0.0f; };
	RepeatAction(lambda);
}
