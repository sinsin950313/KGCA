#pragma once

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
		virtual T Identity() = 0;
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
	};

	class Vector2 : protected Float2, public VectorInterface<Vector2>
	{
	public:
		virtual float LengthSquare() const override;
		virtual float Length() const override;
		virtual float Dot(const Vector2 vec) override;
		virtual Vector2 Cross(const Vector2 vec) override;
		virtual void Normalize() override;
		virtual Vector2 Identity() override;
		virtual void Clear() override;

	public:
		virtual Vector2 operator+(const Vector2 vec) const override;
		virtual void operator+=(const Vector2 vec) override;
		virtual Vector2 operator-(const Vector2 vec) const override;
		virtual void operator-=(const Vector2 vec) override;
		virtual Vector2 operator*(float scalar) const override;
		virtual Vector2 operator/(float scalar) const override;
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
	public:
		virtual float LengthSquare() const override;
		virtual float Length() const override;
		virtual float Dot(const Vector3 vec) override;
		virtual Vector3 Cross(const Vector3 vec) override;
		virtual void Normalize() override;
		virtual Vector3 Identity() override;
		virtual void Clear() override;

	public:
		virtual Vector3 operator+(const Vector3 vec) const override;
		virtual void operator+=(const Vector3 vec) override;
		virtual Vector3 operator-(const Vector3 vec) const override;
		virtual void operator-=(const Vector3 vec) override;
		virtual Vector3 operator*(float scalar) const override;
		virtual Vector3 operator/(float scalar) const override;
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
	public:
		virtual float LengthSquare() const override;
		virtual float Length() const override;
		virtual float Dot(const Vector4 vec) override;
		virtual Vector4 Cross(const Vector4 vec) override;
		virtual void Normalize() override;
		virtual Vector4 Identity() override;
		virtual void Clear() override;

	public:
		virtual Vector4 operator+(const Vector4 vec) const override;
		virtual void operator+=(const Vector4 vec) override;
		virtual Vector4 operator-(const Vector4 vec) const override;
		virtual void operator-=(const Vector4 vec) override;
		virtual Vector4 operator*(float scalar) const override;
		virtual Vector4 operator/(float scalar) const override;
	};
}
