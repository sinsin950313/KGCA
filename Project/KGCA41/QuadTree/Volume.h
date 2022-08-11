#pragma once

#include <vector>
#include "Point.h"
#include "CustomMath.h"

/// <summary>
/// <para>
/// Factory pattern for Volume's vertexes.
/// </para>
///
/// <para>
/// Volume need custom vertexes but virtual function can't used in constructor.
/// So, divide from Volume class.
/// </para>
/// 
/// <para>
/// If any classes that inherit from Volume, it need to realize VolumeVectextFactor, too.
/// </para>
/// </summary>
class VolumeVertexFactory
{
public:
	virtual std::vector<Point*> operator()() = 0;
};

class Volume
{
private:
	class RoughVolume
	{
		Point _center;
		CustomFloat _radius;

	public:
		RoughVolume(CustomFloat x, CustomFloat y, CustomFloat r) : _center(x, y), _radius(r) { }

	public:
		bool IsIn(const Point& p) const;
		void Resize(CustomFloat radius) { _radius = radius; }
		void Reposition(CustomFloat x, CustomFloat y) { _center.Repoisition(x, y); }

	public:
		const Point& GetCenter() const { return _center; }
		CustomFloat GetRadius() const { return _radius; }
	};

private:
	RoughVolume _roughVolume;
	std::vector<Point*> _vertexes;

public:
	Volume(CustomFloat centerX, CustomFloat centerY, CustomFloat radius, VolumeVertexFactory& factory) : _roughVolume(centerX, centerY, radius) { _vertexes = factory(); }
	Volume(CustomFloat centerX, CustomFloat centerY, CustomFloat radius, VolumeVertexFactory&& factory) : _roughVolume(centerX, centerY, radius) { _vertexes = factory(); }
	virtual ~Volume();

public:
	void Resize(CustomFloat radius);
	void Reposition(CustomFloat centerX, CustomFloat centerY);
	bool IsCollide(const Volume& volume) const;

public:
	virtual bool IsIn(const Point& p) const;

public:
	const std::vector<Point*>& GetVertexes() const { return _vertexes; }
	const Point& GetCenter() const { return _roughVolume.GetCenter(); }

protected:
	CustomFloat GetRadius() const { return _roughVolume.GetRadius(); }
};
