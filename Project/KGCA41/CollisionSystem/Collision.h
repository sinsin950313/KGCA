#pragma once

#include "Volume.h"

class Rectangle;
//class Circle;

class Collision
{
public:
	template<int dimension>
	static bool IsCollide(const Volume<dimension>& r1, const Volume<dimension>& r2);
	//static bool IsOverlap(const Rectangle& r1, const Rectangle& r2);
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
