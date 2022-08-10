#pragma once

#include "Volume.h"

class Rectangle : public Volume
{
	Point _lt;
	Point _rb;
	float _width;
	float _height;

public:
	Rectangle() = default;
	Rectangle(float centerX, float centerY, float width, float height);

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
	void Resize(float centerX, float centerY, float width, float height);

public:
	virtual std::vector<Point*> GetDetailVolumeVertexes();
	virtual bool IsIn(const Point& p) const override;
};
