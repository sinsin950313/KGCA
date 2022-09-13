#pragma once

#include "CommonClass.h"
#include "Rectangle.h"
#include "TDX2DObject.h"

class DX2DCamera : public Common
{
private:
	Custom::Rectangle _physicsArea;
	float _windowWidth;
	float _windowHeight;

public:
	DX2DCamera(Vector2D center, float physicsWidth, float physicsHeight);

public:
	Vector2D GetCenter() { return _physicsArea.GetCenter(); }
	// Physics Coordinate to Screen Coordinate
	Position2D PhysicsToDisplay(Vector2D absolute);
	void Move(float x, float y);
	void Move(Vector2D center);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
