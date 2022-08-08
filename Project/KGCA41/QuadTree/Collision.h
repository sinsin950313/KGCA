#pragma once

class Rect;
class Object;

class Collision
{
public:
	static bool IsCollide(const Rect& r1, const Rect& r2);
	static bool IsOverlap(const Rect& r1, const Rect& r2);
	static Rect GetCollision(const Rect& r1, const Rect& r2);

public:
	static bool IsCollide(const Object& obj1, const Object& obj2);
	static Rect GetCollision(const Object& obj1, const Object& obj2);
};
