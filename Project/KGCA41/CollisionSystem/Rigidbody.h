#pragma once

#include "Vector2D.h"

class Rigidbody
{
private:
	float _mass;
	Vector2D _acc;
	Vector2D _vel;

public:
	Rigidbody(float mass = 1) : _mass(mass) { }

public:
	void AddForce(const Vector2D& newForce);
	void Calculate(float deltaTime);

public:
	float GetMass() { return _mass; }
	Vector2D GetAcceleration() { return _acc; }
	Vector2D GetVelocity() { return _vel; }
};
