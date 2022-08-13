#pragma once

#include <vector>
#include "Vector2D.h"

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
	virtual std::vector<Vector2D*> operator()() = 0;
};

class Volume
{
private:
	class RoughVolume
	{
		Vector2D _center;
		float _radius;

	public:
		RoughVolume(float x, float y, float r) : _center(x, y), _radius(r) { }

	public:
		/// <summary>
		/// Check local coordinate distance
		/// </summary>
		/// <param name="v">This should be this object's local coordinate</param>
		/// <returns></returns>
		bool IsIn(const Vector2D& v) const;
		void Resize(float radius) { _radius = radius; }
		void Reposition(float x, float y) { _center.Repoint(x, y); }

	public:
		const Vector2D& GetCenter() const { return _center; }
		float GetRadius() const { return _radius; }
	};

private:
	RoughVolume _roughVolume;
	std::vector<Vector2D*> _vertexes;

public:
	Volume(float centerX, float centerY, float radius, VolumeVertexFactory& factory) : _roughVolume(centerX, centerY, radius) { _vertexes = factory(); }
	Volume(float centerX, float centerY, float radius, VolumeVertexFactory&& factory) : _roughVolume(centerX, centerY, radius) { _vertexes = factory(); }
	virtual ~Volume();

public:
	void Resize(float radius);
	virtual void Reposition(float centerX, float centerY);
	/// <summary>
	/// Check Collide from same coordinate
	/// </summary>
	/// <param name="volume">This object and volume should be same coordinate</param>
	/// <returns></returns>
	bool IsCollide(const Volume& volume) const;

public:
	virtual bool IsIn(const Vector2D& coordinate, const Vector2D& v) const;

public:
	const std::vector<Vector2D*>& GetVertexes() const { return _vertexes; }
	const Vector2D& GetCenter() const { return _roughVolume.GetCenter(); }

protected:
	float GetRadius() const { return _roughVolume.GetRadius(); }
};
