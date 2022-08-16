#pragma once

#include "Volume.h"

class RectangleVertexFactory : public VolumeVertexFactory
{
private:
	Vector2D _lt;
	Vector2D _rb;

public:
	RectangleVertexFactory(float left, float top, float right, float bottom);
	virtual std::vector<Vector2D*> operator()() override;
};

class Rectangle : public Volume
{
	Vector2D _lt;
	Vector2D _rb;
	float _width;
	float _height;

public:
	Rectangle() = default;
	Rectangle(float centerX, float centerY, float _width, float _height);

public:
	float GetLeft() const { return _lt.GetX() + GetCenter().GetX(); }
	float GetTop() const { return _lt.GetY() + GetCenter().GetY(); }
	float GetRight() const { return _rb.GetX() + GetCenter().GetX(); }
	float GetBottom() const { return _rb.GetY() + GetCenter().GetY(); }
	float GetWidth() const { return _width; }
	float GetHeight() const { return _height; }

public:
	bool operator==(const Rectangle& rect) const;
	Rectangle operator&(const Rectangle& rect) const;
	bool operator&&(const Rectangle& rect) const;

public:
	void Resize(float width, float height);
	void Reposition(float centerX, float centerY) override;

public:
	bool IsIn(const Vector2D& coordinate, const Vector2D& v) const override;
	void Print() const override;
};
