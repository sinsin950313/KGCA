#pragma once

#include "Volume.h"

class Circle : public Volume
{
public:
	float GetCenterX() const { return Volume::GetCenter().GetX(); }
	float GetCenterY() const { return Volume::GetCenter().GetY(); }
	float GetRadius() const { return Volume::GetRadius(); }

public:
	bool operator&&(const Circle& circle) const;
	bool operator==(const Circle& circle) const;

public:
	virtual std::vector<Point*> GetDetailVolumeVertexes();
};
