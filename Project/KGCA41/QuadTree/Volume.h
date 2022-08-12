#pragma once

#include <vector>
#include "Point.h"

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
	Volume(float centerX, float centerY, float radius, VolumeVertexFactory& factory) : _roughVolume(centerX, centerY, radius) { _vertexes = factory(); }
	Volume(float centerX, float centerY, float radius, VolumeVertexFactory&& factory) : _roughVolume(centerX, centerY, radius) { _vertexes = factory(); }
	virtual ~Volume();

public:
	void Resize(float radius);
	virtual void Reposition(float centerX, float centerY);
	bool IsCollide(const Volume& volume) const;

public:
	virtual bool IsIn(const Point& p) const;

public:
	const std::vector<Point*>& GetVertexes() const { return _vertexes; }
	const Point& GetCenter() const { return _roughVolume.GetCenter(); }

protected:
	float GetRadius() const { return _roughVolume.GetRadius(); }
};
