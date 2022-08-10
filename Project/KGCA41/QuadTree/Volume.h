#pragma once

#include <vector>
#include "Point.h"

class Volume
{
private:
	class RoughVolume
	{
		Point _center;
		float _radius;

	public:
		RoughVolume(float x, float y, float r) : _center(x, y), _radius(r) { }

	public:
		bool IsIn(const Point& p) const;
		void Resize(float radius) { _radius = radius; }
		void Reposition(float x, float y) { _center.Repoisition(x, y); }

	public:
		const Point& GetCenter() const { return _center; }
		float GetRadius() const { return _radius; }
	};

private:
	RoughVolume _roughVolume;
	std::vector<Point*> _vertexes;

public:
	Volume(float centerX, float centerY, float radius) : _roughVolume(centerX, centerY, radius) { }
	Volume(float centerX, float centerY, float width, float height);
	virtual ~Volume();

protected:
	void AddVertexes(Point* p);
	virtual std::vector<Point*> GetDetailVolumeVertexes() = 0;
	std::vector<Point*>& GetVolumeVertexes();

public:
	void Resize(float radius);
	void Reposition(float centerX, float centerY);
	bool IsCollide(const Volume& volume) const;

public:
	virtual bool IsIn(const Point& p) const;

public:
	const std::vector<Point*>& GetVertexes() const { return _vertexes; }
	const Point& GetCenter() const { return _roughVolume.GetCenter(); }
	float GetRadius() const { return _roughVolume.GetRadius(); }
};
