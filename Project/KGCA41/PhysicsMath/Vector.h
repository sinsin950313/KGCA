#pragma once
#include <cmath>

namespace SSB
{
	//template<typename T>
	//class VectorInterface
	//{
	//public:
	//	float LengthSquare() const = 0;
	//	float Length() const = 0;
	//	float Dot(const T vec) = 0;
	//	T Cross(const T vec) = 0;
	//	void Normalize() = 0;
	//	T Normal() = 0;
	//	void Clear() = 0;

	//public:
	//	T operator+(const T vec) const = 0;
	//	void operator+=(const T vec) = 0;
	//	T operator-(const T vec) const = 0;
	//	void operator-=(const T vec) = 0;
	//	T operator*(float scalar) const = 0;
	//	T operator/(float scalar) const = 0;
	//	//void operator=(const T& copy) = 0;
	//	//void operator=(T&& move) = 0;
	//};

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

	class Vector2/*, public VectorInterface<Vector2>*/
	{
	private:
		Float2 _f;

	public:
		Vector2(float x = 0.0f, float y = 0.0f) : _f{ x, y } { }
		Vector2(Float2 data) : _f{data.x, data.y} { }

	public:
		float LengthSquare() const;
		float Length() const;
		float Dot(const Vector2 vec);
		//Vector2 Cross(const Vector2 vec);
		void Normalize();
		Vector2 Normal();
		void Clear();

	public:
		Vector2 operator+(const Vector2 vec) const;
		void operator+=(const Vector2 vec);
		Vector2 operator-(const Vector2 vec) const;
		void operator-=(const Vector2 vec);
		Vector2 operator*(float scalar) const;
		Vector2 operator/(float scalar) const;

	public:
		float GetX() const { return _f.x; }
		float GetY() const { return _f.y; }
		operator Float2() const { return _f; }
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

	class Vector3/*, public VectorInterface<Vector3>*/
	{
	private:
		Float3 _f;

	public:
		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : _f{ x, y, z }{ }
		Vector3(Float3 data) : _f{ data.x, data.y, data.z } { }
		Vector3(DirectX::XMFLOAT3 data);

	public:
		float LengthSquare() const;
		float Length() const;
		float Dot(const Vector3 vec);
		Vector3 Cross(const Vector3 vec);
		void Normalize();
		Vector3 Normal();
		void Clear();

	public:
		Vector3 operator+(const Vector3 vec) const;
		void operator+=(const Vector3 vec);
		Vector3 operator-(const Vector3 vec) const;
		void operator-=(const Vector3 vec);
		Vector3 operator*(float scalar) const;
		Vector3 operator/(float scalar) const;

	public:
		float GetX() const { return _f.x; }
		float GetY() const { return _f.y; }
		float GetZ() const { return _f.z; }
		operator Float3() const { return _f; }
		operator DirectX::XMFLOAT3();
	};

	class HVector3/*, public VectorInterface<HVector3>*/
	{
	private:
		static const float _fThreshold;
		Float3 _f;

	public:
		HVector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : _f { x, y, z } { }
		HVector3(Float2 data, float z = 0.0f) : _f{ data.x, data.y, z } { }
		HVector3(Vector2 data, float z = 0.0f) : _f{ data.GetX(), data.GetY(), z } { }

	private:
		bool IsVector() const { return abs(_f.z) < _fThreshold; }

	public:
		//float LengthSquare() const;
		//float Length() const;
		float Dot(const HVector3 vec);
		//HVector3 Cross(const HVector3 vec);
		void Normalize();
		HVector3 Normal();
		//void Clear();

	//public:
	//	HVector3 operator+(const HVector3 vec) const;
	//	void operator+=(const HVector3 vec);
	//	HVector3 operator-(const HVector3 vec) const;
	//	void operator-=(const HVector3 vec);
	//	HVector3 operator*(float scalar) const;
	//	HVector3 operator/(float scalar) const;

	public:
		float GetX() { return _f.x; }
		float GetY() { return _f.y; }
		float GetZ() { return _f.z; }
		operator Float2() const;
		operator Vector2() const;
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
		operator DirectX::FXMVECTOR();
	};

	class Vector4
	{
	private:
		Float4 _f;

	public:
		Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : _f{ x, y, z, w } { }
		Vector4(Float4 data) : _f{ data.x, data.y, data.z, data.w } { }

	public:
		float LengthSquare() const;
		float Length() const;
		//float Dot(const Vector4 vec);
		void Normalize();
		Vector4 Normal();
		void Clear();

	public:
		Vector4 operator+(const Vector4 vec) const;
		void operator+=(const Vector4 vec);
		Vector4 operator-(const Vector4 vec) const;
		void operator-=(const Vector4 vec);
		Vector4 operator*(float scalar) const;
		Vector4 operator/(float scalar) const;

	public:
		float GetX() { return _f.x; }
		float GetY() { return _f.y; }
		float GetZ() { return _f.z; }
		float GetW() { return _f.w; }
	};

	class HVector4/*, public VectorInterface<HVector4>*/
	{
	private:
		static const float _fThreshold;
		Float4 _f;

	public:
		HVector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : _f { x, y, z, w } { }
		HVector4(Float3 data, float w = 0.0f) : _f{ data.x, data.y, data.z, w } { } 
		HVector4(Vector3 data, float w = 0.0f) : _f{ data.GetX(), data.GetY(), data.GetZ(), w } { }

	private:
		bool IsVector() const { return abs(_f.w) < _fThreshold; }

	public:
		//float LengthSquare() const;
		//float Length() const;
		float Dot(const HVector4 vec);
		//HVector4 Cross(const HVector4 vec);
		void Normalize();
		HVector4 Normal();
		//void Clear();

	//public:
	//	HVector4 operator+(const HVector4 vec) const;
	//	void operator+=(const HVector4 vec);
	//	HVector4 operator-(const HVector4 vec) const;
	//	void operator-=(const HVector4 vec);
	//	HVector4 operator*(float scalar) const;
	//	HVector4 operator/(float scalar) const;

	public:
		float GetX() const { return _f.x; }
		float GetY() const { return _f.y; }
		float GetZ() const { return _f.z; }
		float GetW() const { return _f.w; }
		operator Float3() const;
		operator Vector3() const;
	};
}
