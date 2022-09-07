#pragma once

#include "Volume.h"

namespace Custom
{
	class RectangleVertexFactory : public VolumeVertexFactory<2>
	{
	private:
		Vector2D _lt;
		Vector2D _rb;

	public:
		RectangleVertexFactory(float left, float top, float right, float bottom);
		virtual std::vector<Vector2D*> operator()() override;
	};

	class Rectangle : public Volume<2>
	{
		Vector2D _lt;
		Vector2D _rb;
		float _width;
		float _height;

	public:
		Rectangle() = default;
		Rectangle(float centerX, float centerY, float _width, float _height);

	public:
		float GetLeft() const { return _lt.Get(0) + GetCenter().Get(0); }
		float GetTop() const { return _lt.Get(1) + GetCenter().Get(1); }
		float GetRight() const { return _rb.Get(0) + GetCenter().Get(0); }
		float GetBottom() const { return _rb.Get(1) + GetCenter().Get(1); }
		float GetWidth() const { return _width; }
		float GetHeight() const { return _height; }

	public:
		bool operator==(const Rectangle& rect) const;
		//Rectangle operator&(const Rectangle& rect) const;
		bool operator&&(const Rectangle& rect) const;

	public:
		void Resize(float width, float height);

	public:
		bool IsIn(const Vector2D& coordinate, const Vector2D& v) const override;
		void Print() const override;
	};
};