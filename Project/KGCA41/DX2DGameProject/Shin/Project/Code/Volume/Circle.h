#pragma once

#include "Volume.h"

//class CircleVertexFactory : public VolumeVertexFactory<2>
//{
//private:
//	Vector2D _center;
//	float _radius;
//
//private:
//	float GetCenterX() { return _center.GetX(); }
//	float GetCenterY() { return _center.GetY(); }
//	float GetRadius() { return _radius; }
//
//public:
//	CircleVertexFactory(float centerX, float centerY, float radius);
//	virtual std::vector<Vector2D*> operator()() override;
//};
//
//class Circle : public Volume<2>
//{
//public:
//	float GetCenterX() const { return Volume::GetCenter().GetX(); }
//	float GetCenterY() const { return Volume::GetCenter().GetY(); }
//	float GetRadius() const { return Volume::GetRadius(); }
//
//public:
//	bool operator&&(const Circle& circle) const;
//	bool operator==(const Circle& circle) const;
//};
