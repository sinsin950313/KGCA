#pragma once

#include "CommonClass.h"
#include "TDX2DObject.h"
#include "Object.h"

class DX2DCamera;

class DX2DGameObject : public Common
{
private:
	TDX2DObject* _dxObject;
	Object2D* _physicsObject;

public:
	DX2DGameObject(Position2D center, float width, float height, float mass);
	~DX2DGameObject();

public:
	TDX2DObject* GetDXObject() { return _dxObject; }
	Object2D* GetPhysicsObject() { return _physicsObject; }
	void Move(float x, float y);
	void Move(Vector2D center);
	// should be in Scene or Camera
	//void CalculateDXPosition(DX2DCamera* camera);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
