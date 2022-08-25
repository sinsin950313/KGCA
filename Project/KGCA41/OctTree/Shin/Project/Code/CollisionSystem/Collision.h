#pragma once

#include "Volume.h"

class Rectangle;
//class Circle;

class Collision
{
public:
	template<int dimension>
	static bool IsCollide(const Volume<dimension>& r1, const Volume<dimension>& r2);
	template<int dimension>
	static bool IsIn(const Volume<dimension>& from, const Volume<dimension>& to);
//	static Rectangle GetCollision(const Rectangle& r1, const Rectangle& r2);
//
//public:
//	static bool IsCollide(const Circle& cir1, const Circle& cir2);
};

template<int dimension>
bool Collision::IsCollide(const Volume<dimension>& r1, const Volume<dimension>& r2)
{
	return (r1.IsCollide(r2)) || (r2.IsCollide(r1));
}

template<int dimension>
inline bool Collision::IsIn(const Volume<dimension>& from, const Volume<dimension>& to)
{
	auto vertexes = to.GetVertexes();
	auto coordinate = to.GetCenter();
	for (auto vertex : vertexes)
	{
		if (!from.IsIn(coordinate, *vertex))
		{
			return false;
		}
	}
	return true;
}
