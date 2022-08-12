#pragma once

#include "Volume.h"

class RectangleVertexFactory : public VolumeVertexFactory
{
private:
	Point _lt;
	Point _rb;

public:
	RectangleVertexFactory(float left, float top, float right, float bottom);
	virtual std::vector<Point*> operator()() override;
};

class Rectangle : public Volume
{
	Point _lt;
	Point _rb;
	float _width;
	float _height;

public:
	Rectangle() = default;
	Rectangle(float centerX, float centerY, float _width, float _height);

public:
	float GetLeft() const { return _lt.GetX(); }
	float GetTop() const { return _lt.GetY(); }
	float GetRight() const { return _rb.GetX(); }
	float GetBottom() const { return _rb.GetY(); }
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
	virtual bool IsIn(const Point& p) const override;
};
