#pragma once

class Object;
class Volume;
class Rectangle;
class Circle;

class Collision
{
public:
	static bool IsCollide(const Volume& r1, const Volume& r2);
	static bool IsOverlap(const Rectangle& r1, const Rectangle& r2);
	static Rectangle GetCollision(const Rectangle& r1, const Rectangle& r2);

public:
	static bool IsCollide(const Circle& cir1, const Circle& cir2);
};
