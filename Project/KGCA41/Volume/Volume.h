#pragma once

#include <vector>
#include "PhysicsVector.h"

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
template<int dim>
class VolumeVertexFactory
{
public:
	virtual std::vector<PhysicsVector<dim>*> operator()() = 0;
};

template<int dim>
class Volume
{
private:
	class RoughVolume
	{
		PhysicsVector<dim> _center;
		float _radius;

	public:
		RoughVolume(PhysicsVector<dim>& center, float radius) : _center(center), _radius(radius) { }

	public:
		/// <summary>
		/// Check local coordinate distance
		/// </summary>
		/// <param name="v">This should be this object's local coordinate</param>
		/// <returns></returns>
		bool IsIn(const PhysicsVector<dim>& v) const;
		void Resize(float radius) { _radius = radius; }
		void Reposition(PhysicsVector<dim>& pos) { _center = pos; }

	public:
		const PhysicsVector<dim>& GetCenter() const { return _center; }
		float GetRadius() const { return _radius; }
	};

private:
	RoughVolume _roughVolume;
	std::vector<PhysicsVector<dim>*> _vertexes;

public:
	//easy way? what about universal reference?
	//template<PhysicsVector T, VolumeVertexFactory VF>
	//Volume(const T&& center, float radius, VF&& factory) : _roughVolume(center, radius) { _vertexes = factory(); }
	Volume(PhysicsVector<dim>& center, float radius, VolumeVertexFactory<dim>& factory) : _roughVolume(center, radius) { _vertexes = factory(); }
	Volume(PhysicsVector<dim>&& center, float radius, VolumeVertexFactory<dim>& factory) : _roughVolume(center, radius) { _vertexes = factory(); }
	Volume(const PhysicsVector<dim>& center, float radius, VolumeVertexFactory<dim>&& factory) : _roughVolume(center, radius) { _vertexes = factory(); }
	Volume(PhysicsVector<dim>&& center, float radius, VolumeVertexFactory<dim>&& factory) : _roughVolume(center, radius) { _vertexes = factory(); }
	virtual ~Volume();

public:
	void Resize(float radius);
	virtual void Reposition(PhysicsVector<dim>& pos);
	/// <summary>
	/// Check Collide from same coordinate
	/// </summary>
	/// <param name="volume">This object and volume should be same coordinate</param>
	/// <returns></returns>
	bool IsCollide(const Volume& volume) const;

public:
	virtual bool IsIn(const PhysicsVector<dim>& coordinate, const PhysicsVector<dim>& v) const;
	virtual void Print() const = 0;

public:
	const std::vector<PhysicsVector<dim>*>& GetVertexes() const { return _vertexes; }
	const PhysicsVector<dim>& GetCenter() const { return _roughVolume.GetCenter(); }

protected:
	float GetRadius() const { return _roughVolume.GetRadius(); }
};

template<int dim>
inline bool Volume<dim>::RoughVolume::IsIn(const PhysicsVector<dim>& v) const
{
	return v.Length() <= _radius;
}

template<int dim>
inline Volume<dim>::~Volume()
{
	for (auto iter = _vertexes.begin(); iter != _vertexes.end(); ++iter)
	{
		delete (*iter);
	}
}

template<int dim>
inline void Volume<dim>::Resize(float radius)
{
	float ratio = radius / _roughVolume.GetRadius();
	for (auto iter = _vertexes.begin(); iter != _vertexes.end(); ++iter)
	{
		PhysicsVector<dim> tmp = (*(*iter) * ratio);
		**iter = tmp;
	}

	_roughVolume.Resize(radius);
}

template<int dim>
inline void Volume<dim>::Reposition(PhysicsVector<dim>& pos)
{
	_roughVolume.Reposition(pos);
}

template<int dim>
inline bool Volume<dim>::IsCollide(const Volume& volume) const
{
	const std::vector<Vector2D*>& checkVolumeVectexes = volume.GetVertexes();
	for (auto iter = checkVolumeVectexes.begin(); iter != checkVolumeVectexes.end(); ++iter)
	{
		if (IsIn(volume.GetCenter(), **iter))
		{
			return true;
		}
	}
	return false;
}

template<int dim>
inline bool Volume<dim>::IsIn(const PhysicsVector<dim>& coordinate, const PhysicsVector<dim>& v) const
{
	PhysicsVector<dim> absolute = v + coordinate;
	PhysicsVector<dim> relative = absolute - GetCenter();
	return _roughVolume.IsIn(relative);
}
