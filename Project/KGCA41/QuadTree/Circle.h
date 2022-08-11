#pragma once

#include "Volume.h"
#include "CustomMath.h"

class CircleVertexFactory : public VolumeVertexFactory
{
private:
	Point _center;
	CustomFloat _radius;

private:
	CustomFloat GetCenterX() { return _center.GetX(); }
	CustomFloat GetCenterY() { return _center.GetY(); }
	CustomFloat GetRadius() { return _radius; }

public:
	CircleVertexFactory(CustomFloat centerX, CustomFloat centerY, CustomFloat radius);
	virtual std::vector<Point*> operator()() override;
};

class Circle : public Volume
{
public:
	CustomFloat GetCenterX() const { return Volume::GetCenter().GetX(); }
	CustomFloat GetCenterY() const { return Volume::GetCenter().GetY(); }
	CustomFloat GetRadius() const { return Volume::GetRadius(); }

public:
	bool operator&&(const Circle& circle) const;
	bool operator==(const Circle& circle) const;
};
