#pragma once

class Circle
{
private:
	float _centerX;
	float _centerY;
	float _radius;

public:
	Circle() = default;
	Circle(float centerX, float centerY, float radius) { Resize(centerX, centerY, radius); }

public:
	float GetCenterX() const { return _centerX; }
	float GetCenterY() const { return _centerY; }
	float GetRadius() const { return _radius; }

public:
	bool operator&&(const Circle& circle) const;
	bool operator==(const Circle& circle) const { return GetCenterX() == circle.GetCenterX() && GetCenterY() == circle.GetCenterY() && GetRadius() == circle.GetRadius(); }

public:
	void Resize(float centerX, float centerY, float radius);
};
