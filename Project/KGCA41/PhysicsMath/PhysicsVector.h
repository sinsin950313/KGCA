#pragma once

#include <math.h>
#include <exception>
#include <cstdarg>
#include <iostream>

namespace SSB
{
	class DimensionMatchException : public std::exception
	{
		char const* what() const override { return "PhysicsVector Dimension doesn't match"; }
	};

	struct Vector2DData
	{
		float x = 0;
		float y = 0;
	};

	struct Vector3DData
	{
		float x = 0;
		float y = 0;
		float z = 0;
	};

	template<int dimension>
	class PhysicsVector final
	{
	private:
		static const int _dimension = dimension;
		float* _coordinate;

	public:
		PhysicsVector() { _coordinate = new float[_dimension]; Clear(); }
		/// <summary>
		/// Don't forget to write dimension to first parameter
		/// And Coordinate values are must be float(double) type.
		/// </summary>
		/// <param name="count"></param>
		/// <param name=""></param>
		explicit PhysicsVector(int count, ...);
		PhysicsVector(Vector2DData&& data);
		PhysicsVector(Vector3DData&& data);
		PhysicsVector(const PhysicsVector& copy);
		PhysicsVector(PhysicsVector&& move);
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
		PhysicsVector Cross(const PhysicsVector& vec);

	public:
		PhysicsVector operator+(const PhysicsVector& vec) const;
		void operator+=(const PhysicsVector& vec);
		PhysicsVector operator-(const PhysicsVector& vec) const;
		PhysicsVector operator*(float scalar) const;
		PhysicsVector operator/(float scalar) const;
		void operator=(const PhysicsVector& copy);
		void operator=(PhysicsVector&& move);

	public:
		void Normalize();
		PhysicsVector Identity();
		void Clear();

	public:
		float* operator[](int dimension) { return _coordinate + dimension; }
		float Get(int dimension) const { return _coordinate[dimension]; }
	};

	using Vector2D = PhysicsVector<2>;
	//Template Specialize?
	//template<>
	//class PhysicsVector<2>
	//{
	//public:
	//	PhysicsVector(int dimension, ...) : PhysicsVector<2>(2, ...) { }
	//};
	using Vector3D = PhysicsVector<3>;

	template<int dimension>
	inline PhysicsVector<dimension>::PhysicsVector(int count, ...)
	{
		if (count != _dimension)
		{
			std::cout << count << std::endl;
			throw DimensionMatchException();
		}

		_coordinate = new float[_dimension];

		va_list list;
		va_start(list, count);

		for (int i = 0; i < _dimension; ++i)
		{
			_coordinate[i] = va_arg(list, double);
		}
		va_end(list);
	}

	template<int dimension>
	inline PhysicsVector<dimension>::PhysicsVector(Vector2DData&& data)
	{
		_coordinate = new float[2];
		_coordinate[0] = data.x;
		_coordinate[1] = data.y;
	}

	template<int dimension>
	inline PhysicsVector<dimension>::PhysicsVector(Vector3DData&& data)
	{
		_coordinate = new float[3];
		_coordinate[0] = data.x;
		_coordinate[1] = data.y;
		_coordinate[2] = data.z;
	}

	template<int dimension>
	inline PhysicsVector<dimension>::PhysicsVector(const PhysicsVector& copy)
	{
		_coordinate = new float[_dimension];
		for (int i = 0; i < _dimension; ++i)
		{
			_coordinate[i] = copy._coordinate[i];
		}
	}

	template<int dimension>
	inline PhysicsVector<dimension>::PhysicsVector(PhysicsVector&& move)
	{
		_coordinate = move._coordinate;
		move._coordinate = nullptr;
	}

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
	inline PhysicsVector<dimension> PhysicsVector<dimension>::Cross(const PhysicsVector& vec)
	{
		DimensionCheck(vec);

		if (_dimension == 2)
		{
			return PhysicsVector();
		}
		else
		{
			return PhysicsVector(Vector3DData{ Get(1) * vec.Get(2) - Get(2) * vec.Get(1), Get(2) * vec.Get(0) - Get(0) * vec.Get(2), Get(0) * vec.Get(1) - Get(1) * vec.Get(0) });
		}
	}

	template<int dimension>
	inline PhysicsVector<dimension> PhysicsVector<dimension>::operator+(const PhysicsVector& vec) const
	{
		PhysicsVector<dimension> ret;
		auto lambda = [&ret, this](int dim, float val) -> void { *ret[dim] = _coordinate[dim] + val; };
		RepeatAction(vec, lambda);
		return ret;
	}

	template<int dimension>
	inline void PhysicsVector<dimension>::operator+=(const PhysicsVector& vec)
	{
		auto lambda = [this](int dim, float val) -> void { _coordinate[dim] += val; };
		RepeatAction(vec, lambda);
	}

	template<int dimension>
	inline PhysicsVector<dimension> PhysicsVector<dimension>::operator-(const PhysicsVector& vec) const
	{
		PhysicsVector ret;
		auto lambda = [&ret, this](int dim, float val) -> void { *ret[dim] = _coordinate[dim] - val; };
		RepeatAction(vec, lambda);
		return ret;
	}

	template<int dimension>
	inline PhysicsVector<dimension> PhysicsVector<dimension>::operator*(float scalar) const
	{
		PhysicsVector ret;
		auto lambda = [&ret, this, scalar](int dim) -> void { *ret[dim] = _coordinate[dim] * scalar; };
		RepeatAction(lambda);
		return ret;
	}

	template<int dimension>
	inline PhysicsVector<dimension> PhysicsVector<dimension>::operator/(float scalar) const
	{
		PhysicsVector ret;
		float invertScalar = 1 / scalar;
		auto lambda = [&ret, this, invertScalar](int dim) -> void { *ret[dim] = _coordinate[dim] * invertScalar; };
		RepeatAction(lambda);
		return ret;
	}

	template<int dimension>
	inline void PhysicsVector<dimension>::operator=(const PhysicsVector& copy)
	{
		DimensionCheck(copy);
		auto lambda = [this](int dim, float val)-> void { _coordinate[dim] = val; };
		RepeatAction(copy, lambda);
	}

	template<int dimension>
	inline void PhysicsVector<dimension>::operator=(PhysicsVector&& move)
	{
		DimensionCheck(move);
		_coordinate = move._coordinate;
		move._coordinate = nullptr;
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
		auto lambda = [&ret, this, inverseLength](int dim) -> void { *ret[dim] = _coordinate[dim] * inverseLength; };
		RepeatAction(lambda);
		return ret;
	}

	template<int dimension>
	inline void PhysicsVector<dimension>::Clear()
	{
		auto lambda = [this](int dim) -> void { _coordinate[dim] = 0.0f; };
		RepeatAction(lambda);
	}
}
