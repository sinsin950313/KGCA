#pragma once

#include "Volume.h"
#include "CustomMath.h"

class RectangleVertexFactory : public VolumeVertexFactory
{
private:
	Point _lt;
	Point _rb;

public:
	RectangleVertexFactory(CustomFloat left, CustomFloat top, CustomFloat right, CustomFloat bottom);
	virtual std::vector<Point*> operator()() override;
};

class Rectangle : public Volume
{
	Point _lt;
	Point _rb;
	CustomFloat _width;
	CustomFloat _height;

public:
	Rectangle() = default;
	Rectangle(CustomFloat centerX, CustomFloat centerY, CustomFloat width, CustomFloat height);

public:
	CustomFloat GetLeft() const { return _lt.GetX(); }
	CustomFloat GetTop() const { return _lt.GetY(); }
	CustomFloat GetRight() const { return _rb.GetX(); }
	CustomFloat GetBottom() const { return _rb.GetY(); }
	CustomFloat GetWidth() const { return _width; }
	CustomFloat GetHeight() const { return _height; }

public:
	bool operator==(const Rectangle& rect) const;
	Rectangle operator&(const Rectangle& rect) const;
	bool operator&&(const Rectangle& rect) const;

public:
	void Resize(CustomFloat centerX, CustomFloat centerY, CustomFloat width, CustomFloat height);

public:
	virtual bool IsIn(const Point& p) const override;
};
