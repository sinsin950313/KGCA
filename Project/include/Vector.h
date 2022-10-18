#pragma once
#include <cmath>

namespace SSB
{
	template<typename T>
	class VectorInterface
	{
	public:
		virtual float LengthSquare() const = 0;
		virtual float Length() const = 0;
		virtual float Dot(const T vec) = 0;
		virtual T Cross(const T vec) = 0;
		virtual void Normalize() = 0;
		virtual T Normal() = 0;
		virtual void Clear() = 0;

	public:
		virtual T operator+(const T vec) const = 0;
		virtual void operator+=(const T vec) = 0;
		virtual T operator-(const T vec) const = 0;
		virtual void operator-=(const T vec) = 0;
		virtual T operator*(float scalar) const = 0;
		virtual T operator/(float scalar) const = 0;
		//virtual void operator=(const T& copy) = 0;
		//virtual void operator=(T&& move) = 0;
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
			float e[2];
		};
		//Float2(float xVal = 0.0f, float yVal = 0.0f) { x = xVal; y = yVal; }
	};

	class Vector2 : protected Float2, public VectorInterface<Vector2>
	{
	public:
		Vector2(float xVal = 0.0f, float yVal = 0.0f) { x = xVal; y = yVal; }

	public:
		virtual float LengthSquare() const override;
		virtual float Length() const override;
		virtual float Dot(const Vector2 vec) override;
		virtual Vector2 Cross(const Vector2 vec) override;
		virtual void Normalize() override;
		virtual Vector2 Normal() override;
		virtual void Clear() override;

	public:
		virtual Vector2 operator+(const Vector2 vec) const override;
		virtual void operator+=(const Vector2 vec) override;
		virtual Vector2 operator-(const Vector2 vec) const override;
		virtual void operator-=(const Vector2 vec) override;
		virtual Vector2 operator*(float scalar) const override;
		virtual Vector2 operator/(float scalar) const override;

	public:
		float GetX() { return x; }
		float GetY() { return y; }
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
		//Float3(float xVal = 0.0f, float yVal = 0.0f, float zVal = 0.0f, float wVal = 0.0f) { x = xVal; y = yVal; z = zVal; }
	};

	class Vector3 : protected Float3, public VectorInterface<Vector3>
	{
	public:
		Vector3(float xVal = 0.0f, float yVal = 0.0f, float zVal = 0.0f) { x = xVal; y = yVal; z = zVal; }

	public:
		virtual float LengthSquare() const override;
		virtual float Length() const override;
		virtual float Dot(const Vector3 vec) override;
		virtual Vector3 Cross(const Vector3 vec) override;
		virtual void Normalize() override;
		virtual Vector3 Normal() override;
		virtual void Clear() override;

	public:
		virtual Vector3 operator+(const Vector3 vec) const override;
		virtual void operator+=(const Vector3 vec) override;
		virtual Vector3 operator-(const Vector3 vec) const override;
		virtual void operator-=(const Vector3 vec) override;
		virtual Vector3 operator*(float scalar) const override;
		virtual Vector3 operator/(float scalar) const override;

	public:
		float GetX() { return x; }
		float GetY() { return y; }
		float GetZ() { return z; }
	};

	class HVector3 : protected Float3, public VectorInterface<HVector3>
	{
	private:
		static const float _fThreshold;

	public:
		HVector3(float xVal = 0.0f, float yVal = 0.0f, float zVal = 0.0f) { x = xVal; y = yVal; z = zVal; }

	private:
		bool IsVector() const { return abs(z) < _fThreshold; }

	public:
		virtual float LengthSquare() const override;
		virtual float Length() const override;
		virtual float Dot(const HVector3 vec) override;
		virtual HVector3 Cross(const HVector3 vec) override;
		virtual void Normalize() override;
		virtual HVector3 Normal() override;
		virtual void Clear() override;

	public:
		virtual HVector3 operator+(const HVector3 vec) const override;
		virtual void operator+=(const HVector3 vec) override;
		virtual HVector3 operator-(const HVector3 vec) const override;
		virtual void operator-=(const HVector3 vec) override;
		virtual HVector3 operator*(float scalar) const override;
		virtual HVector3 operator/(float scalar) const override;

	public:
		float GetX() { return x; }
		float GetY() { return y; }
		float GetZ() { return z; }
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
		//Float4(float xVal = 0.0f, float yVal = 0.0f, float zVal = 0.0f, float wVal = 0.0f) { x = xVal; y = yVal; z = zVal; w = wVal; }
	};

	class Vector4 : protected Float4, public VectorInterface<Vector4>
	{
	public:
		Vector4(float xVal = 0.0f, float yVal = 0.0f, float zVal = 0.0f, float wVal = 0.0f) { x = xVal; y = yVal; z = zVal; w = wVal; }

	public:
		virtual float LengthSquare() const override;
		virtual float Length() const override;
		virtual float Dot(const Vector4 vec) override;
		virtual Vector4 Cross(const Vector4 vec) override;
		virtual void Normalize() override;
		virtual Vector4 Normal() override;
		virtual void Clear() override;

	public:
		virtual Vector4 operator+(const Vector4 vec) const override;
		virtual void operator+=(const Vector4 vec) override;
		virtual Vector4 operator-(const Vector4 vec) const override;
		virtual void operator-=(const Vector4 vec) override;
		virtual Vector4 operator*(float scalar) const override;
		virtual Vector4 operator/(float scalar) const override;

	public:
		float GetX() { return x; }
		float GetY() { return y; }
		float GetZ() { return z; }
		float GetW() { return w; }
	};

	class HVector4 : protected Float4, public VectorInterface<HVector4>
	{
	private:
		static const float _fThreshold;

	public:
		HVector4(float xVal = 0.0f, float yVal = 0.0f, float zVal = 0.0f, float wVal = 0.0f) { x = xVal; y = yVal; z = zVal; w = wVal; }

	private:
		bool IsVector() const { return abs(w) < _fThreshold; }

	public:
		virtual float LengthSquare() const override;
		virtual float Length() const override;
		virtual float Dot(const HVector4 vec) override;
		virtual HVector4 Cross(const HVector4 vec) override;
		virtual void Normalize() override;
		virtual HVector4 Normal() override;
		virtual void Clear() override;

	public:
		virtual HVector4 operator+(const HVector4 vec) const override;
		virtual void operator+=(const HVector4 vec) override;
		virtual HVector4 operator-(const HVector4 vec) const override;
		virtual void operator-=(const HVector4 vec) override;
		virtual HVector4 operator*(float scalar) const override;
		virtual HVector4 operator/(float scalar) const override;

	public:
		float GetX() { return x; }
		float GetY() { return y; }
		float GetZ() { return z; }
		float GetW() { return w; }
	};
}
