#pragma once

#include "Volume.h"

class BoxVertexFactory : public VolumeVertexFactory<3>
{
private:
	Vector3D _center;
	float _width;
	float _height;
	float _depth;

public:
	BoxVertexFactory(Vector3D center, float width, float height, float depth);
	virtual std::vector<Vector3D*> operator()();
};

class Box : public Volume<3>
{
	Vector3D _ltf;
	Vector3D _rbb;

public:
	Box(Vector3D&& center, float width, float height, float depth);

public:
	void Resize(float width, float height, float depth);
	bool IsIn(const Vector3D& coordinate, const Vector3D& v) const override;
	void Print() const override;
};
